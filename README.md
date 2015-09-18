# logger
A logger for C99 with selective logmessages, output routing and colour

### Repository Structure:

  - include/logger.h --- macros and function prototypes 
  - include/color.h  -- color service for the log output
  - src/logger.c --- core functionality
  - src/logger_unix_file.c -- optional 'log to file' facility (to come)
  - tests/logger_test.c -- test suite and demo function
  - CMakeLists.txt -- Cmake set up.


### Function List

* Set the level where and when you need it:

    `log_set_level(int display_option, int level)`

* A default printf function is provided for log output, but if you'd like your own
  define:
    `your_output_function(char *location, *char contents)`

   and then use

    `log_set_output_function(your_output_function)`

  to point to it.

* Define a customised level anywhere:

  Global to your file, provide the following declarations:
```
    const int CUSTOM_LOG_LEVEL = LOG_BASE_COUNT + __COUNTER__;
    #define CUSTOM_LOG_MSG("name", CUSTOM_LOG_LEVEL, fmt, ...)
```

 * To create a selection of log levels to display:

    `log_set_level_selection(int selection[], int selection_size)`

  Usage example:
```
     int arr[] = {LOG_INFO, LOG_WARN, YOUR_CUSTOM_LEVEL};
     log_set_level_selection(arr, 3);
     log_set_level(SHOW_SELECT_LOG_LEVELS, LOG_WARN)
```

  This will show you only the selected levels up to LOG_WARN.

### Display Options

    SHOW_NOTHING:                   Do not output any log messages
    SHOW_EXACT_LOG_LEVEL            See exactly that level
    SHOW_LOG_LEVEL_INCLUDING        See all log levels up to given level
    SHOW_SELECT_LOG_LEVELS          Cherry pick levels to display


### Provided LOG Macros

    LOG_ERROR_MSG    
    LOG_WARNING_MSG 
    LOG_NOTICE_MSG
    LOG_INFO_MSG
    LOG_DEBUG_MSG

    Usage: `LOG_MACRO_NAME(char *name, int level, char *fmt, varargs)`


### Turn of the colours

  To stop seeing colors change line logger/CMakeLists:16 to

  `set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g -fPIC -DCOLOR_ON=0 -DLOGGING_ON=1")`

### Turn off logging

  To compile without log macros change line logger/CMakeLists:16 to

  `set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g -fPIC -DCOLOR_ON=1 -DLOGGING_ON=0")`


### To compile logger and run the test

  - clone the repository and cd into there
  - mkdir build; cd build; cmake ..; make; ./bin/logger_tests

### Code examples how to use logger:

   - See [/test/logger_tests.c](https://github.com/GabrielaBarbara/logger/blob/master/test/logger_tests.c)
  

### What's the deal with the color.h file I see?

   Well, I like color in my debugging statements, it makes things
   easier to see.  Either leave it in place, or, stick it in your
   /usr/local/include so you can use in anywhere you want, like so:

   `#include <color.h>`

   For instructions how to use it, read the file itself, it shows you
   how to easily put some color in your code, and how to turn the
   resulting Xmas tree lights off on the quick as well.

   Alternatively, you can just remove it for your purposes, logger.c
   does not depend on it.


### Can I use the code?  

   Yes, it has an Apache 2.0 licence, with one small caveat: You need
   to keep the licence statement intact, and that also means, you
   leave the advert for this repository in place, so other people can
   see where to get the source.  If I contribute to your project then
   that is a different matter, because I get to change my licence how
   I like in order to match your usual conditions :P
