#include <iostream>
#include <stdlib.h>
#include <vector>
#include <set> 
#include <fstream>
#include <sstream>
using namespace std;
string tostr(int x)
{
	stringstream a; a<<x; string p; a>>p; return p;
}
int main()
{
	system("dir /B *.in;*.ans;*.out >___");
	vector<string> fs;
	set<string> ss;
	{
	ifstream p("___");
	string r;
	while(getline(p,r)) fs.push_back(r),ss.insert(r);
	p.close(); system("del ___");
	}
	//LCP
	int l=0;
	for(l=0;;l++)
	{
		bool ok=1; string s=fs[0].substr(0,l+1);
		for(int i=0;i<fs.size();i++)
			if(fs[i].substr(0,l+1)!=s) ok=0;
		if(!ok) break;
	}
	string qz=fs[0].substr(0,l);
	int L=1e9,R=-1e9;
	string suf;
	for(int i=0;i<fs.size();i++)
	{
		string nx=fs[i].substr(l,fs.size()-l);
		int lp=nx.find_last_of('.');
		string pv=nx.substr(0,lp);
		if(!pv.size()) continue;
		bool gg=1;
		for(int i=0;i<pv.size();i++) gg&=isdigit(pv[i]);
		if(!gg) continue;
		if(nx.substr(lp,nx.size()-lp)==".ans") suf="ans";
		else if(nx.substr(lp,nx.size()-lp)==".out") suf="out";
		int x=atoi(pv.c_str());
		L=min(L,x); R=max(R,x);
	}
	if(L>R||!suf.size())
	{
		puts("Empty Dataset");
		return 0;
	}
	for(int i=L;i<=R;i++)
	{
		string p=qz+tostr(i)+".in";
		if(!ss.count(p))
		{
			printf("%s%d.in is missing\n",qz.c_str(),i);
			return 0;
		}
		p=qz+tostr(i)+"."+suf;
		if(!ss.count(p))
		{
			printf("%s%d.%s is missing\n",qz.c_str(),i,suf.c_str());
			continue;
		}
	}
	//$qz[$L,$R].in, $qz[$L,$R].$suf
	int TL=1,ML=128;
	system("mkdir uoj_data");
	for(int i=L;i<=R;i++)
	{
		string p=qz+tostr(i)+".in";
		string q=qz+tostr(i-L+1)+".in";
		system(("copy "+p+" uoj_data\\"+q).c_str());
		p=qz+tostr(i)+"."+suf;
		q=qz+tostr(i-L+1)+"."+suf;
		system(("copy "+p+" uoj_data\\"+q).c_str());
	}
	FILE*fp=fopen("uoj_data\\problem.conf","w");
	fprintf(fp,"\
use_builtin_judger on\n\
use_builtin_checker lcmp\n\
n_tests %d\n\
n_ex_tests 0\n\
n_sample_tests 0\n\
input_pre %s\n\
input_suf in\n\
output_pre %s\n\
output_suf %s\n\
time_limit %d\n\
memory_limit %d",
	R-L+1,qz.c_str(),qz.c_str(),suf.c_str(),TL,ML);
	fclose(fp);
	string tozip;
#ifdef _WIN32
	tozip = "\"C:\\Program Files\\WinRAR\\winrar.exe\" a uoj_data.zip uoj_data";
#endif
/* 
#ifdef __linux__
	tozip = "zip -r uoj_data.zip uoj_data";
#endif
*/
//	cout << tozip << "\n";
	system(tozip.c_str());
	puts("UOJ data ported successfully");
}
