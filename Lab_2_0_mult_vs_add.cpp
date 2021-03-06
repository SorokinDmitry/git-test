#include <iostream>
#include <algorithm>
#include <omp.h>

const size_t N = 1000000;
const size_t repeats = 10000;
using std::min;
using std::max;


int main() {
	std::cout.precision(12);
	srand(omp_get_wtime());

	double *arr = new double[N]();
	for ( size_t i = 0; i < N; ++i ) {
		arr[i] = 1.0 + ( rand() ) / ( 0.9 * RAND_MAX ) * 0.001;
	}
	std::cout << "arr: " << arr[0] << " " << arr[1] << " ...\n";

	double t11 = omp_get_wtime();
	double add = 0;
	for ( size_t k = 0; k < repeats; ++k ) {
		double add_loc = 0;
		for ( size_t i = 0; i < N; ++i ) {
			add_loc += arr[i];
		}
		add = max(add, add_loc);
	}
	double t12 = omp_get_wtime();
	std::cout << " Time for add (s.): " << t12 - t11 << "\n";
	std::cout << " add = " << add << "\n\n";

	double t21 = omp_get_wtime();
	double mult = 1.0;
	for ( size_t k = 0; k < repeats; ++k ) {
		double mult_loc = 1.0;
		for ( size_t i = 0; i < N; ++i ) {
			mult_loc *= arr[i];
		}
		mult = max(mult, mult_loc);
	}
	double t22 = omp_get_wtime();
	std::cout << " Time for mult (s.): " << t22 - t21 << "\n";
	std::cout << " mult = " << mult << "\n\n";

	double t31 = omp_get_wtime();
	double frac = 1.0;
	for ( size_t k = 0; k < repeats; ++k ) {
		double frac_loc = 1.0;
		for ( size_t i = 0; i < N; ++i ) {
			frac_loc /= arr[i];
		}
		frac = min(frac, frac_loc);
	}
	double t32 = omp_get_wtime();
	std::cout << " Time for frac (s.): " << t32 - t31 << "\n";
	std::cout << " frac = " << frac << "\n\n";

	std::cout << " Total ( t_mult / t_add ): " << ( t22 - t21 ) / ( t12 - t11 ) << "\n";
	std::cout << " Total ( t_frac / t_add ): " << ( t32 - t31 ) / ( t12 - t11 ) << "\n";

	delete[] arr;
}