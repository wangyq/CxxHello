/*
 * P179_LargestNumber.cxx
 *
 *  Created on: 2017年3月18日
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

using namespace std;

/**
 * Given a list of non negative integers, arrange them such that they form the largest number.
 * For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330.
 * Note: The result may be very large, so you need to return a string instead of an integer.
 */

class Solution {
public:
	string largestNumber(vector<int>& nums) {
		struct bignum_cmp {
			bool operator ()(const string & x, const string & y) const {
				return (x + y) > (y + x);
			}
		};
		//
		vector<string> snum;
		for (auto& v : nums) {
			snum.push_back(std::to_string(v));
		}
		sort(snum.begin(), snum.end(), bignum_cmp()); //

		string strnum = "";
		for (auto & s : snum) {
			strnum += s;
		}
		unsigned int i;
		for (i = 0; i < strnum.length(); i++) {
			if (strnum[i] != '0') break;
		}
		if (i >= strnum.length()) strnum = "0";
		return strnum;

	}
	string largestNumber00(vector<int>& nums) {
		struct bignum_cmp {
			bool operator ()(const string & x, const string & y) const {
				return (x + y) < (y + x);
			}
		};

		string largestnum; //return value!
		priority_queue<string, vector<string>, bignum_cmp> queue; //compare value!

		stringstream ss;
		for (auto& v : nums) { //get string of int
			ss << v;
			queue.push(ss.str());
			ss.str("");  //clear it's content!
		}

		while (!queue.empty()) {
			largestnum += queue.top();
			queue.pop();
		}

		unsigned int i = 0;
		// check for "000...000"
		for (i = 0; i < largestnum.length(); i++) {
			if (largestnum[i] != '0')
				break;
		}
		if (i >= largestnum.length())
			largestnum = "0";
		return largestnum;

	}

	string largestNumber000(vector<int>& nums) {

		struct bignum_cmp {
			bool operator ()(const string & x, const string & y) {
				string str1 = x + y, str2 = y + x;
				return str1 < str2;
			}
		};

		string largestnum; //return value!
		priority_queue<string, vector<string>, bignum_cmp> queue; //compare value!

		//get string of int
		unsigned int i = 0;
		for (auto v : nums) {
			string s;
			if (v == 0) {
				s = "0";
			} else {
				while (v > 0) {
					char ch = '0' + v % 10;
					s += ch;
					v /= 10;
				}
			}
			//reverse string
			for (i = 0; i < s.length() / 2; i++) {
				char c = s[i];
				s[i] = s[s.length() - 1 - i];
				s[s.length() - 1 - i] = c;
			}

			queue.push(s);
		}

		while (!queue.empty()) {
			largestnum += queue.top();
			queue.pop();
		}

		// check for "000...000"
		for (i = 0; i < largestnum.length(); i++) {
			if (largestnum[i] != '0')
				break;
		}
		if (i >= largestnum.length())
			largestnum = "0";
		return largestnum;

	}
};

void start_leecode_p179_bignum() {
	Solution so;
	//vector<int> nums = { 3, 30, 34, 5,9 };
	//vector<int> nums = { 626, 62648, 6261, 6267, 6266 };
	vector<int> nums = { 0, 0 }; //{ 1,2,3,4,5,6,7,8,9,0,0};

	string str = so.largestNumber(nums);

	cout << str << endl;
}

