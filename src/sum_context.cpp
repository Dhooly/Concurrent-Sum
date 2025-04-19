#include <cstdlib>
#include "sum_context.hpp"

concurrent_sum::sum_context::sum_context(void)
{;}

concurrent_sum::sum_context::~sum_context(void)
{
  free(_pArr);
}

void concurrent_sum::sum_context::init(void)
{
  initArr();
  initResult();
}

void concurrent_sum::sum_context::initResult(void)
{
  _result = 0;
}

void concurrent_sum::sum_context::initArr(void)
{
  _size = &concurrent_sum::arrSize;
  _pArr = (int*)malloc(*_size * sizeof(int));
  int result = 0;
  for (size_t i = 0; i < *(_size); ++i)
  {
    int rand = std::rand() % 100;
    _pArr[i] = rand;
  }
}

const uint64_t* concurrent_sum::sum_context::getSize(void)
{
  return _size;
}

int* concurrent_sum::sum_context::getArr(void)
{
  return _pArr;
}

uint64_t concurrent_sum::sum_context::getResult(void)
{
  return _result;
}

void concurrent_sum::sum_context::addResult(uint64_t& sum)
{
  _result += sum;
}
