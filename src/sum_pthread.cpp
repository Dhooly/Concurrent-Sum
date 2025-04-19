#include <iostream>
#include <cmath>
#include "sum_pthread.hpp"

concurrent_sum::pthread::pthread(uint8_t id_)
  : _id(id_)
{;}

int concurrent_sum::pthread::getId(void)
{
  return _id;
}

pthread_t concurrent_sum::pthread::getThreadId(void)
{
  return _tid;
}

void* concurrent_sum::pthread::s_threadEntryPoint(void* arg_)
{
  concurrent_sum::pthread_args* args = static_cast<pthread_args*>(arg_);

  concurrent_sum::sum_context* pSumContext = args->_pSumContext;
  int* pArr = pSumContext->getArr();
  uint64_t range = args->_range;
  int id = args->_id;

  // Create a CPU set and add the desired core
  cpu_set_t cpuset;
  CPU_ZERO(&cpuset);
  CPU_SET(id, &cpuset);

  if (pthread_setaffinity_np(pthread_self(), sizeof(cpu_set_t), &cpuset))
  {
    std::cerr << "Error setting CPU affinity on core " << id << "\n";
  }

  uint64_t localSum = 0;
  double tmp = 0.0;

  uint64_t start = range * id;
  uint64_t end   = range * (id + 1);

  for (size_t i = start; i < end; ++i )
  {
    for (size_t j = 0; j < 1000; ++j)
    {
      std::sqrt(tmp + j);
    }
    localSum += pArr[i];
  }
  pthread_mutex_lock(&concurrent_sum::g_Mutex);
  pSumContext->addResult(localSum);
  pthread_mutex_unlock(&concurrent_sum::g_Mutex);

  delete args;

  return nullptr;
}

void concurrent_sum::pthread::start(pthread_args* args_)
{
  args_->_id = getId();
  if (pthread_create(&_tid, nullptr, concurrent_sum::pthread::s_threadEntryPoint, static_cast<void*>(args_)) != 0)
  {
    error("Error: Unable to create thread... terminating");
  }
}

void concurrent_sum::pthread::join(void)
{
  pthread_join(_tid, nullptr);
}

void concurrent_sum::pthread::error(std::string msg_)
{
  std::cerr << msg_ << std::endl;
  exit(-1);
}

void concurrent_sum::pthread::affinitizeThread(void)
{
}
