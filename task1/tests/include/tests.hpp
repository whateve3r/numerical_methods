#pragma once

#include <iostream>
#include <expected>

template <typename T, typename E>
std::ostream& operator<<(std::ostream& os, const std::expected<T, E>& exp)
{
  if (exp.has_value())
    os << exp.value();
 
  else
    os << exp.error();

  return os;
}
