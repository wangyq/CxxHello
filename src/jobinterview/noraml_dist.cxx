#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>


/* ====================================
 * heart curve : (x^2 + y^2 -1)^3  - x^2 * y^3 = 0
 *
 * Point(X,Y): X~N(mu1,sigma1), Y~N(mu2, sigma2)
 *
*/
double heartlove(double mu1,double sigma1, double mu2,double sigma2)
{
    double value = 0.0f;
    int hit=0, count=100000;

    std::random_device rd;
    std::mt19937 gen1(rd()), gen2(rd());

    std::normal_distribution<> XX(mu1,sigma1), YY(mu2,sigma2); // normal variable of (X,Y)

    for(int i=0;i<count;i++)
    {
    	double x = XX(gen1);
    	double y = YY(gen2);

    	//if( x >=2.0 || x <=-2.0 ) continue;
    	//if( y >=2.0 || y < -1.0 ) continue;

    	double f1 = x*x;
    	double f2 = f1 + y*y -1;
    	double f = f2*f2*f2 - f1*y*y*y;

    	if( f > 0.0 ) continue;

    	//now hit
    	hit++;
    }

    value = double(hit)/count;

    return value;
}
/**
 * (x^2 + y^2 -1)^2  - x^2 * y^2 = 0
 */
double Ovallove(double mu1,double sigma1, double mu2,double sigma2)
{
    double value = 0.0f;
    int hit=0, count=10000000;

    std::random_device rd;
    std::mt19937 gen1(rd()), gen2(rd());

    std::normal_distribution<> XX(mu1,sigma1), YY(mu2,sigma2); // normal variable of (X,Y)

    for(int i=0;i<count;i++)
    {
    	double x = XX(gen1);
    	double y = YY(gen2);

    	double f1 = x*x + y*y -1;
    	double f2 = x*y;

    	if( f1 + f2  > 0.0 && f1 -f2 >0.0 ) continue;

    	//now hit
    	hit++;
    }

    value = double(hit)/count;

    return value;
}


void start_heartlove_proberbility(){
	using namespace std;
	double v = heartlove(0.0,1.0, 0.0,2.0);
	cout <<"heartlove: "<<v<<endl;
	cout<<"ovallove:" << Ovallove(0,1,0,1)<<endl;
	cout<<"ovallove:" << Ovallove(2,2,2,2)<<endl;
}

