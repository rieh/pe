#include "pe_test.h"

namespace nt_test {
SL void parity_test() {
  assert(is_even(0) == 1);
  assert(is_even(1) == 0);
  assert(is_even(2) == 1);
  assert(is_even(3) == 0);

  assert(is_odd(0) == 0);
  assert(is_odd(1) == 1);
  assert(is_odd(2) == 0);
  assert(is_odd(3) == 1);

  assert(same_parity(0, 0) == 1);
  assert(same_parity(0, 1) == 0);
  assert(same_parity(0, 2) == 1);
  assert(same_parity(0, 3) == 0);

  assert(same_parity(1, 0) == 0);
  assert(same_parity(1, 1) == 1);
  assert(same_parity(1, 2) == 0);
  assert(same_parity(1, 3) == 1);

  assert(same_parity(2, 0) == 1);
  assert(same_parity(2, 1) == 0);
  assert(same_parity(2, 2) == 1);
  assert(same_parity(2, 3) == 0);

  assert(same_parity(3, 0) == 0);
  assert(same_parity(3, 1) == 1);
  assert(same_parity(3, 2) == 0);
  assert(same_parity(3, 3) == 1);

  for (int i = -100; i <= 100; ++i) assert(is_even(i) + is_odd(i) == 1);
}
PE_REGISTER_TEST(&parity_test, "parity_test", SMALL);

SL void gcd_test() {
  assert(gcd({2, 4, 6}) == 2);
  assert(gcd(2, 4, 6) == 2);
  assert(gcd(2L, 4LL, 6ULL) == 2);
}
PE_REGISTER_TEST(&gcd_test, "gcd_test", SMALL);

SL void get_factors_test() {
  auto result = get_factors(1);
  assert(result == vector<int64>{1});

  result = get_factors(2);
  assert(result == vector<int64>({1, 2}));

  result = get_factors(3);
  assert(result == vector<int64>({1, 3}));

  result = get_factors(4);
  assert(result == vector<int64>({1, 2, 4}));

  result = get_factors(12);
  sort(all(result));
  assert(result == vector<int64>({1, 2, 3, 4, 6, 12}));

  for (int64 limit = -1; limit <= 20; ++limit) {
    auto result = get_factors(12, limit);
    sort(all(result));
    vector<int64> expected;
    for (auto iter : {1, 2, 3, 4, 6, 12})
      if (limit < 0 || iter <= limit) {
        expected.push_back(iter);
      }
    assert(result == expected);
  }
}

PE_REGISTER_TEST(&get_factors_test, "get_factors_test", SMALL);

SL void is_square_free_test() {
  const int64 n = maxp * 2;
  int64 ans1 = 0;
  {
    TimeRecorder tr;
    for (int i = 1; i <= n; ++i) ans1 += is_square_free(i);
    // cerr << tr.elapsed().format() << endl;
  }
  int64 ans2 = 0;
  {
    TimeRecorder tr;
    for (int i = 1; i <= n; ++i) ans2 += is_square_free_normal(i);
    // cerr << tr.elapsed().format() << endl;
  }
  assert(ans1 == ans2);
}

PE_REGISTER_TEST(&is_square_free_test, "is_square_free_test", SMALL);
}  // namespace nt_test
