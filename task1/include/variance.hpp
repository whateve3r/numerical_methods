#pragma once

#include <cmath>
#include <vector>
#include <expected>

#include "error.hpp"

template <typename T> std::expected<T, Error> fast(std::vector<T> data)
{
  if (data.empty())
  {
    return std::unexpected(Error::EMPTY_VECTOR_ERROR);
  }

  T sum{}, rs{}, m{};

  for (size_t i = 0; i < data.size(); i++)
  {
    sum += data[i] * data[i];
    m   += data[i];
  }

  rs = sum / static_cast<T>(data.size());
  m /= static_cast<T>(data.size());

  T res = rs - m * m;

  if (!std::isfinite(res))
  {
    return std::unexpected(Error::NAN_OR_INF_ERROR);
  }

  return res;
}

template <typename T> std::expected<T, Error> one_pass(std::vector<T> data)
{
  if (data.empty())
  {
    return std::unexpected(Error::EMPTY_VECTOR_ERROR);
  }

  T m = data[0];
  T res{};

  for (size_t i = 0; i < data.size(); i++)
  {
    T count = static_cast<T>(i + 1);

    assert(count != 0);

    T old_m = m;

    m = old_m + ((data[i] - old_m) / count);
    
    res += ((data[i] - old_m) * (data[i] - m) - res) / count; 
  }

  if (!std::isfinite(res))
  {
    return std::unexpected(Error::NAN_OR_INF_ERROR);
  }

  return res;
}

template <typename T> std::expected<T, Error> two_pass(std::vector<T> data)
{
  if (data.empty())
  {
    return std::unexpected(Error::EMPTY_VECTOR_ERROR);
  }

  T m{}, res{};

  for (size_t i = 0; i < data.size(); i++)
  {
    m += data[i];
  }

  m /= static_cast<T>(data.size());

  for (size_t j = 0; j < data.size(); j++)
  {
    res += (data[j] - m) * (data[j] - m);
  }

  res /= static_cast<T>(data.size());

  if (!std::isfinite(res))
  {
    return std::unexpected(Error::NAN_OR_INF_ERROR);
  }

  return res;
}
