#include <iostream>
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
 * The geometric information of each building is represented by a triplet of integers [Li, Ri, Hi],
 * where Li and Ri are the x coordinates of the left and right edge of the ith building, respectively,
 * and Hi is its height. It is guaranteed that 0 ¡Ü Li, Ri ¡Ü INT_MAX, 0 < Hi ¡Ü INT_MAX, and Ri - Li > 0.
 * You may assume all buildings are perfect rectangles grounded on an absolutely flat surface at height 0.
 * For instance, the dimensions of all buildings in Figure A are recorded as: [ [2 9 10], [3 7 15], [5 12 12], [15 20 10], [19 24 8] ]
 *
 * The output is a list of "key points" (red dots in Figure B) in the format of [ [x1,y1], [x2, y2], [x3, y3], ... ]
 * that uniquely defines a skyline. A key point is the left endpoint of a horizontal line segment.
 *
 * For instance, the skyline in Figure B should be represented as:[ [2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0] ].
 *
 *
 * Notes:
 * The number of buildings in any input list is guaranteed to be in the range [0, 10000].
 * The input list is already sorted in ascending order by the left x position Li.
 * The output list must be sorted by the x position.
 * There must be no consecutive horizontal lines of equal height in the output skyline.
 * For instance, [...[2 3], [4 5], [7 5], [11 5], [12 7]...] is not acceptable;
 * the three lines of height 5 should be merged into one in the final output as such: [...[2 3], [4 5], [12 7], ...]
 *
 */

class Solution {
public:
    vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {

    	vector<pair<int, int> > skyline, houses;

    	for( auto& b : buildings){
    		houses.push_back({b[0], -b[2]});
    		houses.push_back({b[1], b[2]});
    	}

    	sort(houses.begin(), houses.end()); //asc order,  if same location then heigher first.

    	multiset<int> m;  //little first, that is negative height.
    	m.insert(0);  //no need to test whether empty()

    	int prev = 0;
    	int cur = 0;

    	for( auto& h : houses){
    		if( h.second<0 )  m.insert(h.second);
    		else m.erase(m.find(-h.second));

    		cur = -*m.begin();  //positive height!

    		if( prev != cur ){
    			skyline.push_back({h.first,cur});
    			prev = cur;
    		}
    	} //end of for
    	return skyline;
    }
};

/**
 *
 */
void start_leecode_p218_skyline()
{
	Solution solution;

//	int input[3][3] = {{1,2,1},{1,2,2},{1,2,3}};
	vector<vector<int> > buildings = {{1,2,1},{1,2,2},{1,2,3}};

//	vector<int> a1(input[0],input[1]), a2(input[1],input[2]), a3(input[2],input[3]);
//
//	vector<vector<int>> buildings;
//
//	buildings.push_back(a1);
//	buildings.push_back(a2);
//	buildings.push_back(a3);

	vector<pair<int, int>> skyline = solution.getSkyline(buildings);

	for(auto& p : skyline){
		cout<< "["<<p.first<<" "<<p.second<<"] ";
	}
	cout<<endl;
}
