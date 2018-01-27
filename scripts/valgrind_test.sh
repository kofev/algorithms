#!/bin/bash

cd build
valgrind --error-exitcode=1 --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=definite,indirect,possible --track-fds=yes ./test/alg_example > /dev/null
