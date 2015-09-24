# logger
A logger for C99 with selective logmessages, output routing and colour.  
(Also a nice small project starter!)


### To compile logger and run the test

  - clone the repository and cd into there
  - `mkdir build; cd build; cmake ..; make; ./bin/logger_tests`

  Note: This writes 2 files to your /tmp directory and sets 2 symlinks
  in the build directory pointing to them.
 
### Code examples how to use logger:

   - See [/test/logger_tests.c](https://github.com/GabrielaBarbara/logger/blob/master/test/logger_tests.c)
  
### Repository Structure:

  - include/logger.h --- macros and function prototypes 
  - include/color.h  -- color service for the log output
  - src/logger.c --- core functionality
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
    int CUSTOM_LOG_LEVEL = LOG_BASE_COUNT + __COUNTER__;
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
    LOG_TODO_MSG

Usage: `LOG_MACRO_NAME(char *fmt, varargs)`


### Turn of the colours

  To stop seeing colors change line logger/CMakeLists:16 to

  `set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g -fPIC -DCOLOR_ON=0 -DLOGGING_ON=1")`

### Turn off logging

  To compile without log macros change line logger/CMakeLists:16 to

  `set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g -fPIC -DCOLOR_ON=1 -DLOGGING_ON=0")`

### Write or append selected log files (Unix only currently)

  Call this function:

    void log_file_init(char *log_dir_name, // directory where the logs are written to
                       char *symlink_dir,  // where to make the symlink
                       int with_hostname,  // is the hostname in the file name?
                       int log_strategy);  // LOG_WRITE_PER_RUN, LOG_APPEND

  with the following pre-defined values:

  append or write individual files per run: `LOG_WRITE_PER_RUN` or `LOG_APPEND`  
  with or without hostname:                 `NO_HOSTNAME` or `WITH_HOSTNAME`


  Two kinds of symlinks are created:  

    - current.log  
      symlink to the log of the last run (if selected)

    - append_current.log
      symlink to the appended log (if selected)

  *Example:*

    log_file_init("/tmp", 
                  "./",  
                  WITH_HOSTNAME,
                  LOG_WRITE_PER_RUN);
    log_set_level(SHOW_EXACT_LOG_LEVEL, LOG_ERR);
    logger_test("Write to log file:  exact log level -> LOG_ERR");

  This will write the result of LOG_ERR to the log file in /tmp and
  the symlink to to your current directory, complete with hostname and
  time stamp in the name.

  If you use color, this writes the file with colour codes.  To look
  at the file with colour, use:

   `less -R`

  If you want to remove the colour codes from the log file, use:

   `cat logfile_name | sed -r "s:\x1B\[[0-9;]*[m]::g" > target_file`


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

### My terminal is bleeding colour!

   You forgot to add a RESET statement somewhere in your printf statements.

   To fix the terminal, type: `stty sane`

### TODO/Bug list

    - Offer an option to colorise just the name of the log messages

    - Move everything in src into lib, so this project can be used as
      a canned project starter.

    - Add Doxygen 

    - add gcov coverage capability

    - Figure out how to avoid the warning for LOG_MSGs that do not
      have a va_list entry

    - add #ifdef guard to exclude unix file support for windows compiles

    - add windows log file support

