#include <iostream>
#include <string.h>
#include "Commands.h"
using namespace std;

int main(int argc, char* argv[]) {
	system("cls");
	if (!strcmp(argv[1], "-a")){
		//Algorithm Mode
		if (argc == 5) {
			//Khi argc = 5, tại argv[3] có thể là InputFile(cmd1) hoặc InputSize (cmd3)
			ifstream fin(argv[3]);
			if (!fin) {
				//Nếu không mở file có tên argv[3] được thì đó là InputSize
				command3(argv[2],argv[3], argv[4]);
			}
			else {
				//Nếu mở được file có tên argv[3] thì đó là InputFile
				fin.close();
				command1(argv[2], argv[3], argv[4]);
			}
		}
		else if (argc == 6)
			command2(argv[2], argv[3], argv[4], argv[5]);
	}
	else if (!strcmp(argv[1], "-c")){
		//Compare Mode
		if (argc == 5)
			command4(argv[2], argv[3], argv[4]);
		else if (argc == 6)
			command5(argv[2], argv[3], argv[4], argv[5]);
	}
	return 0;
}
