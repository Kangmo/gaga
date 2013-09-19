

#ifndef UTIL_H_
#define UTIL_H_

class Util {

public :
	static const int RANDOM_SEED = 179425237; // A prime number.
	static const int RANDOM_DIVIDEND = 179426549; // Another prime number.

	static float random() {
		static int seed = RANDOM_SEED;
		static int invoked_count = 0;
		seed = (seed * invoked_count++) % RANDOM_DIVIDEND;
		return (float) ( seed ) / (float) RANDOM_DIVIDEND;
	}

	static int abs(int a) {
		return (a>0) ? a : -a;
	}
};

#endif
