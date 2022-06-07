#include <iostream>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/WebSocket.h>
#include <Poco/Net/HTTPClientSession.h>
#include <zlib.h>
#include <chrono>
#include <thread>
#include <vector>
#include <stack>
#include <json/json.h>
#include <ctime>
#include <curl/curl.h>

#pragma comment(lib,"ws2_32.lib")
using namespace std;

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::Net::WebSocket;
Json::Reader reader;
Json::Value root;


int pack(char*& ptr, const string& payload, int pv = 0, int t = 7) {
    char header[16];
    uint32_t pack_len = 16 + payload.length(),
        header_len = htons(16),
        proto_version = htons(pv),
        type = htonl(t),
        fixed = htonl(1),
        pack_len_converted = htonl(pack_len);
    memcpy(&header[0], &pack_len_converted, 4);
    memcpy(&header[4], &header_len, 2);
    memcpy(&header[6], &proto_version, 2);
    memcpy(&header[8], &type, 4);
    memcpy(&header[12], &fixed, 4);
    std::cout << std::endl;
    ptr = new char[pack_len];
    memcpy(ptr, header, sizeof(header));
    memcpy(ptr + 16, payload.c_str(), payload.length());
    return pack_len;
}

int conOpenPack(char*& ptr, const string& room_id) {
    string payload = (R"({"roomid":)" + room_id + R"(,"protover":2,"platform":"web"})");
    return pack(ptr, payload);
}

int heartBeatPack(char*& ptr) {
    string payload = R"([object Object])";
    return pack(ptr, payload, 1, 2);
}

int sendHearBeat(WebSocket*& ws) {
    char* msg{ nullptr };
    int send_len = heartBeatPack(msg);

    cout << endl;
    int len = ws->sendFrame(msg, send_len, WebSocket::FRAME_BINARY);
    std::cout << "������BiliBili��Ļ���������ͳ�Ϊ " << len << " �ֽڵ��������ݰ�" << std::endl;
    delete[] msg;
    return len;
}

unsigned char* serializePack(unsigned char* data, unsigned char* res, int data_len) {
    // ����������λ��16�ֽڱ�ʶ�ֽ�֮��Ŀռ���
    memcpy(res, data + 16, data_len - 16);
    return res;
}

void connectToDanmuServer(WebSocket*& ws, const string& room_id) {
    char* msg;
    int send_len = conOpenPack(msg, room_id);
    int len = ws->sendFrame(msg, send_len, WebSocket::FRAME_BINARY);
    std::cout << "������BiliBili��Ļ���������ͳ�Ϊ " << len << " �ֽڵ��������ݰ�" << std::endl;
    int flags = 0;

    unsigned char rcv_buffer[256];
    unsigned char rcv_buffer_ser[256];
    int rcv_len = ws->receiveFrame(rcv_buffer, 256, flags);
    std::cout << "�յ� " << rcv_len << " �ֽڵĻ�Ӧ���ݰ�, ��������:" << std::endl;
    std::cout << serializePack(rcv_buffer, rcv_buffer_ser, rcv_len) << std::endl;
    delete[] msg;
}

int uncompressDanmuPack(unsigned char* compressed, int source_len, unsigned char* uncompressed) {
    uLong dest_len;
    uncompress(uncompressed, &dest_len, compressed, source_len);
    return dest_len;
}

// ���ճ������
vector<string> cleanString(string str) {
    vector<string> res;
    int start{ -1 }, len{ -1 }, cnt{ 0 };
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '{') {
            if (cnt == 0) {
                len = 1;
                start = i;
            }
            ++cnt;
        }
        else if (str[i] == '}') {
            --cnt;
            if (cnt == 0) {
                res.push_back(str.substr(start, len));
            }
        }
        ++len;
    }
    return res;
}

int rcvPack(WebSocket*& ws, int size) {
    int flags = 0;
    unsigned char msg_compressed[2048], msg_uncompressed[4096];

    flags = ws->receiveFrame(msg_compressed, 2048, flags);
    // ������յ��������Ǿ�����zlibѹ������
    int len = uncompressDanmuPack(msg_compressed + 16, flags - 16, msg_uncompressed);
    string res(reinterpret_cast<char*>(msg_uncompressed), len);
    int index{ -1 };
    string cmd;
    if ((index = res.find("{\"") != -1)) {
        vector<string> jsons = cleanString(res);
        for (auto& json : jsons) {
            if (!reader.parse(json, root)) {
                cout << "JSON������������: " << reader.getFormattedErrorMessages() << endl;
            }
            else {
                cmd = root["cmd"].asString();
                if (cmd == "DANMU_MSG") {
                    cout << "��" << root["info"][2][1].asString() << "�������˵�Ļ -> "
                        << root["info"][1].asString();
                }
                else if (cmd == "SEND_GIFT") {
                    cout << "��" << root["data"]["uname"].asString() << "���ͳ������� -> "
                        << root["data"]["giftName"].asString() << " �� " << root["data"]["num"].asInt();
                }
                else if (cmd == "WELCOME") {
                    cout << "�û���" << root["data"]["uname"].asString() << "��������ֱ����";
                }
                else {
                    cout << "δʶ��Ļ: " << json;
                }
                cout << endl;
            }
        }
    }
    return flags;
}


int main(int args, char** argv) {
    std::string roomId;
    std::string input="432048";
    roomId = (input == "y" || input == "Y") ? "22247501" : input;
    HTTPClientSession cs("broadcastlv.chat.bilibili.com", 2244);
    HTTPRequest request(HTTPRequest::HTTP_GET, "/sub", HTTPMessage::HTTP_1_1);
    request.set("origin", "http://broadcastlv.chat.bilibili.com");
    HTTPResponse response;
    WebSocket* socket=NULL;
    int flags;
    std::time_t last_time{ std::time(nullptr) };
    try {
        socket = new WebSocket(cs, request, response);
        connectToDanmuServer(socket, roomId);
        while (true) {
            rcvPack(socket, 2048);
            if (time(nullptr) - last_time >= 30) {
                sendHearBeat(socket);
                last_time = time(nullptr);
            }

        }
    }
    catch (std::exception& e) {
        std::cout << "Exception " << e.what();
        socket->close();
    }

}