#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cassert>
#include <climits>
#include <algorithm>

using std::max;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::deque;
using std::string;
using std::vector;
typedef long long int lli;

struct sol {
  size_t cost;
  lli prev;
  lli loc;
  sol() {
    cost = 0;
    loc = -1;
    prev = -1;
  }
};

void
add_sol(const size_t w, deque<sol> &helper, sol &cand) {
  // removes solutions that will no longer be selected
  while (!helper.empty() && helper.back().cost > cand.cost)
    helper.pop_back();

  // add the current solution
  helper.push_back(cand);
  assert(helper.size() <= w+1);
}

// removes solutions that are now outside of the window
void
clean_sol(const size_t w, const size_t new_loc, deque<sol> &helper) {
  // solutions outside of window w
  while(helper.front().loc + w < new_loc)
    helper.pop_front();

  assert(!helper.empty());
}

void
solve(const vector<size_t> &costs, const size_t &w,
      vector<bool> &s, size_t &ans) {
  static const size_t INF = std::numeric_limits<size_t>::max();


  const size_t m = costs.size();
  vector<sol> dp(m);
  deque<sol> helper;
  for (size_t i = 0; i < w; ++i) {
    dp[i].cost = costs[i];
    dp[i].loc = i;
    dp[i].prev = -1;
    add_sol(w, helper, dp[i]);
  }

  for (size_t i = w; i < m; ++i) {

    clean_sol(w, i, helper);

    dp[i].loc = i;
    dp[i].cost += helper.front().cost + costs[i];
    dp[i].prev = helper.front().loc;
    add_sol(w, helper, dp[i]);
  }

  // find the final answer
  lli fin = std::numeric_limits<lli>::max();
  ans = INF;
  for (size_t i = 0; i < w; ++i) {
    const size_t cand = dp[m - 1 - i].cost;
    if (cand < ans) {
      ans = cand;
      fin = m - 1 - i;
    }
  }


  // build traceback
  while (fin != -1) {
    s[fin] = true;
    fin = dp[fin].prev;
  }
}

int
main(int argc, const char **argv) {
  size_t m, w;
  cin >> m >> w;
  vector<size_t> costs (m, 0);
  for (size_t i = 0; i < m; ++i)
    cin >> costs[i];

  vector<bool> s (m, false);
  size_t ans;
  solve(costs, w, s, ans);

  for (size_t i = 0; i < m; ++i)
    cout << (s[i] ? ('*') : (' ')) << ' ' << costs[i] << '\n';

  cout << "FINAL COST: " << ans << endl;

  return EXIT_SUCCESS;
}
