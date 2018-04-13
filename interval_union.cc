#include "interval_union.h"

#include <algorithm>
#include <cassert>

void IntervalUnion::add(double lb, double ub) {
  assert(lb < ub);
  Bound b1;
  b1.is_lower_ = true;
  b1.location_ = lb;
  Bound b2;
  b2.is_lower_ = false;
  b2.location_ = ub;
  bounds_.push_back(b1);
  bounds_.push_back(b2);
}

void IntervalUnion::max_point(double* pt, int* votes) {
  assert(!bounds_.empty());
  std::sort(bounds_.begin(), bounds_.end(), [](Bound a, Bound b){return a.location_ < b.location_;});
  int num_in = 0;
  int max_num_in = 0;
  double midpoint = 0;
  for(int bound_idx = 0; bound_idx < bounds_.size() - 1; ++bound_idx) {
    if (bounds_[bound_idx].is_lower_) {
      ++num_in;
      if (!bounds_[bound_idx+1].is_lower_) {
        if (num_in > max_num_in) {
          max_num_in = num_in;
          midpoint = (bounds_[bound_idx].location_ + bounds_[bound_idx+1].location_) / 2;
        }
      }
    } else {
      --num_in;
    }
  }
*pt = midpoint;
*votes = max_num_in;
}
