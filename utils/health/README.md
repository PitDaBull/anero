# Intro

This directory contains tools which can be used for checking the health of **The Anero Project**, such as build/run time analyzers, lints, and other diagnostic utilities.

# Usage

Unless stated otherwise, these scripts should be executed from within the source directory where you want the checks performed, for example:

`user@host:~/dev/anero$ utils/health/clang-build-time-analyzer-run.sh`

## ClangBuildAnalyzer

`utils/health/clang-build-time-analyzer-run.sh`  
The Clang Build Analyzer helps identify culprits of slow compilation.
On the first run, the script will report that the ClangBuildAnalyzer binary is missing and will point you to another script that can clone and build the required binary.

## clang-tidy

`utils/health/clang-tidy-run-cc.sh`  
`utils/health/clang-tidy-run-cpp.sh`  
Performs lint checks on the project’s source code and stores the results in the build directory.  
More information can be found on the [clang-tidy home page](https://clang.llvm.org/extra/clang-tidy/).

## include-what-you-use

`utils/health/clang-include-what-you-use-run.sh`  
Analyzes header dependencies and provides suggestions on how to reduce complexity and improve compile-time efficiency.  
More information can be found on the [Include What You Use home page](https://include-what-you-use.org/).

## Valgrind checks

`utils/health/valgrind-tests.sh`  
This script can run valgrind’s callgrind, cachegrind, and memcheck tools against a given list of executables.
It expects **one** parameter pointing to a file containing paths to executables and their arguments, one per line. For example:

