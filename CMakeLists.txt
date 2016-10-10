cmake_minimum_required(VERSION 3.6)
project(clang_test)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CLANG_DIR "/home/kobzol/libraries/llvm3.8-binaries")
set(Z3_DIR "/home/kobzol/libraries/z3/build/build")

set(CMAKE_CXX_COMPILER "${CLANG_DIR}/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fno-rtti -Wsign-compare -Wall -pedantic -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS")

include_directories(${CLANG_DIR}/include)
link_directories(${CLANG_DIR}/lib)

include_directories(${Z3_DIR}/include)
link_directories(${Z3_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/src)

set(CLANG_LIB
    clangFrontend
    clangSerialization
    clangDriver
    clangParse
    clangSema
    clangAnalysis
    clangAST
    clangBasic
    clangEdit
    clangLex
    clangTooling
    LLVMX86AsmParser # MC, MCParser, Support, X86Desc, X86Info
    LLVMX86Desc # MC, Support, X86AsmPrinter, X86Info
    LLVMX86AsmPrinter # MC, Support, X86Utils
    LLVMX86Info # MC, Support, Target
    LLVMX86Utils # Core, Support
    LLVMipo
    LLVMScalarOpts
    LLVMInstCombine
    LLVMTransformUtils
    LLVMAnalysis
    LLVMTarget
    LLVMOption # Support
    LLVMMCParser # MC, Support
    LLVMMC # Object, Support
    LLVMObject # BitReader, Core, Support
    LLVMBitReader # Core, Support
    LLVMCore # Support
    LLVMSupport
    pthread
    dl
)

set(Z3_LIB z3)


# Project
add_library(src
    src/context.cpp
        src/solver/solver.cpp
        src/ast/driver.cpp
        src/program/function.cpp
        src/solver/expr_builder.cpp
        src/program/path.cpp
    src/variable/variable.cpp
    src/variable/int_variable.cpp src/ast/visitor.cpp src/program/declaration.cpp src/util.cpp src/program/evaluator.cpp)

add_executable(clang_test main.cpp)
target_link_libraries(clang_test src)
target_link_libraries(clang_test ${CLANG_LIB})
target_link_libraries(clang_test ${Z3_LIB})


# Test
set(TEST_SOURCE_FILES
    test/util.cpp
    test/run_test.cpp
    test/test_solver.cpp
    test/test_variable.cpp
    test/test_function.cpp
)

add_executable(unittest ${TEST_SOURCE_FILES})
target_link_libraries(unittest src)
target_link_libraries(unittest ${CLANG_LIB})
target_link_libraries(unittest ${Z3_LIB})