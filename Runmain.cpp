#include "Control.h"
#include<fstream>
#include <thread>

DanMu_Data DanMu_Data_M;
PID_control_data PID_control_data_M;

typedef void (*SetHandle1) ();
SetHandle1 SetHandle;//DLL ��ȡ�������

typedef void (*KeyDown1) (USHORT VirtualKey);
KeyDown1 KeyDown;//DLL ��������
typedef void (*KeyUp1) (USHORT VirtualKey);
KeyUp1 KeyUp;//DLL ��������

//? [W] 3s  1.5[ba]  w3/ba1.5  wwww 4*w =w4
//? []



//������Ļ����
int analysis(string Json_data) {
	string w = "w";
	string W = "W";
	string a = "a";
	string A = "A";
	string d = "d";
	string D = "D";
	string s = "s";
	string S = "S";
	string R = "R";
	string r = "r";
	string Tab = "T";
	string t = "t";
	string backspace = "b";
	int address = 0;


	if (Json_data.find(W) != -1 || Json_data.find(w) != -1)
	{
		//if (Json_data.compare("w2")==0|| Json_data.compare("w3")==0|| Json_data.compare("w4")==0)
		//{
		//	int number = stoi(Json_data.substr(1, 1));
		//	//? warning ��PID�����㷨Ӱ����ʱ����ֱ�ӳ˶�ֵ
		//	
		//}
		setcolor(2);
		cout << "��⵽[W]�ؼ���" << endl;
		KeyDown((USHORT)0x57);
		setcolor(15);
		cout << Sleep_number << endl;
		Sleep(Sleep_number);
		KeyUp((USHORT)0x57);
		return 2;
	}
	else if (Json_data.find(A) != -1 || Json_data.find(a) != -1)
	{
		setcolor(2);
		cout << "��⵽[A]�ؼ���" << endl;
		KeyDown((USHORT)0x41);
		setcolor(15);
		Sleep(1500);
		KeyUp((USHORT)0x41);
		return 3;
	}
	else if (Json_data.find(S) != -1 || Json_data.find(s) != -1)
	{
		setcolor(2);
		cout << "��⵽[S]�ؼ���" << endl;
		KeyDown((USHORT)0x53);
		setcolor(15);
		Sleep(1500);
		KeyUp((USHORT)0x53);
		return 4;
	}
	else if (Json_data.find(D) != -1 || Json_data.find(d) != -1)
	{
		setcolor(2);
		cout << "��⵽[D]�ؼ���" << endl;
		KeyDown((USHORT)0x44);
		setcolor(15);
		Sleep(1500);
		KeyUp((USHORT)0x44);
		return 5;
	}
	else if (Json_data.find(R) != -1 || Json_data.find(r) != -1)
	{
		setcolor(2);
		cout << "��⵽[R]�ؼ���" << endl;
		KeyDown((USHORT)0x52);
		setcolor(15);
		Sleep(1500);
		KeyUp((USHORT)0x52);
		return 6;
	}
	else if (Json_data.find(Tab) != -1||Json_data.find(t)!=-1)
	{
		setcolor(2);
		cout << "��⵽[Tab]�ؼ���" << endl;
		KeyDown((USHORT)0x09);
		setcolor(15);
		Sleep(500);
		KeyUp((USHORT)0x09);
		return 7;
	}
	else if(Json_data.find(backspace) != -1)
	{
		setcolor(2);
		cout << "��⵽[�ո�]�ؼ���" << endl;
		KeyDown((USHORT)0x08);
		setcolor(15);
		Sleep(3000);
		KeyUp((USHORT)0x08);
		return 6;
	}
	else
	{
		return 0;
	}

}





void main() {
	cotrol_data_initialization();
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	DanMu_Data_M.Time = sys.wMinute;
	DanMu_Data_M.LostTime = sys.wMinute + 1;
	cout << DanMu_Data_M.Time << DanMu_Data_M.LostTime << endl;
	HINSTANCE hDLL = LoadLibrary(L"kmclassdll.dll");
	DWORD dwError = 1;
	dwError = GetLastError();
	cout << "�����ļ�װ�����,��ַ:" << hDLL << dwError << endl;
	SetHandle = (SetHandle1)GetProcAddress(hDLL, "SetHandle");//������������
	SetHandle();

	KeyDown = (KeyDown1)GetProcAddress(hDLL, "KeyDown");//��ʼ���������º���

	KeyUp = (KeyUp1)GetProcAddress(hDLL, "KeyUp");//��ʼ������������
	thread th1(control_data_thread, danmu_strict_data);
	th1.detach();

	Get_Data_Page_Information();
}

//join ���߳�
//dech 