#include "RLE.h"


string RLE(string RLE) {
	string comRLE;
	int count = 1;
	for (int i = 0; i < RLE.length(); i++) {
		if (RLE[i] == RLE[i + 1]) {
			count++;
		}
		else {
			comRLE += to_string(count);
			comRLE += RLE[i];
			count = 1;
		}
	}
	return comRLE;
}