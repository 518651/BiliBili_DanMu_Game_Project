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

	//�û���Ϣ
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
	//��Ļ����
	string Text;
	string Message;
	string Gift_name;
	//ʱ��
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

//����ĻPOST��
string Get_BililBili_DanMu();


//������Ļ����
int analysis(string Json_data);

//http POST����  
CURLcode curl_post_req(const string& url, const string& postParams, string& response);

//WebSocket����
void Get_Data_Page_Information();


//funtion
void setcolor(unsigned short color);

//���߳�
int cotrol_Thread(int return_data);

void input_funtion(int model);

int python_data_analysis(string Python_send_data);//����python��Json

int _find(char* star, int starl, char* data, int datal);//����˵�� ����ֵ1Ϊ�ҵ�0Ϊû�ҵ�����һ������Ϊ�ؼ��ַ������ڶ�������Ϊ�ؼ��ַ������ȣ��������ؼ���Ϊԭʼ�ַ��������ĸ�����Ϊԭʼ�ַ�������


//�㷨���Ƴ�ʼ��
void cotrol_data_initialization();

//�����Ե�����ֵ
void start_control_funtion();

//��ʱִ���޸�
void control_data_thread(const int danmu_number);