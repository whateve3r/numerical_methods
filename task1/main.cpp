#include <iomanip>
#include <iostream>

#include <cmath>
#include <random>
#include <vector>

enum Method 
{ 
  FAST = 0, 
  ONE_PASS = 1, 
  TWO_PASS = 2 
};

template <typename T> T variance(std::vector<T> data, Method method) 
{
  T dx{};
  T m{};

  switch (method) 
  {
  case FAST: {
    T sum{};
    T rs{};

    for (size_t i = 0; i < data.capacity(); i++) 
    {
      sum += pow(data[i], 2);

      m += data[i];
    }

    rs = sum / static_cast<T>(data.capacity());
    m /= static_cast<T>(data.capacity());

    dx = rs - pow(m, 2);
    break;
  }

  case ONE_PASS:
    m = data[0];
    dx = 0;

    for (size_t i = 0; i < data.capacity(); i++) 
    {
      size_t count = i + 1;

      T old_m = m;

      m = old_m + ((data[i] - old_m) / count);

      dx = dx + ((data[i] - old_m) * (data[i] - m) - dx) / count;
    }

    break;

  case TWO_PASS:
    for (size_t i = 0; i < data.capacity(); i++) 
    {
      m += data[i];
    }

    m /= static_cast<T>(data.capacity());

    for (size_t j = 0; j < data.capacity(); j++)
    {
      dx += pow((data[j] - m), 2);
    }

    dx /= static_cast<T>(data.capacity());
    break;

  default:
    return 1;
  }

  return dx;
}

template <typename T> std::vector<T> generate_selection(int n, T mean, T std_deviation)
{
  std::vector<T> output_data;

  std::random_device seed;
  std::mt19937 generator(seed());
  std::normal_distribution<T> distr(mean, std_deviation);

  for (int i = 0; i < n; i++)
  {
    output_data.push_back(distr(generator));
  }

  return output_data;
}

int main() 
{
  float deviation = 0.01f;

  std::vector<float> sel1 = generate_selection(1000, 100.0f, deviation);

  float dx_fast = variance(sel1, FAST);
  float dx_one_pass = variance(sel1, ONE_PASS);
  float dx_two_pass = variance(sel1, TWO_PASS);

  std::cout << "dx_fast = " << dx_fast << std::endl;

  std::cout << "dx_one_pass = " << dx_one_pass << std::endl;

  std::cout << "dx_two_pass = " << dx_two_pass << std::endl;

  float etalon_dx = pow(deviation, 2);

  std::cout << "etalon_dx = " << etalon_dx << std::endl;

  float rel_error_f = abs(dx_fast - etalon_dx) / etalon_dx;
  float rel_error_o = abs(dx_one_pass - etalon_dx) / etalon_dx;
  float rel_error_t = abs(dx_two_pass - etalon_dx) / etalon_dx;

  std::cout << "Relative error (FAST):     " << rel_error_f << std::endl;
  std::cout << "Relative error (ONE_PASS): " << rel_error_o << std::endl;
  std::cout << "Relative error (TWO_PASS): " << rel_error_t << std::endl;

  std::cout << std::endl;

  float rel_error_fast_twopass = abs(dx_fast - dx_two_pass) / dx_two_pass;
  float rel_error_onepass_twopass = abs(dx_one_pass - dx_two_pass) / dx_two_pass;

  std::cout << "Relative error (FAST & TWO_PASS): " << rel_error_fast_twopass << std::endl;
  std::cout << "Relative error (ONE_PASS & TWO_PASS): " << rel_error_onepass_twopass << std::endl;

}
