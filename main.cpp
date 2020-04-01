#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
string unzip, Pnum;
bool check() {
	system("dir /B *.zip > ____");
	ifstream p("____");
	string s;
	while (p >> s) {
		if (s == Pnum) return 1;
	}
	return 0;
}
int main() {
	system("g++ data.cpp -o data");
	system("python data_download.py");
	ifstream pp("_");
	pp >> Pnum;
	while (!check()) {
		puts("Waiting...");
		Sleep(5000);
	}
	puts("Download Successful!!!");
#ifdef _WIN32
	unzip = "\"C:\\Program Files\\WinRAR\\winrar.exe\" e " + Pnum;
#endif
/*
#ifdef __linux__
	unzip = ;
#endif
*/
	system(unzip.c_str());
	system("data");
}
