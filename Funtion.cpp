#include "Control.h"


void input_funtion(int model) {
	cout << "Success!" << endl;
	switch (model)
	{
		case 2:keybd_event('W', 0, 0, 0); //����W��
			keybd_event('W', KEYEVENTF_KEYUP, 0,0);
			break;
		case 3:keybd_event('A', 0, 0, 0); //����A��
			keybd_event('A', KEYEVENTF_KEYUP, 0, 0);
			break;
		case 4:keybd_event('S', 0, 0, 0); //����S��
			keybd_event('S', KEYEVENTF_KEYUP, 0, 0);
			break;
		case 5:keybd_event('D', 0, 0, 0); //����D��
			keybd_event('D', KEYEVENTF_KEYUP, 0, 0);
			break;
	default:
		cout << "δֵ֪,�ѱ�ϵͳ����" << endl;
		break;
	}
}