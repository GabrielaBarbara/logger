// This file is part of the logger project:
//    (https://github.com/GabrielaBarbara/logger)
// 
// The copyright for this software is held by 
//    Gabriela Gibson <gabriela.gibson@gmail.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Display Options
---------------

SHOW_NOTHING:                   Do not output any log messages
SHOW_EXACT_LOG_LEVEL            See exactly that level
SHOW_LOG_LEVEL_INCLUDING        See all log levels up to given level
SHOW_SELECT_LOG_LEVELS          Cherry pick levels to display

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Existing Log levels
--------------------

Name         Purpose
------------------------------------------------------------------------------
LOG_ERR    
LOG_WARN   
LOG_NOTICE 
LOG_DEBUG  
LOG_INFO   

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Provided LOG Macros
-------------------

LOG_ERROR_MSG    
LOG_WARNING_MSG 
LOG_NOTICE_MSG
LOG_INFO_MSG
LOG_DEBUG_MSG

Usage: LOG_MACRO_NAME(char *name, int level, char *fmt, varargs)

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
Function List
-------------

* Set the level where and when you need it:
   log_set_level(int display_option, int level) 

* A default printf function is provided for log output, but if you'd like your own
  define 'your_output_function(char *location, *char contents)' and then use
     log_set_output_function(your_output_function)       
  to point to it.

* Define a customised level anywhere:

   Global to your file, provide the following declarations:
         const int CUSTOM_LOG_LEVEL = LOG_BASE_COUNT + __COUNTER__;
         #define CUSTOM_LOG_MSG("name", CUSTOM_LOG_LEVEL, fmt, ...)


 * To create a selection of log levels to display:

  log_set_level_selection(int selection[], int selection_size)

  Usage example:
         int arr[] = {LOG_INFO, LOG_WARN, YOUR_CUSTOM_LEVEL};
         log_set_level_selection(arr, 3);
         log_set_level(SHOW_SELECT_LOG_LEVELS, LOG_WARN)

  This will show you only the selected levels up to LOG_WARN .

=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
To stop seeing colors change line logger/CMakeLists:16 from

set(CMAKE_C_FLAGS "-std=c99 -D_GNU_SOURCE -g -fPIC -DCOLOR_ON=1 -DLOGGING_ON=1")

to:  -DCOLOR_ON=0

And to turn off logging, set -DLOGGING_ON=1 to -DLOGGING_ON=0 in the same line.
=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
*/

#ifndef LOGGIN_ON_H
#define LOGGIN_ON_H

/** log levels */
#define LOG_ERR    1
#define LOG_WARN   2
#define LOG_NOTICE 3
#define LOG_DEBUG  4
#define LOG_INFO   5

/* We have 5 predefined log levels, __COUNTER__ starts at 0 */
#define LOG_BASE_COUNT 6

/** Display options */
#define SHOW_NOTHING 0
#define SHOW_EXACT_LOG_LEVEL 1
#define SHOW_LOG_LEVEL_INCLUDING 2
#define SHOW_SELECT_LOG_LEVELS 3

/** Set the display option and the log level */
void log_set_level(int display_option, int log_level);

/** Set the selection picks and the size of the selection array */
void log_set_level_selection(int selection[], int selection_size);

/** Set the ptr to the log output function */
void log_set_output_function(void (*function_ptr)(char* prefix, char* contents));

/** The default output function is set to printf for unix */
void log_default_stdout_func(char *prefix, char *contents);

/* Produce the log message defined by the DEFINE_LOG_MSG macro */
void _log_msg(char *name, int level, char* filename, int linenum, 
              const char* function, char *fmt, ...);

#if LOGGING_ON /* -DLOGGING=1 was passed to gcc */

/* The general log macro */
#define DEFINE_LOG_MSG(name, level, msg, ...)                                  \
    _log_msg(name, level, __FILE__, __LINE__, __FUNCTION__, msg, __VA_ARGS__);

/* Convenience functions corresponding to the provided log levels */
#define LOG_ERROR_MSG(msg, ...)   DEFINE_LOG_MSG("ERROR",LOG_ERR, msg, __VA_ARGS__);
#define LOG_WARNING_MSG(msg, ...) DEFINE_LOG_MSG("WARN",LOG_WARN, msg, __VA_ARGS__);
#define LOG_NOTICE_MSG(msg, ...)  DEFINE_LOG_MSG("NOTICE",LOG_NOTICE, msg, __VA_ARGS__);
#define LOG_INFO_MSG(msg, ...)    DEFINE_LOG_MSG("INFO",LOG_INFO, msg, __VA_ARGS__);
#define LOG_DEBUG_MSG(msg, ...)   DEFINE_LOG_MSG("DEBUG",LOG_DEBUG, msg, __VA_ARGS__);

#else

#define DEFINE_LOG_MSG(name, level, msg, ...) 

#define LOG_ERROR_MSG(msg, ...)   
#define LOG_WARNING_MSG(msg, ...) 
#define LOG_NOTICE_MSG(msg, ...)  
#define LOG_INFO_MSG(msg, ...)    
#define LOG_DEBUG_MSG(msg, ...)   

#endif /* LOGGGIN_ON */
#endif /* LOGGING_ON_H */
