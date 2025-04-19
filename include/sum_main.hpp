#ifndef SUM_MAIN_HEADER
#define SUM_MAIN_HEADER

namespace concurrent_sum
{
  void usage(void);

  class command_line_options
  {
    public:
      command_line_options(int argc_, char* argv_[]);

      bool isValid(void);

      uint8_t getThreadCount(void);

    private:
      std::vector<std::string>  _options;
      uint8_t                   _threadCount;
  };
}

#endif
