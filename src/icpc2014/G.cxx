
#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long INT;
//typedef int INT;

INT gcd(INT a, INT b, INT* x, INT* y)
{
	INT r, q;
	INT u[3],v[3];
	
	bool a_sign = false, b_sign = false;
	bool exchange = false;

	if( a<0 ) {
		a = -a; a_sign = true; 
	}
	if( b<0 ) {
		b = -b; b_sign = true;
	}
	//make sure a >= b >= 0;
	if( a < b ){
		r = a; a = b; b=r;
		exchange = true;
		//cout <<"exchange"<<endl;
	}

	u[0] = 1,v[0] = 0; //for a
	u[1] = 0,v[1] = 1; //for b
	

	while(b>0){ //b==0 , is the answer
		r = a%b;
		q = a/b;
		a = b;
		b = r;
		u[2] = u[0] - u[1]*q;  // a-bq
		v[2] = v[0] - v[1]*q;  
		u[0] = u[1]; u[1] = u[2];
     		v[0] = v[1]; v[1] = v[2]; //
		//cout<<u[0]<<","<<v[0]<<" "<<u[1]<<","<<v[1]<<" "<<u[2]<<","<<v[2]<<endl;
	}
	if( exchange ){
		*x = v[0]; *y = u[0];
		//cout<<"using exchange"<<endl;
	}else{
		*x = u[0]; *y = v[0];
		//cout<<"NOT! using exchange"<<endl;
	}
	if( a_sign ) *x = -(*x);
	if( b_sign ) *y = -(*y);
	return a;
}

bool get_root(INT A,INT B,INT C, INT* low, INT* high)
{
	//assume a >0
	double a = A, b = B, c = C, dt;
	if( A<0 ){
		a = -a; b=-b; c=-c;
	}
	dt = b*b - 4*a*c;
	if( dt < 0 ) return false;
	
	double l,h,tmp;
	tmp = (C==0)?fabs(b):sqrt(dt); //caution
	l = (-b - tmp)/(2*a);
	h = (-b + tmp)/(2*a);
	
	*low = INT(l)-1;
	*high = INT(h)+1;

	return true;
}
INT normalCase(INT a, INT b, INT c, INT g, INT x0, INT y0,INT r)
{//make sure has solution!

	INT res = 0;
	INT p,q;

	if( c%g != 0 ) return res; //
	
	x0 *= c/g; y0 *= c/g;
	p = b/g; q = -a/g;
	INT t1,t2;
	if( get_root(p*p + q*q, 2*(p*x0 + q*y0), x0*x0 + y0*y0 - r*r, &t1,&t2) ){
		do{
			INT x = x0 + p*t1, y = y0 + q*t1;
			if( x*x + y*y <= r*r ) break;
			if( t1 > t2 ) break;
			t1 ++;
		}while(true);
		do{
			INT x = x0 + p*t2, y = y0 + q*t2;
			if( x*x + y*y <= r*r ) break;
			if( t1 > t2 ) break;
			t2 --;
		}while(true);
		if( t1 <=t2 ) res = t2-t1 + 1;
	}

	return res;
}
void G_Case()
{

	INT s = 0,x0,y0,r,g, x1,y1,x2,y2;
	INT num=0;
	INT A,B,C[2],tmp,i;
	
	cin>>s;
	cin>>x0>>y0>>r;
	cin>>x1>>y1>>x2>>y2;

	//translation
	x1 -= x0; y1 -= y0;
	x2 -= x0; y2 -= y0;
	
	if( y1 == y2 ){ //exchange value!
		tmp = x1; x1 = y1; y1 = tmp;
		tmp = x2; x2 = y2; y2 = tmp;
	}

	if( x1 == x2 ){ //special case!
		if( s % (y2-y1) == 0 ){
			C[0] = x1 - s/(y2-y1);
			C[1] = x1 + s/(y2-y1);
			
			for(i=0;i<2;i++){
				tmp = C[i]; //make sure the height is positive!
				if( tmp <0 ) tmp = -tmp;
				if ( tmp>r ) continue; //no solution
				INT t = (tmp==0)?r:(INT)sqrt(r*r - tmp*tmp) + 1;
				do{
					if( t*t + tmp*tmp <= r*r ) break;
					if( t<0 ) break;
					t --;
				}while(true);
				if( t>=0 ) num += 2*t + 1;
				//INT t = (tmp==0)?r:sqrt(r*r - tmp*tmp);
				//num += t*2 + 1;
			}

		}
	} else{
		A = y1 - y2;
		B = x2 - x1;
		tmp = x2*y1 - x1*y2; 
		C[0] = tmp - s; //x2*y1 - x1*y2 - s ;
		C[1] = tmp + s; //x2*y1 - x1*y2 + s ;

		g = gcd(A,B,&x0,&y0);

		for(i=0;i<2;i++){
			if( C[i] % g == 0 ) num += normalCase(A,B,C[i],g,x0,y0,r);
		}
	}
	
	cout<<num<<endl;
	
}

//int main()
int G()
{

        int numCases = 0;
        cin >> numCases;
        while(numCases -- > 0){
                G_Case();
        }

        return 0;
}
