/*
 * ali_largestnumber_string.cxx
 *
 *  Created on: 2017年3月19日
 *      Author: wang
 */
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <map>
#include <random>
#include <cmath>
#include <vector>
#include <map>
#include <queue>          // std::priority_queue
#include <algorithm>    // std::sort
#include <set>
#include <functional>


using namespace std;

/**
 * 有n个正整数(每个数小于10亿)， 将它们表示成字符串形式，
 * 对每个字符串s, 可以翻转为新字符串s',例如"1234"可以翻转为"4321"。
 * 现在，将这n个字符串以任意顺序连成一个字符环，每个字符串可以选择是否翻转。
 * 在字符环中，从任意一个位置开始，遍历整个环，得到一个长整数。请问，如何才能得到最大的长整数。
 *
 * 1) 将一个整数变成字符串环，找出这个环的最大整数
 * 2) 对每个整数的构造上述最大整数，从中选出最大数, 这个数的第一个字符就是环的起始字符
 * 3) 对剩下的依次判断，从上述的最大数中的哪个地方断开即可。
 *
 */

string int2str(int v){
	stringstream ss;
	ss<<v;
	return ss.str();
}
int str2int(string s){
	int v;
	stringstream ss;
	ss<<s;
	ss>>v;
	return v;
}

struct LargeNum{
	int num, rnum;
	string numstr;

	int buildmaxringnum(string s){
		char ch = '0' ; //max char
		for(auto& c : s){
			if( c > ch ) ch = c;
		}

		string rstr = s;
		for(unsigned int i = 0;i<s.length();i++){//find largest ring num!
			if( s[i] == ch ){
				string smid;
				if( i< s.length()-1) {
					smid = s.substr(i+1, s.length()-i-1);
				}
				if( i>0 ){
					smid += s.substr(0,i);
				}
				if( rstr.compare(s[i] + smid) <0 ){
					rstr = s[i] + smid;
				}
				std::reverse(smid.begin(),smid.end());
				if( rstr.compare(s[i] + smid) <0 ){
					rstr = s[i] + smid;
				}
			}
		}
		return str2int(rstr); //get the largest ring num!
	}
	LargeNum(int v){//construct function!
		string s = int2str(v);
		string s2 = s;
		std::reverse(s2.begin(), s2.end());

		int v2 = str2int(s2);
		if( v < v2 ){
			num = v2;
			numstr = s2;
		}else{
			num = v;
			numstr = s;
		}
		rnum = buildmaxringnum(numstr);
	}
}; // end of struct LargeNum!!

class Solution {
public:

	string buildLargestNumber(vector<int> & nums){

		string largestnum;
		int rnum = 0;
		unsigned int i = 0;
		vector<LargeNum> lnums;

		for(i=0;i<nums.size();i++){
			LargeNum l = LargeNum(nums[i]);
			if( rnum < l.rnum ) {
				rnum = l.rnum;
			}
		}

		vector<int> vnums(nums.size()-1);
		for(auto& ln : lnums){
			if( rnum != ln.rnum ){
				vnums.push_back(ln.num);
			}
		}
		std::sort(vnums.begin(),vnums.end(),std::greater<int>()); //

		string s1,s2;
		for(auto& v : vnums){
			s1 += int2str(v);
		}
		s2 = int2str(rnum);

		for(i=0;i<s1.length() && i<s2.length();i++){

		}

		return largestnum;
	}


};

void start_ali_bignum_ring_string()
{
	int v = 719191913;
	LargeNum n(v);
	cout<<n.num<<" "<<n.numstr<<" "<<n.rnum<<endl;
}

