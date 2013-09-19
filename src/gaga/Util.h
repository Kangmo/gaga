

#ifndef UTIL_H_
#define UTIL_H_

#include <cstdlib>
#include <time.h>
#include <iostream>
#include <Poco/Random.h>

class Util {

public :

	static float random() {
		static Poco::Random r;
		static bool initialized = false;
		if (!initialized) {
			r.seed(time(NULL));
			initialized = true;
		}

		float value = r.nextFloat();

//		std::cout << "["<< value <<"]";

		return value;
	}

	static int abs(int a) {
		return (a>0) ? a : -a;
	}
};

#endif
