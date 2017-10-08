#include<iostream>
#include<fstream>
#include<conio.h>
#include<list>
#include"sort.h"

using namespace std;

int main(int argc, char** argv){
	string str;
	std::list<string> Str;
	ifstream file(argv[1]);
	ofstream out(argv[2]/*"output.txt"*/);
	//file.open("input.txt", ios::in | ios::binary);
	/*if (!file) {
		cout << "File error - can't open to read data!";
		cin.sync(); cin.get(); return 2;
	}*/
	if (argc != 3){
		out << "WRONG input";
	}
	else{
		while (getline(file, str)){
			//if (file.eof()) break;
			Str.push_back(str);
		}
		using namespace Strings;
		sort_strings(&Str);

		while (!Str.empty()){
			out << Str.front() << "\n";
			Str.pop_front();
		}
	}
	//file.close(); // Закрываем файл
	//out.close();
	_getch();
	return 0;
}