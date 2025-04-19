#ifndef SUM_PTHREAD_HEADER
#define SUM_PTHREAD_HEADER

#include <string>
#include "sum_context.hpp"
#include "sum_pthread_manager.hpp"

namespace concurrent_sum
{
  typedef struct
  {
    sum_context*  _pSumContext;
    uint64_t      _range;
    int           _id;
  } pthread_args;

  class pthread
  {
    public:
      pthread(uint8_t id_);

      int getId(void);

      pthread_t getThreadId(void);

      static void* s_threadEntryPoint(void* arg_);

      void start(pthread_args* args_);

      void join(void);

      void error(std::string msg_);

      void affinitizeThread(void);

    private:
      int        _id;
      pthread_t  _tid;
  };
}

#endif
