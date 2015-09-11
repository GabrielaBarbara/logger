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

/////////////////////////////////////////////////////////////
//
// color.h -- a color utility
// 
// To use this file globally via #include <color.h> 
// copy it to /usr/include
//
// To see the color map and some help on this file, 
// use SHOW_COLOR_HELP() to your code.
//
/////////////////////////////////////////////////////////////
#ifndef __COLOR_H
#define __COLOR_H
//
#ifndef COLOR_ON
#define COLOR_ON 1
#endif

#if COLOR_ON 

#define RED        "\x1b[31m"
#define ORANGE     "\x1b[01;31m"
#define MOSS       "\x1b[32m"
#define GREEN      "\x1b[01;32m"
#define BROWN      "\x1b[33m"
#define YELLOW     "\x1b[01;33m"
#define NAVY       "\x1b[34m"
#define BLUE       "\x1b[01;34m"
#define PURPLE     "\x1b[35m"
#define PINK       "\x1b[01;35m"
#define TEAL       "\x1b[36m"
#define CYAN       "\x1b[01;36m"
#define BLACK      "\x1b[30m"
#define GREY       "\x1b[37m"
#define CHARCOAL   "\x1b[01;30m"
#define WHITE      "\x1b[01;37m"
#define RESET      "\x1b[0;0m"
#define COLOR_SIZEOF 10  // useful if you want to use snprintf etc.
//  
#else 
//
#define RED      "" 
#define ORANGE   "" 
#define MOSS     "" 
#define GREEN    "" 
#define YELLOW   "" 
#define BROWN    "" 
#define NAVY     "" 
#define BLUE     "" 
#define PURPLE   "" 
#define PINK     "" 
#define TEAL     "" 
#define CYAN     "" 
#define BLACK    "" 
#define GREY     "" 
#define CHARCOAL "" 
#define WHITE    "" 
#define RESET    ""
#define COLOR_SIZEOF 0
//
#endif // COLOR_ON
//

#define P_RED(X)      printf(RED "%s" RESET, X)  
#define P_ORANGE(X)   printf(ORANGE "%s" RESET, X)
#define P_MOSS(X)     printf(MOSS "%s" RESET, X)
#define P_GREEN(X)    printf(GREEN "%s" RESET, X)
#define P_YELLOW(X)   printf(YELLOW "%s" RESET, X)
#define P_BROWN(X)    printf(BROWN "%s" RESET, X)
#define P_NAVY(X)     printf(NAVY "%s" RESET, X) 
#define P_BLUE(X)     printf(BLUE "%s" RESET, X)
#define P_PURPLE(X)   printf(PURPLE "%s" RESET, X)
#define P_PINK(X)     printf(PINK "%s" RESET, X)
#define P_TEAL(X)     printf(TEAL"%s" RESET, X) 
#define P_CYAN(X)     printf(CYAN "%s" RESET, X)
#define P_BLACK(X)    printf(BLACK "%s" RESET, X)
#define P_GREY(X)     printf(GREY "%s" RESET, X) 
#define P_CHARCOAL(X) printf(CHARCOAL "%s" RESET, X)
#define P_WHITE(X)    printf(WHITE "%s" RESET, X)

#define SHOW_COLOR_HELP() {\
P_WHITE    ("Color map:\n");\
P_RED      ("RED, ");\
P_ORANGE   ("ORANGE, ");\
P_MOSS     ("MOSS, ");\
P_GREEN    ("GREEN, ");\
P_YELLOW   ("YELLOW, ");\
P_BROWN    ("BROWN, ");\
P_NAVY     ("NAVY, ");\
P_BLUE     ("BLUE, ");\
P_PURPLE   ("PURPLE, ");\
P_PINK     ("PINK,\n");\
P_TEAL     ("TEAL, ");\
P_CYAN     ("CYAN,");\
P_WHITE    ("--> ");\
P_BLACK    ("BLACK ");\
P_WHITE    ("<-- BLACK, ");\
P_GREY     ("GREY, ");\
P_CHARCOAL ("CHARCOAL, ");\
P_WHITE    ("WHITE, ");\
printf(RESET "RESET: Normal text\n\n"\
"Every color has a macro, add P_ to the name, eg.: P_PURPLE(\"Your text\");\n"\
"To use a color in printf, do: printf(COLOR \"Text = %%d \" RESET, variable);\n"\
"The #define COLOR_SIZEOF provides the string length of the colors.\n"\
"To switch off colours, add #define COLOR_ON 0 before including <color.h>.\n"\
"if you forget a RESET and your terminal is affected, type " PINK "stty sane" RESET ".\n");\
} 
#endif // __COLOR_H

/*************************************************
// test code for color.h

#include <stdio.h>
// #define COLOR_ON 0  // uncomment to switch colors off
#include <color.h>

int main(int argc, char *argv[])
{
    SHOW_COLOR_HELP();
    return 0;
}

**************************************************/
