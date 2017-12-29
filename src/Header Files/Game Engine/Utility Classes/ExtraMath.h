#ifndef EXTRA_MATH
#define EXTRA_MATH

#include <cmath>

const long double EM_PI = 3.141592653589793238L;

template<typename T>
inline T toDegrees(T radians) {
	return (radians * ((T)180 / (T)EM_PI));
}

template <typename T>
inline T toRadians(T degrees) {
	return (degrees * ((T)EM_PI / (T)180));
}

template<typename T>
T fixDegrees(T degrees) {
	T posDegrees = degrees;

	while (posDegrees < (T)0) {
		posDegrees += (T)360;
	}
	
	while (posDegrees >= (T)360) {
		posDegrees -= (T)360;
	}

	return posDegrees;
}

template<typename T>
T smartSin(T degrees) {
	T fixedDegrees = fixDegrees<T>(degrees);
	return (fixedDegrees == (T)0 || fixedDegrees == (T)180) ? (T)0 :
		(fixedDegrees == (T)90) ? (T)1 :
		(fixedDegrees == (T)270) ? (T)-1 :
		(T)sin(toRadians<T>(fixedDegrees));
}

template<typename T>
T smartCos(T degrees) {
	T fixedDegrees = fixDegrees<T>(degrees);
	return (fixedDegrees == (T)90 || fixedDegrees == (T)270) ? (T)0 :
		(fixedDegrees == (T)0) ? (T)1 :
		(fixedDegrees == (T)180) ? (T)-1 :
		(T)cos(toRadians<T>(fixedDegrees));
}

//Returns dot product.
template<typename T>
inline T dotProduct(T x1, T z1, T x2, T z2) {
	return (x1 * x2) + (z1 * z2);
}

//Returns angle in radians.
template<typename T>
T angleBetweenVectors(T x1, T z1, T x2, T z2) {
	double dP = (double)dotProduct(x1, z1, x2, z2);
	double mag1 = sqrt((double)((x1 * x1) + (z1 * z1)));
	double mag2 = sqrt((double)((x2 * x2) + (z2 * z2)));
	return toDegrees<T>((T)acos(dP / (mag1 * mag2)));
}

#endif