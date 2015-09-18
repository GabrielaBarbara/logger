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

#include <stdarg.h>    //  va_args
#include <stdio.h>     //  sprinf
#include "logger.h"

/* The currently selected log level */
int log_level_currently = 0;

/* The currently selected scope of log messages to show */
int log_level_scope = 0;

/* A selection of log levels we wish to display */
int *log_level_selection;

/* Size of the selection array */
int log_level_selection_size = 0;

void log_set_level(int scope, int level)
{
    log_level_currently = level;
    log_level_scope = scope;
}

void log_default_stdout_func(char *prefix, char *contents)
{
    printf("%s %s\n", prefix, contents);
}

void (*log_output_ptr)(char* prefix, char* contents) = &log_default_stdout_func;

void log_set_output_function(void (*function_ptr)(char* prefix, char* contents))
{
    log_output_ptr = function_ptr;
}

void log_set_level_selection(int selection[], int size)
{
    log_level_selection = selection;
    log_level_selection_size = size;
}

void _log_msg(char *name, int level, char* filename, int linenum, 
              const char* function, char *fmt, ...)
{
    switch (log_level_scope) {
        case(SHOW_NOTHING): return;
        case(SHOW_LOG_LEVEL_INCLUDING): {
            if (level > log_level_currently)
                return;
            break;
        }
        case(SHOW_EXACT_LOG_LEVEL): {
            if (level != log_level_currently)
                return;
            break;
        }
        default: { /* SHOW_SELECT_LOG_LEVELS */
            int ok = 0;
            for (int i = 0; i < log_level_selection_size; i++) {
                if (level > log_level_currently)
                    break;
                if (level == log_level_selection[i]) {
                    ok = 1;
                    break;
                }
            }
            if (!ok) {
                return;
            }
        }
        }

    char prefix[300];
    char contents[1000]; 

    va_list argp;

    sprintf(prefix, "%-10s %s:%d %s() \n          ", name, filename, linenum, function);

    va_start(argp, fmt);
    vsprintf(contents, fmt, argp);
    va_end(argp);
    
    log_output_ptr(prefix, contents);
}
