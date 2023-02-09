#include <iostream>
#include "big3.h"
using namespace std;
#include <vector>
#include <string>
#include <cmath>
#include <unordered_map>
#include <algorithm>
using namespace std;

int get_gcd(int a, int b) {
	while (true) {
		if (a == 0) {
			return b;
		}
		
		if (b == 0) {
			return a;
		}
		
		int temp = a;
		a = b;
		b = temp % a;
	}
}

string get_slope(vector<int> point_1, vector<int> point_2) {
	int delta_x = point_2[0] - point_1[0];
	int delta_y = point_2[1] - point_1[1];
	int gcd = get_gcd(std::abs(delta_x), std::abs(delta_y));
	
	string prev = "";
	if ((delta_x < 0) ^ (delta_y < 0)) {
		prev = "-";
	}
	string ans = prev + std::to_string(std::abs(delta_y) / gcd) + "/" + std::to_string(std::abs(delta_x) / gcd);
	
	return ans;
}

int lineThroughPoints(vector<vector<int>> points) {
  // Write your code here.
	int ans = 1;
	for (int i = 0; i < points.size(); i++) {
		unordered_map<string, int> hst;
		for (int j = 0; j < points.size(); j++) {
			if (i == j) {
				continue;
			}
			
			string slope = get_slope(points[i], points[j]);
			if (hst.find(slope) == hst.end()) {
				hst.insert({slope, 1});
			}
			hst[slope]++;

			
			ans = std::max(ans, hst[slope]);
		}
	}
  return ans;
}


int main()
{
	lineThroughPoints(vector<vector<int>>{{2,3},{3,3},{-5,3}});
    int _;
    cin >> _;
}
