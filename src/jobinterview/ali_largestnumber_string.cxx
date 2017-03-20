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


class Solution {
public:

	/**
	 * no need now!
	 * can call with findmaxringnum(s, "");
	 */
	string findmaxringnum(string s){

		string rstr = s;
		for(unsigned int i = 0;i<s.length();i++){//find largest ring num!
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
		}//end of for!
		return rstr; //get the largest ring num!
	}
	string findmaxringnumfromstartchar(string s1, string s2){ //start from s1, can split
		string rstr = "";
		unsigned int i = 0;
		for( i=1;i<s1.length() && i<=s2.length();i++){
			if( s1[i] >= s2[i-1] ) continue;
			else{
				rstr = s1.substr(0, i);
				rstr += s2;
				rstr += s1.substr(i, s1.length() - i);
				break;
			}
		}//end of for
		if( rstr.length() == 0 ){
			rstr = s1 + s2;
		}
		return rstr;//
	}
	string findmaxringnum(string s1, string s2){ //start from s1, can split
		string rstr = "";
		for(unsigned int i = 0; i<s1.length();i++){
			string smid , tmp;
			if( i< s1.length()-1) {
				smid = s1.substr(i+1, s1.length()-i-1);
			}
			if( i>0 ){
				smid += s1.substr(0,i);
			}
			tmp = findmaxringnumfromstartchar(s1[i] + smid,s2);
			if( rstr < tmp ) rstr = tmp;
			std::reverse(smid.begin(),smid.end());
			tmp = findmaxringnumfromstartchar(s1[i] + smid,s2);
			if( rstr < tmp ) rstr = tmp;
		}
		return rstr; //
	}
	bool isRingFirst(string s1, string s2){ //compare who is the first!
		string ms1 = findmaxringnum(s1,s2);
		string ms2 = findmaxringnum(s2,s1);
		if( ms1 < ms2 ) return false;
		return true;
	}
	/**
	 *
	 */
	string buildLargestNumber(vector<int> & nums){

		vector<string> numstr;
		for(auto& v: nums ){ //preprocessor for vector!
			string s1 = std::to_string(v);
			string s2 = string(s1.rbegin(),s1.rend());

			if( s1 < s2 ) numstr.push_back(s2); //
			else numstr.push_back(s1); //
		}
		sort(numstr.begin(),numstr.end(),std::greater<string>());// desc order
//		if( numstr.size() == 1 ){ //only one number!
//			return findmaxringnum(numstr[0]);
//		}

		string rstr = "";
		for(auto& v : numstr ){
			if( isRingFirst(v, rstr) ) rstr = v; //find the first ring number!
		}

		string midstr = "";
		for(auto& v : numstr){
			if( rstr.compare(v) == 0 ) continue;
			midstr += v;
		}

		return findmaxringnum(rstr,midstr);
	}


};

void start_ali_bignum_ring_string()
{
	Solution so;
	vector<int> nums = {1,2,3,4,5,6,7,8,9,0};
	//vector<int> nums = {123,494,878};
	//vector<int> nums = {92,28,19};
	//vector<int> nums = {719191913};
	cout<< so.buildLargestNumber(nums)<<endl;
}

