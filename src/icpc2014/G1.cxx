#include <string>
#include <cmath>
#include <iostream>
#include <iomanip>

using namespace std;

typedef long long INT;

void G1_Case()
{
	INT s = 0,x0,y0,r,x1,y1,x2,y2;
	INT x,y, num=0; 
	INT a,b,c[2],i,tmp; 

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

	if( x1 == x2 ){
		if( s % (y2-y1) == 0 ){
			c[0] = x1 + s/(y2-y1);
			c[1] = x1 - s/(y2-y1);
			
			for(i=0;i<2;i++){
				tmp = c[i]; //make sure the height is positive!
				if ( tmp<0 ) tmp = -tmp;
				if( tmp > r ) continue; //no solution
				
				//double u = acos((double)tmp/r);
				//INT range = r*sin(u) + 1;
				
				//INT range = sqrt(r*r - tmp*tmp);  //maybe wrong here!
				INT range = (tmp==0)?r:sqrt(r*r - tmp*tmp)+1;
				do{
					if( range*range + tmp*tmp <= r*r ) break;
					if( range <0 ) break;
					range --;
				}while(true);	
				if( range>=0 ) num += (range<<1) + 1;
				
			}

		}
	} else{
		c[0] = x2*y1 - x1*y2 - s;
		c[1] = x2*y1 - x1*y2 + s;
		a = y1 - y2; b = x2-x1;

		for(x=-r; x<=r;x++){ // ax+by = c 
			for(i=0;i<2;i++){
				tmp = c[i] - a*x;
				if( tmp % b == 0 ){ //may be answer!
					y = tmp / b;
					if( y<-r || y>r ) continue;
					if( x*x + y*y <= r*r ){
						num ++;
					}
				}
			}
		}
	}
	cout<<num<<endl;

}

//int main()
int G1()
{
        INT numCases = 0;
        cin >> numCases;
        while(numCases -- > 0){
                G1_Case();
        }
        return 0;
}

