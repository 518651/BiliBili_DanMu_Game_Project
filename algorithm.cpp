#include "Control.h"

int Sleep_number = 0;


PID_control_data PID_control_data_c;
DanMu_Data DanMu_Data_c;

void cotrol_data_initialization() {
	PID_control_data_c.Pid_SetSpeed = 100.0;
	PID_control_data_c.Pid_ActualSpeed = 0.0;
	PID_control_data_c.Pid_Error = 0.0;
	PID_control_data_c.Pid_Error_Last = 0.0;
	PID_control_data_c.Pid_Voltage = 0.0;
	PID_control_data_c.Pid_integral = 0.0;
	PID_control_data_c.Pid_kp = 0.2;
	PID_control_data_c.Pid_ki = 0.015;
	PID_control_data_c.Pid_kd = 0.2;
	DanMu_Data_c.frequency_i_last = 0;
}

void algorithm_control_data() {
	cout<<PID_control_data_c.Pid_SetSpeed << endl;
	PID_control_data_c.Pid_Error = PID_control_data_c.Pid_SetSpeed - PID_control_data_c.Pid_ActualSpeed;
	PID_control_data_c.Pid_integral += PID_control_data_c.Pid_Error;
	PID_control_data_c.Pid_Voltage = PID_control_data_c.Pid_kp * PID_control_data_c.Pid_Error + PID_control_data_c.Pid_ki * PID_control_data_c.Pid_integral + PID_control_data_c.Pid_kd * (PID_control_data_c.Pid_Error - PID_control_data_c.Pid_Error_Last);
	PID_control_data_c.Pid_Error_Last = PID_control_data_c.Pid_Error;
	PID_control_data_c.Pid_ActualSpeed = PID_control_data_c.Pid_Voltage * 100;
	if (PID_control_data_c.Pid_ActualSpeed < 500)
	{
		PID_control_data_c.Pid_ActualSpeed = 500;
	}
	Sleep_number = PID_control_data_c.Pid_ActualSpeed;
	cout << "实时控制数值为:" << PID_control_data_c.Pid_ActualSpeed << endl;
	spdlog::info("PID控制输出为:{}", PID_control_data_c.Pid_ActualSpeed);
}

void start_control_funtion() {
	//Sleep(10000);
	spdlog::info("---------------周期性调整开始---------------{}", danmu_strict_data);
	//PID_control_data_c.Pid_ActualSpeed= DanMu_Data_c.frequency_i;
	PID_control_data_c.Pid_ActualSpeed = danmu_strict_data;
	algorithm_control_data();
	DanMu_Data_c.frequency_i=0;
}