#ifndef SUM_CONTEXT_HEADER
#define SUM_CONTEXT_HEADER

#include <cstdint>

namespace concurrent_sum
{
  const uint64_t arrSize = 1000 * 1000;

  class sum_context
  {
    public:
      sum_context(void);

      ~sum_context(void);

      void init(void);

      void initResult(void);

      void initArr(void);

      const uint64_t* getSize(void);

      int* getArr(void);

      uint64_t getResult(void);

      void addResult(uint64_t& sum);

    private:
      uint64_t         _offset;
      uint64_t         _result;
      const uint64_t*  _size;
      int*             _pArr;
  };
}

#endif
