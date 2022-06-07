#include "Control.h"


//get�����post����������Ӧ����
size_t req_reply(void* ptr, size_t size, size_t nmemb, void* stream)
{
	//��ע�͵�������Դ�ӡ��������cookie����Ϣ
	//cout << "----->reply" << endl;
	string* str = (string*)stream;
	//cout << *str << endl;
	(*str).append((char*)ptr, size * nmemb);
	return size * nmemb;
}

//http POST����  
CURLcode curl_post_req(const string& url, const string& postParams, string& response)
{
	// curl��ʼ��  
	CURL* curl = curl_easy_init();
	// curl����ֵ 
	CURLcode res;
	if (curl)
	{
		// set params
		//����curl������ͷ
		struct curl_slist* header_list = NULL;
		header_list = curl_slist_append(header_list, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/101.0.4951.67 Safari/537.36");
		header_list = curl_slist_append(header_list, "Content-Type:application/x-www-form-urlencoded;charset=UTF-8");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header_list);

		//��������Ӧͷ����0�������� 1�������
		curl_easy_setopt(curl, CURLOPT_HEADER, 0);

		//��������Ϊpost����
		curl_easy_setopt(curl, CURLOPT_POST, 1);

		//���������URL��ַ
		curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
		//����post����Ĳ���
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postParams.c_str());

		//����ssl��֤
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, false);

		//CURLOPT_VERBOSE��ֵΪ1ʱ������ʾ��ϸ�ĵ�����Ϣ
		curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);

		curl_easy_setopt(curl, CURLOPT_READFUNCTION, NULL);

		//�������ݽ��պ�д�뺯��
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, req_reply);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&response);

		curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);

		//���ó�ʱʱ��
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 6);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);

		// ����post����
		res = curl_easy_perform(curl);
	}
	//�ͷ�curl 
	curl_easy_cleanup(curl);
	return res;
}


//����ĻPOST��
string Get_BililBili_DanMu()
{
	string url_post0 = "http://api.live.bilibili.com/ajax/msg?";
	string roomid = "roomid=432048";
	string resPost0;
	auto res3 = curl_post_req(url_post0, roomid, resPost0);
	if (res3 == CURLE_OK)
	{
		//cout << resPost0 << endl;
		resPost0= UTF8ToGBK(resPost0);
	}
	return resPost0;
}

