#include "Control.h"
#include <json/json.h>

Json::Reader reader;
Json::Value root;

DanMu_Data _DanMu_Data;

int danmu_strict_data = 0;

string danmu_funtion_data = "";

int python_data_analysis(string Python_send_data) {
	int cheak = Python_send_data.find_first_of("{");
	if (cheak >=2)
	{
		return 0;
	}
	if (reader.parse(Python_send_data, root))
	{
		_DanMu_Data.room_id = root["room_id"].asString();
		_DanMu_Data.Object = root["Object"].asString();
		if (_DanMu_Data.Object == "renqizhi")//����ָ��
		{
			_DanMu_Data.renqizhi = root["renqizhi"].asString();
			spdlog::info("����{}��ǰ����ָ��{}", _DanMu_Data.room_id, _DanMu_Data.renqizhi);
			return 1;
		}
		else if (_DanMu_Data.Object == "danmu")//��Ļ����
		{
			_DanMu_Data.Username = root["Username"].asString();
			danmu_funtion_data = root["Text"].asString();
			danmu_strict_data=_DanMu_Data.frequency_i = _DanMu_Data.frequency_i++;
			spdlog::info("�û�:{}---���͵�Ļ---{}  �����յ�{}����Ļ",_DanMu_Data.Username, danmu_funtion_data, _DanMu_Data.frequency_i);
			return 2;
		}
		else if (_DanMu_Data.Object == "gift")//��������
		{
			_DanMu_Data.Username = root["Username"].asString();
			_DanMu_Data.Text = root["Giftname"].asString();
			_DanMu_Data.Gift_number = root["Number"].asString();
			spdlog::info("�û�:{}����{}*{}", _DanMu_Data.Username, _DanMu_Data.Text, _DanMu_Data.Gift_number);
			return 3;
		}
		else if (_DanMu_Data.Object== "buy")//��������
		{
			_DanMu_Data.Username = root["Username"].asString();
			_DanMu_Data.Text = root["Giftname"].asString();
			spdlog::info("�û�:{}����������{}", _DanMu_Data.Username, _DanMu_Data.Text);
			return 4;
		}
		else if (_DanMu_Data.Object=="Message")//������Ϣ
		{
			_DanMu_Data.Username = root["Username"].asString();
			_DanMu_Data.Price = root["Price"].asString();
			_DanMu_Data.Message = root["Message"].asString();
			spdlog::info("�û�:{}������ֵ{}Ԫ��������Ϣ{}", _DanMu_Data.Username, _DanMu_Data.Price, _DanMu_Data.Message);
			return 5;
		}
	}

}











int _find(char* star, int starl, char* data, int datal)//����˵�� ����ֵ1Ϊ�ҵ�0Ϊû�ҵ�����һ������Ϊ�ؼ��ַ������ڶ�������Ϊ�ؼ��ַ������ȣ��������ؼ���Ϊԭʼ�ַ��������ĸ�����Ϊԭʼ�ַ�������
{
	char a = 0;
	char* b = (char*)malloc(datal);
	char b1 = 0;
	char c = 0;
	char* d = (char*)malloc(datal);
	char d1 = 0;
	int o = 0;
	char tiaojian = 0;
	char isok = 1;
	//char*p = out;
	for (char a = 0; a < datal; a++)//ѭ���ȶ�star��data���������star���ֵ�λ��a�ǿ��Ʊ���
	{
		char* data1 = data;
		data1 = data1 + a;
		//printf("%p\n", data1);
		if (*data1 == *star)//�Աȵ�����star��һ���ַ���Ȼ��ʼ�жϺ����ַ�
		{
			if (starl < 3)
			{
				if (b1 < datal - 1)
				{

					b[b1] = a + 1;//���Ա�ĩβ��ƫ�Ƹ�ֵ������b,ʵ�������Ҫ+1


					b1 = b1 + 1;
				}
			}
			//printf("%p\n", data1);
			for (char i = 1; i < starl; i++)//ѭ���ж�֮���ַ����Ƿ���ȫһ�£����һ���ַ���/0û�б�Ҫ�Ƚϣ�
			{
				char* s1 = data1;//��Ӱ��ԭ���ԱȽ��̣�ʹ��s1��s2����Ƚ�
				char* s2 = star;
				s1 = s1 + i;
				s2 = s2 + i;
				if (*s1 != *s2)//�ȶԺ�ͬ��break������ѭ���ȶ�star��data
				{

					break;
				}
				else//if (i == starl - 2 - 1)//��ɶԱ�
				{
					if (b1 < datal - 1)
					{

						b[b1] = a + i + 1;//���Ա�ĩβ��ƫ�Ƹ�ֵ������b,ʵ�������Ҫ+1


						b1 = b1 + 1;
						return 1;
					}
				}
			}

		}

	}


	return 0;
}




