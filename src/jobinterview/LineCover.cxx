/*
 * LineCover.cxx
 *
 *  Created on: 2017年3月13日
 *      Author: wang
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution{

	public:


	/**
	 * find all inputs lines's outline.
	 * the input lines is ordered as ascendent.
	 * each line's coordinate is greater than 0.
	 */
	vector<pair<int,int>> createLineOutline(vector<pair<int,int> > & lines){
			vector<pair<int,int> > outline;

			if( lines.size() <=0 ) return outline;

			sort(lines.begin(),lines.end());  //no need!

			int start = lines[0].first,end=lines[0].second; //
			for( auto& l: lines){//==========
				if( l.first <= end ){ //combine new line!
					if( l.second > end ) {
						end = l.second;  //update end!
					} else {
						; //nothing to do!
					}
				} else {//l.first > end
					outline.push_back({start,end});
					start = l.first;
					end = l.second;  //begin new line.
				}
			}

			outline.push_back({start,end}); //last line!

			return outline;
		}
};

void start_linecover(){
	Solution s;
	//vector<pair<int,int>> lines = {{1,2},{1,2},{2,4},{3,7},{4,6},{8,10}};
	vector<pair<int,int>> lines = {{1,2},{1,3}, {3,8},{4,6},{5,8},{16,20},{20,22}};

	vector<pair<int,int>> v = s.createLineOutline(lines);

	for(auto& l: v){
		cout<<"["<<l.first<<","<<l.second<<"] ";
	}
	cout<<endl;
}

