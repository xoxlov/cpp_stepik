#!/bin/bash

# man nm
nm ./libHello.so

# in case of hello.cpp find the function "_Z13hello_messagePKc" and use:
# c++filt _Z13hello_messagePKc
# to prevent this case use in hello.cpp:
# extern "C" void hello_message(const char *name);

