#include<iostream>
#include<string>
#include <json/json.h>
#include <curl/curl.h>


using namespace std;

typedef struct DanMu_Data{
	string DanMu_Post;

	//�û���Ϣ
	string Username;
	string Lost_Username;
	int UID;
	int Lost_UID;
	//��Ļ����
	string Text;
	string LostText;
	//ʱ��
	string Time;
	string LostTime;
	
}DanMu_Data;

	


string UTF8ToGBK(const std::string& strUTF8);
string GBKToUTF8(const std::string& strGBK);

//����ĻPOST��
string Get_BililBili_DanMu();


//������Ļ����
BOOL analysis(string Json_data);

//http POST����  
CURLcode curl_post_req(const string& url, const string& postParams, string& response);

//WebSocket����
void Get_Data_Page_Information();


//funtion
void Set_Command_To_Game();





