#include "Control.h"
#include <vector>
#include <chrono>
#include "ThreadPool.h"
#include "setTimefuntion.h"


int cnt = 20;
std::mutex thlock;

DanMu_Data DanMu_Data_R;

void Thread_one(string DanMu_Analysis) {
	std::lock_guard<std::mutex> lockGuard(thlock);
	analysis(DanMu_Analysis);
}

void control_data_thread(const int danmu_number) {
	cout << "danmu_number��" << danmu_number << endl;
	Timer timer;
	while (true)
	{
		timer.start(60000, std::bind(start_control_funtion));
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));
		timer.stop();
	}

}

void run_the_cheak_config() {
	//GetLocalTime(&sys);
	//printf("%4d/%02d/%02d %02d:%02d:%02d.%03d ����%1d\n", sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds, sys.wDayOfWeek);
	if (DanMu_Data_R.LostTime== 60)
	{
		DanMu_Data_R.LostTime = 0;
	}
	if (DanMu_Data_R.Time== DanMu_Data_R.LostTime)
	{
		start_control_funtion();
	}
}



int cotrol_Thread(int return_data) {
	//cout << danmu_strict_data << endl;
	//run_the_cheak_config();
	//start_control_funtion();
	switch (return_data)
	{
	case 2:
		cout << "��⵽2" << endl;
		analysis(danmu_funtion_data);
		break;
	case 3://�������ﴦ��
		spdlog::warn("��⵽�û���������");
		break;
	case 4://�������ﴦ��
		spdlog::warn("��⵽�û���������");
		break;
	case 5://�������ﴦ��
		spdlog::warn("��⵽�û�������Ϣ");
		break;
	default:
		break;
	}
	return 0;
}