#include "Control.h"
#include <Windows.h>


DanMu_Data __DanMu_Data;
Json::Reader _reader;
Json::Value _root;

//解析弹幕数据
BOOL analysis(string Json_data) {
	if (_reader.parse(Json_data, _root))
	{
		for (int n = 0; n < 10; n++)//输出
		{
		__DanMu_Data.Text = _root["data"]["room"][n]["text"].asString();  //获取弹幕信息
		__DanMu_Data.Username = _root["data"]["room"][n]["nickname"].asString();//B站用户名
		__DanMu_Data.Time = _root["data"]["room"][n]["timeline"].asString();//时间
		__DanMu_Data.UID = _root["data"]["room"][n]["uid"].asInt();//B站UID
		cout << __DanMu_Data.Time << "---" << __DanMu_Data.Username << "---" << __DanMu_Data.Text << endl;//输出第一条-第九条弹幕数据
			if (_root["data"]["room"].isArray()) {//查重
				int nArraySize = _root["data"]["room"].size();
				for (int i = 0; i < nArraySize; i++)//开始在JSON递归
				{
					__DanMu_Data.LostText = _root["data"]["room"][i]["text"].asString();//逐步解析1-9条弹幕数据
					__DanMu_Data.Lost_Username = _root["data"]["room"][i]["nickname"].asString();//解析B站用户名（注意:这个解析的时候会和上面的那个B站用户名对比,如果数据对了就是重复）
					__DanMu_Data.LostTime = _root["data"]["room"][i]["timeline"].asString();
					__DanMu_Data.Lost_UID = _root["data"]["room"][i]["uid"].asInt();
					if (__DanMu_Data.Lost_UID == __DanMu_Data.UID)//开始查重
					{
						if (__DanMu_Data.LostText != __DanMu_Data.Text) {
							cout << __DanMu_Data.LostTime << "---" << __DanMu_Data.Lost_Username << "---" << __DanMu_Data.LostText << endl;
						}
					}
					//cout << _root["data"]["room"][i]["timeline"].asString() << "----";
					//cout << _root["data"]["room"][i]["nickname"].asString() << "----";
					//cout << _root["data"]["room"][i]["text"].asString() << endl;
					//__DanMu_Data.UID = _root["data"]["room"][i]["uid"].asInt();
				}
			}
		}

	}
	
	return true;
}

