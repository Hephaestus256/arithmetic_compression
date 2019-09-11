//
//  main.cpp
//  arithmetic_coding
//
//  Created by Nathan Smith on 9/18/17.
//  Copyright © 2017 Nathan Smith. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

// arithmetic coding
template <class gen = double, int range = 256>
class arith_code {
public:
	vector<gen> tops;
	gen min;
	gen max;
	gen top;
	gen bot;
	
	void init (int* p_freqs)
	{
		int total = 0;
		int ct = 0;
		
		for (int i = 0; p_freqs[i] > 0; ++i) {
			total += p_freqs[i];
			ct++;
		}
		
		gen a = 0.0;
		gen n;
		
		for (int i = 0; i < ct; ++i) {
			n = (gen)p_freqs[i] / (gen)total;
			a += n;
			tops.push_back(a);
		}
		
		reset();
	}
	
	void reset()
	{
		bot = min = 0.0;
		top = max = 1.0;
	}
	
	arith_code (int* p_freqs)
	{
		init(p_freqs);
	}
	
	void encode (int index, bool last = false)
	{
		gen a, b;
		
		if (index == 0) {
			a = 0.0;
		} else {
			a = tops[index - 1];
		}
		b = tops[index];
	
		gen u = top - bot;
		top = u * b + bot;
		bot = u * a + bot;
		
		bool cont;
		do {
			top -= min;
			bot -= min;
			max -= min;
			min = 0.0;

			if (max <= gen(1) / gen(range)) {
				top *= gen(range);
				bot *= gen(range);
				max = gen(1.0);
			}
			
			gen mid = max * 0.5;
			int bit;
			
			if (last) {
				gen m = (top + bot) * 0.5;
				
				if (mid > m) {
					bit = 0;
					max = mid;
				} else {
					bit = 1;
					min = mid;
				}
				
				cont = min < bot || max > top;
			} else {
				if (mid > top) { // mid is over top
					bit = 0;
					max = mid;
					cont = true;
				} else if (mid < bot) { // mid is under bot
					bit = 1;
					min = mid;
					cont = true;
				} else { // mid hits range
					bit = -1;
					cont = false;
				}
			}
			
			if (bit != -1)
				cout << "(" << bit << ") ";
			
			cout << "min: " << min << " max: " << max << " mid " << mid << " top: " << top << " bot: " << bot << endl;
		} while (cont);
		
		cout << endl;
		getchar();
	}
	
};

int main(int argc, const char * argv[]) {
	
	int freqs[] = {2, 5, 3, 8, 12, 43, 77, 2, 5, 30, 1, 9, -1}; // sum = 197
	//int freqs[] = {5, 5, 5, -1};
	
	arith_code<> ac(freqs);
	
	ac.encode(3, false);
	ac.encode(5, false);
	ac.encode(2, false);
	ac.encode(6, false);
	ac.encode(9, false);
	ac.encode(2, false);
	ac.encode(3, false);
	ac.encode(7, false);
	ac.encode(2, false);
	ac.encode(3, false);
	ac.encode(5, false);
	ac.encode(2, false);
	ac.encode(6, false);
	ac.encode(11, false);
	ac.encode(2, false);
	ac.encode(10, false);
	ac.encode(3, false);
	ac.encode(2, false);
	ac.encode(7, false);
	ac.encode(2, false);
	ac.encode(3, false);
	ac.encode(5, false);
	ac.encode(2, false);
	ac.encode(6, false);
	ac.encode(11, false);
	ac.encode(2, false);
	ac.encode(6, false);
	ac.encode(11, false);
	ac.encode(2, false);
	ac.encode(10, false);
	
	// final cleanup
	ac.encode(1, true);
	
	/*
	int i = 0;
	for (; freqs[i + 1] != -1; ++i) {
		//cout << "(" << i << "), " << endl;
		//ac.reset();
		ac.encode(i, false);
		//ac.encode(i, true);
	}
	//ac.reset();
	ac.encode(i, true);
	*/
	
	cout << endl;
	return 0;
}
