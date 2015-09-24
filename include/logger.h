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
//
// Documentation is here https://github.com/GabrielaBarbara/logger 

#ifndef LOGGIN_ON_H
#define LOGGIN_ON_H

/** log levels */
#define LOG_ERR    1
#define LOG_WARN   2
#define LOG_NOTICE 3
#define LOG_DEBUG  4
#define LOG_INFO   5
#define LOG_TODO   6

/* We have 6 predefined log levels, __COUNTER__ starts at 0 */
#define LOG_BASE_COUNT 7

/* if you ever need more macros than this... change it :-D */
#define LOG_MAX_LEVEL 1000000

/** Display options */
#define SHOW_NOTHING 0
#define SHOW_EXACT_LOG_LEVEL 1
#define SHOW_LOG_LEVEL_INCLUDING 2
#define SHOW_SELECT_LOG_LEVELS 3

void log_print_to_file(char *prefix, char *contents);

/** Set the display option and the log level */
void log_set_level(int display_option, int log_level);

/** Set the selection picks and the size of the selection array */
void log_set_level_selection(int selection[], int selection_size);

/** Set the ptr to the log output function */
void log_set_output_function(void (*function_ptr)(char* prefix, char* contents));

/** The default output function is set to printf for unix */
void log_default_stdout_func(char *prefix, char *contents);

/* Produce the log message defined by the DEFINE_LOG_MSG macro */
void __attribute__((nonnull, format(printf,6,7)))
 _log_msg(const char *name, int level, const char* filename, int linenum, 
              const char* function, char *fmt, ...);

/* Log file options */
#define LOG_WRITE_PER_RUN 1
#define LOG_APPEND 2
#define NO_HOSTNAME 0
#define WITH_HOSTNAME 1

/* Everytime you open a new logfile, this function needs to be called.
 * This closes the previous file and lets you know where it was
 * written to, and, which symlink to use to view it.
 * If the file you want to append to does not exist, it is created.
 */
void log_file_init(char *log_dir_name, 
                   char *symlink_dir,  // where to make the current.log symlink
                   int with_hostname,  // is the hostname in the file name?
                   int log_strategy);  // LOG_WRITE_PER_RUN, LOG_APPEND

/* Call this when done, it let's you know the name if the logfile. */
void close_log(void);

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
#define LOG_TODO_MSG(msg, ...)    DEFINE_LOG_MSG("TODO",LOG_TODO, msg, __VA_ARGS__);

#else

#define DEFINE_LOG_MSG(name, level, msg, ...) 

#define LOG_ERROR_MSG(msg, ...)   
#define LOG_WARNING_MSG(msg, ...) 
#define LOG_NOTICE_MSG(msg, ...)  
#define LOG_INFO_MSG(msg, ...)    
#define LOG_DEBUG_MSG(msg, ...)   
#define LOG_TODO_MSG(msg, ...)
#endif /* LOGGGIN_ON */
#endif /* LOGGING_ON_H */
