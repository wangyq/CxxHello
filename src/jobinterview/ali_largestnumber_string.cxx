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
	string findmaxringnum(string s1, string s2, string mstr){ //start from s1, can split
		for(unsigned int i = 0; i<s1.length();i++){
			string smid, tmp;
			smid += s1[i];
			if( i< s1.length()-1) {
				smid += s1.substr(i+1, s1.length()-i-1);
			}
			smid += s2;
			if( i>0 ){
				smid += s1.substr(0,i);
			}
			if( mstr.compare(smid) < 0 ) mstr = smid;
		}
		return mstr; //
	}
	bool isRingFirst(string s1, string s2){ //compare who is the first!
		string ms1 = findmaxringnum(s1,s2,"");
		std::reverse(s1.begin(),s1.end());
		ms1 = findmaxringnum(s1,s2, ms1);

		string ms2 = findmaxringnum(s2,s1, "");
		std::reverse(s2.begin(),s2.end());
		ms2 = findmaxringnum(s2,s1, ms2);

		if( ms1 < ms2 ) return false;
		return true;
	}
	/**
	 *
	 */
	string buildLargestNumber(vector<int> & nums){
		struct ringstr_cmp{
			bool operator()(const string & s1, const string & s2) const{
				return (s1+s2) > (s2+s1);
			}
		};
		vector<string> numstr;
		for(auto& v: nums ){ //preprocessor for vector!
			string s1 = std::to_string(v);
			string s2 = string(s1.rbegin(),s1.rend());

			if( s1 < s2 ) numstr.push_back(s2); //
			else numstr.push_back(s1); //
		}
		sort(numstr.begin(),numstr.end(),ringstr_cmp());// desc order
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
		string ss = findmaxringnum(rstr,midstr, "");
		std::reverse(rstr.begin(),rstr.end());
		ss = findmaxringnum(rstr,midstr, ss);
		return ss;
	}


};

void start_ali_bignum_ring_string()
{
	Solution so;
	vector<int> nums = {1,2,3,4,5,6,7,8,9,0};
	//vector<int> nums = {9,101};
	//vector<int> nums = {3,30,34,5,9};
	//vector<int> nums = {123,494,878};
	//vector<int> nums = {92,28,19};
	//vector<int> nums = {193,245};
	//vector<int> nums = {719191913};
	cout<< so.buildLargestNumber(nums)<<endl;
}

