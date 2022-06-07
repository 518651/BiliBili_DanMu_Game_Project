#include<iostream>
#include<string>
#include <json/json.h>
#include <curl/curl.h>


using namespace std;

typedef struct DanMu_Data{
	string DanMu_Post;

	//用户信息
	string Username;
	string Lost_Username;
	int UID;
	int Lost_UID;
	//弹幕数据
	string Text;
	string LostText;
	//时间
	string Time;
	string LostTime;
	
}DanMu_Data;

	


string UTF8ToGBK(const std::string& strUTF8);
string GBKToUTF8(const std::string& strGBK);

//请求弹幕POST包
string Get_BililBili_DanMu();


//解析弹幕数据
BOOL analysis(string Json_data);

//http POST请求  
CURLcode curl_post_req(const string& url, const string& postParams, string& response);

//WebSocket请求
void Get_Data_Page_Information();


//funtion
void Set_Command_To_Game();





