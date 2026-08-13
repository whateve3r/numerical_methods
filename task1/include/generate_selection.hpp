#pragma once

#include <random>
#include <vector>
#include <expected>

#include "error.hpp"

template <typename T> std::expected<std::vector<T>, Error> generate_selection(int n, T mean, T std_deviation)
{
  if (std_deviation < 0 || n <= 0)
  {
    return std::unexpected(Error::INPUT_DATA_ERROR);
  }

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



