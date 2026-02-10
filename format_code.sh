#!/bin/bash

find . \( -name "*.cpp" -o -name "*.h" \) -print0 | \
xargs -0 clang-format -i
