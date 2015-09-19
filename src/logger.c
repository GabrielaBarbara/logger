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
#include <stdio.h>     //  asprinf,vasprintf
#include <malloc.h>    //  free
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

void __attribute__((nonnull, format(printf,6,7)))
_log_msg(const char *name, int level, const char* filename, int linenum, 
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

    char *prefix, *contents;
    va_list argp;

    if (-1 == asprintf(&prefix, "%-10s %s:%d %s() \n          ", 
                       name, filename, linenum, function))
        prefix = NULL;

    va_start(argp, fmt); 
    if (-1 == vasprintf(&contents, fmt, argp))
        contents = NULL;
    va_end(argp); 
    log_output_ptr(prefix, contents);
    free(prefix);
    free(contents);
}

// TODO:  add file service for windows
// TODO:  add file service for IOS
// TODO:  add file service for OS-X
// TODO:  add compiile guard for file services

/****  file service for unix ****/
#define _XOPEN_SOURCE 700
#include <assert.h>    // assert in log_msg()
#include <libgen.h>    // 'basename'
#include <stdarg.h>    //  va_args
#include <stdio.h>
#include <stdlib.h>    // abort() and basename
#include <string.h>
#include <time.h>      //  time ops
#include <unistd.h>    //  for unlink
#include <dirent.h>    // dir operations
#include <sys/stat.h>  // req for lstat
#include <fcntl.h>     // needed for file ops

// fix function name
// fix variable names
// change to int?
#define filename_len 1024

char log_filename[filename_len];
int log_file_fd = -13;

char logging_dir[filename_len];
char log_symlink[filename_len];

int log_file_initialised = 0;

void close_log(void) 
{
    if (!log_file_initialised) 
        return;
    
    close(log_file_fd);
    if (log_file_initialised == LOG_APPEND)
        printf("Logfile appended to %s\nSee %s to view it\n", log_filename, log_symlink);
    else
        printf("Logfile created in %s\nSee %s to view it\n", log_filename, log_symlink);
    log_file_initialised = 0;
}

void log_print_to_file(char *prefix, char *contents)
{
    dprintf(log_file_fd, "%s %s\n", prefix, contents);
}

void log_file_init(char *log_dir_name, 
                   char *symlink_dir,  
                   int with_hostname,
                   int log_strategy) 
{    
    DIR* has_dir = opendir(log_dir_name);

    if (has_dir) {
        closedir(has_dir);
        snprintf(logging_dir, filename_len, "%s", log_dir_name);
    }
    else { 
        printf("The required directory %s does not exist.\n", log_dir_name);
        return;
    }
 
    if(log_file_initialised) 
        close_log();

    memset(log_filename, 0, sizeof(filename_len));
    int file_exists = 1;

    if (log_strategy == LOG_APPEND) {
        snprintf(log_symlink, filename_len, "%sappended_current.log", symlink_dir);
        if(access(log_symlink, F_OK) == -1) {
            file_exists = 0;
        }
        else {
            if (readlink(log_symlink, log_filename, sizeof(log_filename)-1) < 0) {
                file_exists = 0;
            }
            else {
                log_file_fd = open(log_filename, 
                                   O_APPEND | O_WRONLY, 
                                   S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            }
        }
    }
    if (!file_exists || log_strategy == LOG_WRITE_PER_RUN) {

        if (log_strategy == LOG_WRITE_PER_RUN)
            snprintf(log_symlink, filename_len, "%scurrent.log", symlink_dir);

        struct stat statbuf;
        if (-1 != lstat(log_symlink, &statbuf)) 
            unlink(log_symlink);

        int hostname_len = 80;
        char hostname_buf[hostname_len];
        
        if (with_hostname == WITH_HOSTNAME) 
            gethostname((char*)hostname_buf, hostname_len);
        else 
            hostname_buf[0] = '\0';
        
        char* progname = basename(getenv("_"));

        int time_buf_len = 16;
        char *time_buf = malloc(time_buf_len);
        memset(time_buf, 0, time_buf_len);

        time_t t;
        struct tm *tm_tmp;
        t = time(NULL);

        // should this be threadsafe?
        tm_tmp = localtime(&t);

        // is this needed
        if (NULL == tm_tmp) 
            abort();

        strftime(time_buf, time_buf_len, "%Y%m%d-%H%M%S", tm_tmp);

        time_buf_len = strlen(time_buf);

        if (with_hostname == WITH_HOSTNAME)
            snprintf(log_filename, filename_len, "%s%s.%s.%s",
                     logging_dir, progname, hostname_buf, time_buf);
        else
            snprintf(log_filename, filename_len, "%s%s.%s",
                     logging_dir, progname, time_buf);

        free(time_buf);
        log_file_fd = open(log_filename, 
                           O_CREAT | O_TRUNC | O_WRONLY, 
                           S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    }

    if (log_file_fd == -1) {
        fprintf(stderr, "FATAL: couldn't open file descriptor: >>> %s <<<\n",log_filename);
        abort();
    }
    
    /* make the symlink */
    symlink(log_filename, log_symlink);
    
    log_file_initialised = log_strategy;
}
