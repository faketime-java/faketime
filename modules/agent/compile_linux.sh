#!/bin/sh
gcc -O2 -fPIC -pthread -c -I $JAVA_HOME/include -I $JAVA_HOME/include/linux src/main/c/agent.c
gcc -z defs -static-libgcc -shared -o src/main/resources/linux_x86_32/libfaketime agent.o -lc
rm agent.o

gcc -O2 -fPIC -pthread -D_LP64=1 -c -I $JAVA_HOME/include -I $JAVA_HOME/include/linux src/main/c/agent.c
gcc -z defs -static-libgcc -shared -o src/main/resources/linux_x86_64/libfaketime agent.o -lc
rm agent.o
