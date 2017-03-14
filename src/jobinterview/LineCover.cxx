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

class Solution {

public:

	/**
	 * find all inputs lines's outline.
	 * the input lines is ordered as ascendent.
	 * each line's coordinate is greater than 0.
	 */
	vector<pair<int, int>> findOutline(vector<pair<int, int> > & lines) {
		vector<pair<int, int> > outline;

		if (lines.size() <= 0)
			return outline;

		sort(lines.begin(), lines.end());  //no need!

		int start = lines[0].first, end = lines[0].second; //
		for (auto& l : lines) { //==========
			if (l.first <= end) { //combine new line!
				if (l.second > end) {
					end = l.second;  //update end!
				} else {
					; //nothing to do!
				}
			} else { //l.first > end
				outline.push_back( { start, end });
				start = l.first;
				end = l.second;  //begin new line.
			}
		}

		outline.push_back( { start, end }); //last line!

		return outline;
	}

	/**
	 * find minimize cover of one segment line.
	 */
	vector<pair<int, int>> findMinSegmentCover(vector<pair<int, int> > & lines,
			pair<int, int> segment) {
		vector<pair<int, int> > cover;

		sort(lines.begin(), lines.end()); //sort!

		int x = segment.first, mid = x;
		bool bCover = false;
		for (unsigned int i = 0; i < lines.size(); i++) {
			if (lines[i].first <= x) { //cover ok!
				bCover = true; //
				mid = lines[i].second;
				if (mid >= segment.second) {
					cover.push_back(lines[i]); //
					break;  //already find solution;
				} else {
					;  //nothing to do!
				}
			} else {  //not find, cover again!
				if (bCover) {
					i--;
					cover.push_back(lines[i]);
					x = lines[i].second;
					mid = x;
					bCover = false;
				} else {
					break; //not found!
				}
			}
		}

		if (mid < segment.second) { //not found!
			cover.clear();
		}
		return cover;
	}

	/**
	 * 坐标轴上有两种线段，分别是黑线段和白线段，每种线段若干，其起止点坐标已知。
     * 求问如何选出最少的白线段，能够完全覆盖黑线段.
     * 如果不能覆盖，指出那条黑线段不能被覆盖。 (?)
	 */
	vector<pair<int,int> > findMinLinesCover(vector<pair<int,int> > & bLines, vector<pair<int,int> > &wLines){
		vector<pair<int,int> > cover ;

		sort(wLines.begin(),wLines.end());
		sort(bLines.begin(), bLines.end());
#if 0
		int i = 0, j = 0;
		unsigned int x = bLines[0].first, y = x;
		bool bCover = false;

		while( i<bLines.size() && j<wLines.size() ){
			if( wLines[j].first <= x ){
				bCover = true;
				if( wLines[j].second > y ){
					y = wLines[j].second; //
				}
			}
		}
#endif
		return cover;
	}
};

void start_linecover() {
	Solution s;
	//vector<pair<int,int>> lines = {{1,2},{1,2},{2,4},{3,7},{4,6},{8,10}};
	vector<pair<int, int>> lines = { { 1, 2 }, { 1, 3 }, { 3, 8 }, { 4, 6 }, {
			5, 8 }, { 16, 20 }, { 20, 22 } };
	pair<int, int> ss = { 1, 5 };

	vector<pair<int, int>> v = s.findOutline(lines);

	for (auto& l : v) {
		cout << "[" << l.first << "," << l.second << "] ";
	}
	cout << endl;

	v = s.findMinSegmentCover(lines, ss);

	for (auto& l : v) {
		cout << "[" << l.first << "," << l.second << "] ";
	}
	cout << endl;
}

