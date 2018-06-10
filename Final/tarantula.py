#!/usr/bin/env python
#   Zachary DeVita
#   March 3, 2016
#   CS 362 Final

from __future__ import division

import sys
import os
import subprocess
import re

def printc_red(msg):
    print '\033[91m' + msg + '\033[0m'

def printc_yellow(msg):
    print '\033[93m' + msg + '\033[0m'

def printc_green(msg):
    print '\033[92m' + msg + '\033[0m'

def count_lines(fname):
    return len(open(fname, 'r').readlines())

def print_line(suspiciousness, msg):
    if suspiciousness <= .2:
        print(msg)
    else if suspiciousness <= .5:
        printc_green(msg)
    else if suspiciousness <= .7:
        printc_yellow(msg)
    else:
        printc_red(msg)

def suspiciousness(passed, failed, totalpassed, totalfailed):
    numerator = failed / totalfailed
    denominator = passed / totalpassed + numerator
    return (1 - numerator / denominator)

def main():
    source_file = 'dominion.c'
    total_lines = count_lines(source_file)
    line_num = 0
    tests = 1000
    passed = numpy.empty(total_lines, dtype=int)
    failed = numpy.empty(total_lines, dtype=int)
    totalpassed = 0
    totalfailed = 0
    
    for x in range(0, tests):
        errno = subprocess.call(["make clean all"], shell=True)
        isFail = subprocess.check_output(["./minetest"])

        totalfailed += int(isFail)
        totalpassed += (1 - int(isFail))
        output = subprocess.check_output(["gcov dominion.c"], shell=True)
        gcovFile = open("dominion.c.gcov", "r")

        for line in gcovFile:
            a,b,c = line.split(':')
            if('-' in a or '#####' in a):
                continue
            if(int(isFail)):
                failed[int(b)] += 1
            else:
                passed[int(b)] += 1

    dominion = open(source_file,"r")

    for line in dominion:
        s = suspiciousness(passed[line_num], failed[line_num], totalpassed, totalfailed)
        print_line(s, line)
        line_num += 1

if __name__ == '__main__':
    main()