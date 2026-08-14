#pragma once

#include <iostream>

enum class Error
{
  INPUT_DATA_ERROR,
  EMPTY_VECTOR_ERROR,
  NAN_OR_INF_ERROR
};

inline std::ostream& operator<<(std::ostream& os, const Error& err)
{
  switch(err)
  {
    case Error::EMPTY_VECTOR_ERROR: return os << "ERROR: Empty Vector";
    case Error::INPUT_DATA_ERROR:   return os << "ERROR: Invalid input data";
    case Error::NAN_OR_INF_ERROR:   return os << "ERROR: NAN or INF occured";
  }

  return os << "UNKNOWN ERROR";
}
