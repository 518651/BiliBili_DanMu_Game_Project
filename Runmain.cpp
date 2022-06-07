#include "Control.h"
#include<fstream>
DanMu_Data _DanMu_Data;


ofstream ofs;
ifstream ifs;



void main() {
	Get_Data_Page_Information();
	//ofs.open("data.txt", ios::out);
	//_DanMu_Data.DanMu_Post = Get_BililBili_DanMu();
	//ofs << Get_BililBili_DanMu() << endl;
	//ofs.close();
	//ifs.open("data.txt", ios::in);
	//analysis(_DanMu_Data.DanMu_Post);
}