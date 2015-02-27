#!/bin/bash

find * -name "*.hpp" -exec clang-format -i {} +

find * -name "*.cpp" -exec clang-format -i {} +
