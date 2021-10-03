#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <cassert>
#include <climits>
#include <algorithm>
#include <bitset>

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

// check if mask doesn't have a >w  consecutive run of zeros
bool
valid(const size_t m, const size_t w, size_t mask) {
  size_t zero_run = 0;
  for (size_t i = 0; i < m; ++i) {
    zero_run = (mask & 1) ? (0) : (zero_run + 1);
    if (zero_run >= w) return false;
    mask >>= 1;
  }

  return true;
}

// brute force solve to compare with dp and make sure dp is correct
// for m from 1 to about 25, 26.
void
solve_bruteforce(const vector<size_t> &costs, const size_t &w,
                 vector<bool> &s, size_t &ans) {
  const size_t m = costs.size();
  const size_t num_masks = (1ul << m);

  static const size_t INF = std::numeric_limits<size_t>::max(); 
  size_t best_mask = INF;
  ans = INF;

  // get the best score
  for (size_t i = 0; i < num_masks; ++i) {
    if (valid(m, w, i)) {
      //cerr << "testing " << std::bitset<20>(i) << "\n";
      size_t cand = 0;
      size_t mask = i;
      for (size_t j = 0; j < m; ++j) {
        cand += (mask & 1)*costs[j];
        mask >>= 1;
      }
      if (cand < ans) {
        ans = cand;
        best_mask = i;
      }
    }
  }

  // create the index
  cerr << "best mask: " << std::bitset<20>(best_mask) << "\n";
  for (size_t i = 0; i < m; ++i) {
    s[i] = (best_mask & 1);
    best_mask >>= 1;
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

  // GS: uncomment this to check if brute force matches dp solution
  //solve_bruteforce(costs, w, s, ans);
  solve(costs, w, s, ans);

  for (size_t i = 0; i < m; ++i)
    cout << (s[i] ? ('*') : (' ')) << ' ' << costs[i] << '\n';

  cout << "FINAL COST: " << ans << endl;

  return EXIT_SUCCESS;
}
