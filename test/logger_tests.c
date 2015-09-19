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

#include "logger.h"
#include <stdio.h>
#include <unistd.h>

/* To turn off color, pass -DCOLOR=0 to gcc */
#include "color.h"

/* Demonstrate how to defind a custom log message */
const int LOG_FIRST_CUSTOM_LOG_LEVEL = LOG_BASE_COUNT + __COUNTER__;
#define LOG_FIRST_CUSTOM_MSG(msg,...) DEFINE_LOG_MSG("FIRST_CUSTOM_LOG_LEVEL",LOG_FIRST_CUSTOM_LOG_LEVEL,  msg, __VA_ARGS__);

const int LOG_SECOND_CUSTOM_LOG_LEVEL = LOG_BASE_COUNT + __COUNTER__;
#define LOG_SECOND_CUSTOM_MSG(msg,...) DEFINE_LOG_MSG("SECOND_CUSTOM_LOG_LEVEL",LOG_SECOND_CUSTOM_LOG_LEVEL, msg, __VA_ARGS__);

/* Set a custom output function */
void custom_output_function(char *prefix, char* contents)
{
    printf(MOSS "%s " GREY "%s\n" RESET, prefix, contents);
}

void logger_test(char *show_what)
{
    printf(TEAL "Logger Demo: " PURPLE "%s\n" RESET ,show_what);

    /* predefined log messaage macros */
    LOG_ERROR_MSG("This is a LOG_ERROR_MSG = %s","Something strange has happened.");
    LOG_WARNING_MSG("This is a LOG_WARNING_MSG = %s","Your spidey sense tingles.");
    LOG_NOTICE_MSG(ORANGE "This is a LOG_NOTICE_MSG = %s" RESET, "The geek police has been notified.");
    LOG_DEBUG_MSG("This is a LOG_DEBUG_MSG = %s", "The exterminator arrives.");
    LOG_INFO_MSG("This is a LOG_INFO_MSG = %s","You feel very informed.");
    LOG_TODO_MSG("This is a LOG_TODO_MSG = %s","Don't forget to mow the lawn!");

    /* custom log levels */
    LOG_FIRST_CUSTOM_MSG("This is the first customised log function, log level nr = %d",
                         LOG_FIRST_CUSTOM_LOG_LEVEL);

    LOG_SECOND_CUSTOM_MSG("This is the second custom log function, log level nr = %d",
                         LOG_SECOND_CUSTOM_LOG_LEVEL);

    printf(TEAL "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n" RESET);
}



int main(int argc, char *argv[])
{
    log_set_output_function(custom_output_function);

    log_set_level(SHOW_NOTHING, LOG_ERR);
    logger_test("Show nothing");

    log_set_level(SHOW_LOG_LEVEL_INCLUDING, LOG_INFO);
    logger_test("show all log levels upto including LOG_INFO");

    log_set_level(SHOW_EXACT_LOG_LEVEL, LOG_NOTICE);
    logger_test("show only log level LOG_NOTICE");

    int selection[] = {LOG_TODO, LOG_WARN, LOG_FIRST_CUSTOM_LOG_LEVEL};
    log_set_level_selection(selection, 3);

    log_set_level(SHOW_SELECT_LOG_LEVELS, LOG_FIRST_CUSTOM_LOG_LEVEL);
    logger_test("Show selected log levels up to LOG_FIRST_CUSTOM_LOG_LEVEL");

    log_set_level(SHOW_EXACT_LOG_LEVEL, LOG_SECOND_CUSTOM_LOG_LEVEL);
    logger_test("Show just your second custom log message");

    log_set_output_function(log_print_to_file);
    log_file_init("/home/g/logger/logs/", 
                  "/home/g/logger/build/",  
                  NO_HOSTNAME,
                  LOG_APPEND);

    log_set_level(SHOW_SELECT_LOG_LEVELS, LOG_SECOND_CUSTOM_LOG_LEVEL);
    logger_test("Write to log file:  selected log levels up to LOG_SECOND_CUSTOM_LOG_LEVEL");
    log_set_level(SHOW_EXACT_LOG_LEVEL, LOG_NOTICE);
    logger_test("Write to log file:  exact log level -> LOG_NOTICE");
    log_file_init("/home/g/logger/logs/", 
                  "/home/g/logger/build/",  
                  NO_HOSTNAME,
                  LOG_APPEND);

    log_set_level(SHOW_SELECT_LOG_LEVELS, LOG_SECOND_CUSTOM_LOG_LEVEL);
    logger_test("Write to log file:  selected log levels up to LOG_SECOND_CUSTOM_LOG_LEVEL");
    log_set_level(SHOW_EXACT_LOG_LEVEL, LOG_NOTICE);
    logger_test("Write to log file:  exact log level -> LOG_NOTICE");

    log_file_init("/home/g/logger/logs/", 
                  "/home/g/logger/build/",  
                  WITH_HOSTNAME,
                  LOG_WRITE_PER_RUN);
    log_set_level(SHOW_EXACT_LOG_LEVEL, LOG_ERR);
    logger_test("Write to log file:  exact log level -> LOG_ERR");

    close_log();
    return 0;
}
