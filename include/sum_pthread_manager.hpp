#ifndef SUM_PTHREAD_MANAGER_HEADER
#define SUM_PTHREAD_MANAGER_HEADER

#include <vector>
#include "sum_context.hpp"
#include "sum_pthread.hpp"

namespace concurrent_sum
{
  static inline pthread_mutex_t g_Mutex;

  class pthread;

  using pthread_vector = std::vector<concurrent_sum::pthread>;

  class pthread_manager
  {
    public:

      pthread_manager(uint8_t& threadCount_, sum_context* pSumContext_);

      void init(void);

      void initMutex(void);

      void initThreads(void);

      void startAll(void);

      void joinAll(void);

    private:
      const uint8_t   _threadCount;
      sum_context*    _pSumContext;
      pthread_vector  _threadList;
  };
}

#endif
