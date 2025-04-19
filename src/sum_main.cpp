#include <iostream>
#include <string>
#include <vector>
#include <pthread.h>
#include <chrono>
 #include <unistd.h>
#include "sum_main.hpp"
#include "sum_context.hpp"
#include "sum_pthread_manager.hpp"

void concurrent_sum::usage()
{
  std::cerr << "Usage:" << std::endl << std::endl;
  std::cerr << "\tconccurent_sum" << std::endl;
  std::cerr << "\t\tor" << std::endl;
  std::cerr << "\tconccurent_sum --thread-count <num>" << std::endl << std::endl;
  std::cerr << "Options:" << std::endl << std::endl;
  std::cerr << "--thread-count\t: Number of concurrent threads calculating array sum" << std::endl;
}

concurrent_sum::command_line_options::command_line_options(int argc_, char* argv_[])
{
  _threadCount = 1;

  for (size_t i = 0; i < argc_; ++i)
  {
    _options.emplace_back(argv_[i]);
  }
}

bool concurrent_sum::command_line_options::isValid(void)
{
  int argc = _options.size();
  if (argc > 1)
  {
    if (argc != 3)
    {
      return false;
    }

    if (_options[1] != "--thread-count")
    {
      std::cerr << "Error: Invalid flag." << std::endl << std::endl;
      return false;
    }

    if (!std::stoi(_options[2]))
    {
      std::cerr << "Error: Option not a number." << std::endl << std::endl;
      return false;
    }

    int numCores = sysconf(_SC_NPROCESSORS_ONLN);

    if (std::stoi(_options[2]) > numCores)
    {
      std::cerr << "Warning: Thread count larger than physical core count, defaulting to max: " << numCores << std::endl << std::endl;
      _threadCount = numCores;
      return true;
    }

    _threadCount = std::stoi(_options[2]);
  }

  return true;
}

uint8_t concurrent_sum::command_line_options::getThreadCount(void)
{
  return _threadCount;
}


int main(int argc, char* argv[])
{
  concurrent_sum::command_line_options commandLineOptions(argc, argv);

  if (!commandLineOptions.isValid())
  {
    concurrent_sum::usage();
    return -1;
  }

  uint8_t threadCount = commandLineOptions.getThreadCount();

  fprintf(stdout, "Calculating the sum of %lu numbers with %d thread(s)...\n", concurrent_sum::arrSize, threadCount);

  concurrent_sum::sum_context sumContext;

  concurrent_sum::pthread_manager pthreadManager(threadCount, &sumContext);


  auto start = std::chrono::high_resolution_clock::now();

  pthreadManager.init();
  pthreadManager.startAll();
  pthreadManager.joinAll();

  auto end = std::chrono::high_resolution_clock::now();

 std::chrono::duration<double> duration = end - start;

  std::cout << "Elapsed time: " << duration.count() << " seconds with a result of " << sumContext.getResult() << std::endl;
  return 0;
}
