#include "Control.h"



DanMu_Data __DanMu_Data;
Json::Reader _reader;
Json::Value _root;




//������Ļ����
int analysis(string Json_data) {
	//if (_reader.parse(Json_data, _root))
	//{
	//	for (int n = 0; n < 10; n++)//���
	//	{
	//	__DanMu_Data.Text = _root["data"]["room"][n]["text"].asString();  //��ȡ��Ļ��Ϣ
	//	__DanMu_Data.Username = _root["data"]["room"][n]["nickname"].asString();//Bվ�û���
	//	__DanMu_Data.Time = _root["data"]["room"][n]["timeline"].asString();//ʱ��
	//	__DanMu_Data.UID = _root["data"]["room"][n]["uid"].asInt();//BվUID
	//	cout << __DanMu_Data.Time << "---" << __DanMu_Data.Username << "---" << __DanMu_Data.Text << endl;//�����һ��-�ھ�����Ļ����
	//		if (_root["data"]["room"].isArray()) {//����
	//			int nArraySize = _root["data"]["room"].size();
	//			for (int i = 0; i < nArraySize; i++)//��ʼ��JSON�ݹ�
	//			{
	//				__DanMu_Data.LostText = _root["data"]["room"][i]["text"].asString();//�𲽽���1-9����Ļ����
	//				__DanMu_Data.Lost_Username = _root["data"]["room"][i]["nickname"].asString();//����Bվ�û�����ע��:���������ʱ����������Ǹ�Bվ�û����Ա�,������ݶ��˾����ظ���
	//				__DanMu_Data.LostTime = _root["data"]["room"][i]["timeline"].asString();
	//				__DanMu_Data.Lost_UID = _root["data"]["room"][i]["uid"].asInt();
	//				if (__DanMu_Data.Lost_UID == __DanMu_Data.UID)//��ʼ����
	//				{
	//					if (__DanMu_Data.LostText != __DanMu_Data.Text) {
	//						cout << __DanMu_Data.LostTime << "---" << __DanMu_Data.Lost_Username << "---" << __DanMu_Data.LostText << endl;
	//					}
	//				}
	//				//cout << _root["data"]["room"][i]["timeline"].asString() << "----";
	//				//cout << _root["data"]["room"][i]["nickname"].asString() << "----";
	//				//cout << _root["data"]["room"][i]["text"].asString() << endl;
	//				//__DanMu_Data.UID = _root["data"]["room"][i]["uid"].asInt();
	//			}
	//		}
	//	}

	//}
	string w = "w";
	string W = "W";
	string a = "a";
	string A = "A";
	string d = "d";
	string D = "D";
	string s = "s";
	string S = "S";
	int address=0;
	if (Json_data.find(W) != -1 || Json_data.find(w) != -1)
	{
		setcolor(2);
		cout << "��⵽[W]�ؼ���" << endl;
		setcolor(15);
		return 2;
	}
	else if (Json_data.find(A) != -1 || Json_data.find(a) != -1)
	{
		setcolor(2);
		cout << "��⵽[A]�ؼ���" << endl;
		setcolor(15);
		return 3;
	}
	else if (Json_data.find(S) != -1 || Json_data.find(s) != -1)
	{
		setcolor(2);
		cout << "��⵽[S]�ؼ���" << endl;
		setcolor(15);
		return 4;
	}
	else if (Json_data.find(D) != -1 || Json_data.find(d) != -1)
	{
		setcolor(2);
		cout << "��⵽[D]�ؼ���" << endl;
		setcolor(15);
		return 5;
	}
	else
	{
		return 0;
	}

}

