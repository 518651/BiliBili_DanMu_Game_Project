#pragma once
#include<iostream>
#include<string>
#include <json/json.h>
#include <curl/curl.h>
#include <Windows.h>
#include <spdlog/spdlog.h>
using namespace std;

class data_config
{
public:
	int ai;
	data_config(int i) : ai(i) { }

};


typedef struct DanMu_Data{
	string DanMu_Post;

	//用户信息
	string Username;
	string Lost_Username;
	string Object;
	int UID;
	int Lost_UID;
	int frequency_i;
	int frequency_i_last;
	string frequency_s;
	string room_id;
	string renqizhi;
	string Gift_number;
	string Price;
	//弹幕数据
	string Text;
	string Message;
	string Gift_name;
	//时间
	int Time;
	int LostTime;
	
}DanMu_Data;

typedef struct PID_control_data {
	float Pid_SetSpeed;
	float Pid_ActualSpeed;
	float Pid_Error;
	float Pid_Error_Last;
	float Pid_Voltage;
	float Pid_integral;
	float Pid_kp;
	float Pid_ki;
	float Pid_kd;
}PID_control_data;

extern int danmu_strict_data;
extern int Sleep_number;
extern string danmu_funtion_data;


string UTF8ToGBK(const std::string& strUTF8);
string GBKToUTF8(const std::string& strGBK);

//请求弹幕POST包
string Get_BililBili_DanMu();


//解析弹幕数据
int analysis(string Json_data);

//http POST请求  
CURLcode curl_post_req(const string& url, const string& postParams, string& response);

//WebSocket请求
void Get_Data_Page_Information();


//funtion
void setcolor(unsigned short color);

//多线程
int cotrol_Thread(int return_data);

void input_funtion(int model);

int python_data_analysis(string Python_send_data);//解析python的Json

int _find(char* star, int starl, char* data, int datal);//参数说明 返回值1为找到0为没找到，第一个参数为关键字符串，第二个参数为关键字符串长度，第三个关键字为原始字符串，第四个参数为原始字符串长度


//算法控制初始化
void cotrol_data_initialization();

//周期性调整数值
void start_control_funtion();

//定时执行修改
void control_data_thread(const int danmu_number);