
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

void I_Case()
{
	int n,i, p;
	double H = 0,A=0,B=0, b_log; 
	string strBase;
	cin>>n>>strBase;
	for(i=0;i<n;i++){
		cin>>p;
		if( p == 0 ) continue; //for 0 !
		A += p*log(p);
		B += p;
	}
	if( strBase == "bit" ){
		b_log = log(2);
	} else if( strBase == "dit" ){
		b_log = log(10);
	} else { //nat
		b_log = 1.0;
	}
	
	H = (B*log(100)-A)/(100*b_log);
	cout<<setprecision(12)<<setiosflags(ios::fixed)<<H<<endl;	
}


//int main()
int I()
{
	int numCases = 0;
	cin >> numCases;
	while(numCases -- > 0){
		I_Case();
	}

	return 0;
}

