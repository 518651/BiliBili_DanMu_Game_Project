#include "Control.h"


void input_funtion(int model) {
	cout << "Success!" << endl;
	switch (model)
	{
		case 2:keybd_event('W', 0, 0, 0); //����W��
			keybd_event('W', 0,  KEYEVENTF_KEYUP, 0);
			
			//system("python python_demo.py");
			//mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			//mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			break;
		case 3:keybd_event('A', 0, 0, 0); //����A��
			keybd_event('A',0, KEYEVENTF_KEYUP, 0);
			break;
		case 4:keybd_event('S', 0, 0, 0); //����S��
			keybd_event('S', 0, KEYEVENTF_KEYUP, 0);
			break;
		case 5:keybd_event('D', 0, 0, 0); //����D��
			keybd_event('D', 0, KEYEVENTF_KEYUP, 0);
			break;
	default:
		cout << "δֵ֪,�ѱ�ϵͳ����" << endl;
		break;
	}
}