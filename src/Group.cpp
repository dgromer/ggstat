#include <Rcpp.h>
#include "Group.h"
using namespace Rcpp;

template<class Group>
List groupInfo(Group* pGroup, NumericVector x) {
  int n = x.size();
  IntegerVector out(n);

  for (int i = 0; i < n; ++i) {
    out[i] = pGroup->bin(x[i]);
  }

  return List::create(
    _["x"] = out,
    _["nbins"] = pGroup->nbins(),
    _["bins"] = pGroup->outColumns()
  );
}

// [[Rcpp::export]]
List group_fixed(NumericVector x, double width, double min, double max,
                 bool pad = false, bool right_closed = false) {
  GroupFixed grp(width, min, max, pad, right_closed);
  return groupInfo(&grp, x);
}

// [[Rcpp::export]]
List group_variable(NumericVector x, std::vector<double> breaks,
                    bool right_closed = false) {
  GroupVariable grp(breaks, right_closed);
  return groupInfo(&grp, x);
}
