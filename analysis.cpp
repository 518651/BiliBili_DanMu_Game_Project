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
		if (_DanMu_Data.Object == "renqizhi")//人气指数
		{
			_DanMu_Data.renqizhi = root["renqizhi"].asString();
			spdlog::info("房间{}当前人气指数{}", _DanMu_Data.room_id, _DanMu_Data.renqizhi);
			return 1;
		}
		else if (_DanMu_Data.Object == "danmu")//弹幕数据
		{
			_DanMu_Data.Username = root["Username"].asString();
			danmu_funtion_data = root["Text"].asString();
			danmu_strict_data=_DanMu_Data.frequency_i = _DanMu_Data.frequency_i++;
			spdlog::info("用户:{}---发送弹幕---{}  共计收到{}条弹幕",_DanMu_Data.Username, danmu_funtion_data, _DanMu_Data.frequency_i);
			return 2;
		}
		else if (_DanMu_Data.Object == "gift")//赠送礼物
		{
			_DanMu_Data.Username = root["Username"].asString();
			_DanMu_Data.Text = root["Giftname"].asString();
			_DanMu_Data.Gift_number = root["Number"].asString();
			spdlog::info("用户:{}赠送{}*{}", _DanMu_Data.Username, _DanMu_Data.Text, _DanMu_Data.Gift_number);
			return 3;
		}
		else if (_DanMu_Data.Object== "buy")//购买礼物
		{
			_DanMu_Data.Username = root["Username"].asString();
			_DanMu_Data.Text = root["Giftname"].asString();
			spdlog::info("用户:{}购买了礼物{}", _DanMu_Data.Username, _DanMu_Data.Text);
			return 4;
		}
		else if (_DanMu_Data.Object=="Message")//悬赏信息
		{
			_DanMu_Data.Username = root["Username"].asString();
			_DanMu_Data.Price = root["Price"].asString();
			_DanMu_Data.Message = root["Message"].asString();
			spdlog::info("用户:{}发出价值{}元的悬赏信息{}", _DanMu_Data.Username, _DanMu_Data.Price, _DanMu_Data.Message);
			return 5;
		}
	}

}











int _find(char* star, int starl, char* data, int datal)//参数说明 返回值1为找到0为没找到，第一个参数为关键字符串，第二个参数为关键字符串长度，第三个关键字为原始字符串，第四个参数为原始字符串长度
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
	for (char a = 0; a < datal; a++)//循环比对star和data，输出所有star出现的位置a是控制变量
	{
		char* data1 = data;
		data1 = data1 + a;
		//printf("%p\n", data1);
		if (*data1 == *star)//对比到出现star第一个字符，然后开始判断后续字符
		{
			if (starl < 3)
			{
				if (b1 < datal - 1)
				{

					b[b1] = a + 1;//将对比末尾的偏移赋值给数组b,实际输出需要+1


					b1 = b1 + 1;
				}
			}
			//printf("%p\n", data1);
			for (char i = 1; i < starl; i++)//循环判断之后字符内是否完全一致（最后一个字符是/0没有必要比较）
			{
				char* s1 = data1;//不影响原本对比进程，使用s1和s2代替比较
				char* s2 = star;
				s1 = s1 + i;
				s2 = s2 + i;
				if (*s1 != *s2)//比对后不同则break，继续循环比对star和data
				{

					break;
				}
				else//if (i == starl - 2 - 1)//完成对比
				{
					if (b1 < datal - 1)
					{

						b[b1] = a + i + 1;//将对比末尾的偏移赋值给数组b,实际输出需要+1


						b1 = b1 + 1;
						return 1;
					}
				}
			}

		}

	}


	return 0;
}




