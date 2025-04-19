#include "sum_pthread_manager.hpp"

concurrent_sum::pthread_manager::pthread_manager(uint8_t& threadCount_, sum_context* pSumContext_)
: _threadCount(threadCount_),
  _pSumContext(pSumContext_)
{;}

void concurrent_sum::pthread_manager::init(void)
{
  initMutex();
  initThreads();
  _pSumContext->init();
}

void concurrent_sum::pthread_manager::initMutex(void)
{
  pthread_mutex_init(&concurrent_sum::g_Mutex, nullptr);
}

void concurrent_sum::pthread_manager::initThreads(void)
{
  // _threadList.resize(_threadCount);
  _threadList.reserve(_threadCount);

  for (int index = 0; index < _threadCount; ++index)
  {
    _threadList.emplace_back(index);
  }
}

void concurrent_sum::pthread_manager::startAll(void)
{
  for (size_t index = 0; index < _threadCount; ++index)
  {
    pthread_args* args = new pthread_args();

    args->_pSumContext = _pSumContext;
    args->_range = arrSize / _threadCount;

    _threadList[index].start(args);
  }
}

void concurrent_sum::pthread_manager::joinAll(void)
{
  for (size_t index = 0; index < _threadCount; ++index)
  {
    _threadList[index].join();
  }
}

