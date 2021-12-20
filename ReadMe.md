# Simple Calculator

## how to run it

if you have CMake Build System:

```
$ mkdir build && cd build
$ cmake ..
$ make && ./calc
```

## the structure of source code

### main

the main loop

### logs

provide a interface to log different type of information in terminal.

### models

provide the data structure for calculating.

### parser

convert input string to abstract data structure which provided in `models`

### calculator

provide a function to calculate the expression.

## LICENSE

Mozilla Public License v2.0