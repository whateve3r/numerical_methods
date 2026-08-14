#include <gtest/gtest.h>
#include <cmath>

#include "tests.hpp"
#include "error.hpp"
#include "variance.hpp"

template <typename T>
class VarianceTest : public ::testing::Test 
{
  protected:
      struct Case
      {
        std::vector<T> data;
        std::expected<T, Error> expected;
      };

      inline static std::vector<Case> cases;

      static void SetUpTestSuite()
      {
        cases = {
          { {5, 5, 5, 5, 5},          0},
          { {42},                     0},
          { {2, 4, 4, 4, 5, 5, 7, 9}, 4},
          { {0, 2},                   1},
          { {-3, -1, 1, 3},           5},
          { {-100, 0, 0, 0, 100},     4000},
          { {},                       std::unexpected(Error::EMPTY_VECTOR_ERROR)},
          { {NAN, 2, 3, 4, 9},        std::unexpected(Error::NAN_OR_INF_ERROR)},
          { {INFINITY, 3, 0, 98},     std::unexpected(Error::NAN_OR_INF_ERROR)}
        };
      };

};

using types = ::testing::Types<float, double>;
TYPED_TEST_SUITE(VarianceTest, types);

TYPED_TEST(VarianceTest, CorrectMath)
{
  for (const auto& c : this->cases)
  {
    auto res = fast(c.data);

    EXPECT_EQ(res, c.expected)
      << "Input data: " << ::testing::PrintToString(c.data) << std::endl
      << "Result: "   << res << std::endl
      << "Expected: " << c.expected << std::endl;
  }
}
