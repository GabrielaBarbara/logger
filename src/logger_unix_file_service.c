#define _XOPEN_SOURCE 700
#include "log_maker.h"
#include <assert.h>    // assert in log_msg()
#include <libgen.h>    // 'basename'
#include <stdarg.h>    //  va_args
#include <stdio.h>
#include <stdlib.h>    // abort() and basename
#include <string.h>
#include <time.h>      //  time ops
#include <unistd.h>    //  for unlink
#include <errno.h>     // errorno for file opening
#include <dirent.h>    //   dir operations
#include <sys/stat.h>  // req for lstat
#include <fcntl.h>     // needed for file ops

#define filename_len 1024
char log_filename[filename_len];
int log_file_fd;

static int log_level_initialised = 0;

char logging_dir[filename_len];
char log_symlink[filename_len];

int get_time_string(char** time_buf, int time_buf_len) 
{
    time_t t;
    struct tm *tm_tmp;

    memset(*time_buf, 0, time_buf_len);

    t = time(NULL);
    tm_tmp = localtime(&t);
    if (NULL == tm_tmp) 
        abort();

    strftime(*time_buf, time_buf_len, "%Y%m%d-%H%M%S", tm_tmp);

    return strlen(*time_buf);
}


void log_init(void) 
{
    int hostname_len = 80;
    char hostname_buf[hostname_len];
    gethostname((char*)hostname_buf, hostname_len);

    char* progname = basename(getenv("_"));

    int time_buf_len = 16;
    char *time_buf = malloc(time_buf_len);

    get_time_string(&time_buf, time_buf_len);
    

    snprintf(log_filename, filename_len, "%s%s.%s.%s",
             logging_dir,progname,hostname_buf,time_buf);

    log_file_fd = open(log_filename, 
                  O_CREAT | O_TRUNC | O_WRONLY, 
                  S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    if (log_file_fd == -1) {
        fprintf(stderr, "FATAL: couldn't open file descriptor\n");
        abort();
    }

    symlink(log_filename, log_symlink);

    free(time_buf);
    log_level_initialised = 1;
}


void set_log_dir(const char* dir, const char *sdir) 
{
    errno = 0;

    DIR* has_dir = opendir(dir);

    // int this_error = errno;

    // check the actual log file dir
    if (has_dir) {
        closedir(has_dir);
        snprintf(logging_dir, filename_len, "%s", dir);
    }
    else {
        // FIXME
        // perror(strerror(this_error));
        abort();
        return;
    }

    // check the symlink, remove if it exists
    snprintf(log_symlink, filename_len, "%scurrent.log", sdir);

    struct stat statbuf;
    
    if (-1 == lstat(log_symlink, &statbuf)) 
        return;
    else 
        unlink(log_symlink);

    return;
}

void close_log(void) 
{
    close(log_file_fd);
    printf("Logfile created in %s\nSee %s to view it\n", log_filename, log_symlink);
}

void log_print_to_file(char *prefix, char *contents)
{
    dprintf(log_file_fd, "%s %s ", prefix, contents);
}
