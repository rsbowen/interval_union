#include <iostream>
#include <algorithm>
#include <cmath>

#include "interval_union.h"

int main() {
  int votes;
  double midpoint;
  IntervalUnion iu;
  // Overlapping
  iu.add(0,1);
  iu.add(-1,2);

  iu.max_point(&midpoint, &votes);
  std::cout << "Should be 0.5: " << midpoint << std::endl;
  std::cout << "Should be 2: " << votes << std::endl;

  // Partial overlap
  IntervalUnion iu2;
  iu2.add(0,2);
  iu2.add(1,3);
  iu2.max_point(&midpoint, &votes);
  std::cout << "Should be 1.5: " << midpoint << std::endl;
  std::cout << "Should be 2: " << votes << std::endl;

  // Slightly more complex case.
  IntervalUnion iu3;
  iu3.add(0,2);
  iu3.add(3,4);
  iu3.add(1,3);
  iu3.add(0,4);
  iu3.max_point(&midpoint, &votes);
  std::cout << "Should be 1.5: " << midpoint << std::endl;
  std::cout << "Should be 3: " << votes << std::endl;

  // Random examples.
  std::cout << "Running random tests" << std::endl;
  for(int n = 2; n<50; ++n) {
    for(int randex = 0; randex < 1000; ++randex) {
      IntervalUnion iu4;
      std::vector<double> endpoints;
      for(int i = 0; i<n; ++i) {
        endpoints.push_back(2*i);
        endpoints.push_back(2*i + 1);
      }
      std::random_shuffle(endpoints.begin(), endpoints.end());
      for (int i = 0; i < n; ++i) {
        iu4.add(std::min(endpoints[2*i], endpoints[2*i+1]), std::max(endpoints[2*i], endpoints[2*i+1]));
      }
  
      int expected_votes = 0;
      double expected_midpoint = 0;
      for(int i = 0; i < 2*n-1; ++i) {
        double midpoint_here = i + 0.5;
        int score = 0;
        for(int j = 0; j < n; ++j) {
          if(midpoint_here < std::min(endpoints[2*j], endpoints[2*j+1])) continue;
          if(midpoint_here > std::max(endpoints[2*j], endpoints[2*j+1])) continue;
          ++score;
        }
        if (score > expected_votes) {
          expected_votes = score;
          expected_midpoint = midpoint_here;
        }
      }
  
      iu4.max_point(&midpoint, &votes);
      if(expected_votes != votes || std::abs(expected_midpoint-midpoint) > 0.1) {
        std::cout << n << "," << randex << std::endl;
        std::cout << "Should be " << expected_votes << ": " << votes << std::endl;
        std::cout << "Should be " << expected_midpoint << ": " << midpoint << std::endl;
        return 1;
      }
    }
  }

  return 0;
}
