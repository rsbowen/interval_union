#include <vector>

struct IntervalUnion {
  struct Bound {
    bool is_lower_;
    double location_;
  };
  std::vector<Bound> bounds_;
 
  void add(double lb, double ub);
  void max_point(double* pt, int* votes);
};
