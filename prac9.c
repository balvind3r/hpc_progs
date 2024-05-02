#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SEED 357952 // Modify for different random number sequences (optional)

double calculate_pi(long int num_points) {
  long int num_in_circle = 0;
  double x, y;

  // Initialize random number generator with a seed (optional for reproducibility)
  srand(SEED);

  #pragma omp parallel private(x, y) reduction(+:num_in_circle)
  {
    // Generate random points within a square of side length 2
    for (long int i = 0; i < num_points; i++) {
      x = (double)rand() / RAND_MAX;
      y = (double)rand() / RAND_MAX;

      // Check if the point falls inside the circle with radius 1
      if (x * x + y * y <= 1.0) {
        num_in_circle++;
      }
    }
  }

  // Estimate PI using the ratio of points inside the circle to total points
  double pi_estimate = 4.0 * ((double)num_in_circle / (double)num_points);

  return pi_estimate;
}

int main(int argc, char* argv) {
  long int num_points = 1000000; // Modify as needed for desired accuracy

  // Get the number of threads available
  int num_threads = omp_get_max_threads();
  printf("Using %d threads for calculation.\n", num_threads);

  double pi = calculate_pi(num_points);

  printf("Estimated value of PI/Area of Circle: %.10lf\n", pi);

  return 0;
}

