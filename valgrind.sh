#!/usr/bin/env bash

if [ $1 = "C" ]
then
    /usr/bin/clang -ggdb src/main.c \
                         src/draw.c \
                         src/keys.c \
                         src/init.c \
                         src/init2.c \
                         src/hooks.c \
                         src/color.c \
                         src/parser.c \
                         src/ram_man.c \
                         src/interface.c \
                         src/service_func.c  -std=c99 -Wall -Werror -o ./fractol && /usr/local/bin/valgrind ./fractol
elif [ $1 = "Cpp" ]
then
    /usr/bin/clang++ -std=c++11 -stdlib=libc++  src/main.c \
                                                src/draw.c\
                                                src/keys.c\
                                                src/init.c \
                                                src/hooks.c \
                                                src/color.c \
                                                src/parser.c \
                                                src/ram_man.c \
                                                src/interface.c \
                                                src/service_func.c  -Wall -Werror -o ./fractol && /usr/local/bin/valgrind ./fractol
fi
