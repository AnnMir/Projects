#include<iostream>
#include<fstream>
#include<conio.h>
#include<list>
#include"sort.h"

using namespace std;

int main(int argc, char** argv){
	string str;
	std::list<string> Str;
	ifstream file;
	file.open("input.txt", ios::in | ios::binary);
	if (!file) {
		cout << "File error - can't open to read data!";
		cin.sync(); cin.get(); return 2;
	}
	while (1){
		if (file.eof()) break;
		getline(file,str);
		Str.push_back(str);
	}
	using namespace Strings;
	sort_strings(&Str);
	ofstream out("output.txt");
	while (!Str.empty()){
		out<<Str.front() << "\n";
		Str.pop_front();
	}
	file.close(); // Закрываем файл
	out.close();
	_getch();
	return 0;
}