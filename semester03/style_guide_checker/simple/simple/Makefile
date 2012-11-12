LLVM_BASE_PATH  = /home/ramntry/clang/llvm
LLVM_SRC_PATH   = $(LLVM_BASE_PATH)/llvm
LLVM_BUILD_PATH = $(LLVM_BASE_PATH)/build_cmake
LLVM_BIN_PATH   = $(LLVM_BUILD_PATH)/bin

LLVM_CONFIG_OPTIONS = --cxxflags --ldflags --libs core mc mcparser
LLVM_CONFIG = `$(LLVM_BIN_PATH)/llvm-config $(LLVM_CONFIG_OPTIONS)` -ldl

CXX                 = clang++
DEFINES             =
STANDARD            = -std=c++11
CXXFLAGS            = -fno-rtti -O2 -g3 $(STANDARD) $(DEFINES)

CUSTOM_INCLUDEPATH = \

CLANG_INCLUDEPATH = \
	-I$(LLVM_SRC_PATH)/tools/clang/include \
	-I$(LLVM_BUILD_PATH)/tools/clang/include \

CUSTOM_LIBS = \

CLANG_LIBS = \
	-lclangFrontendTool \
	-lclangFrontend \
	-lclangDriver \
	-lclangSerialization \
	-lclangCodeGen \
	-lclangParse \
	-lclangSema \
	-lclangStaticAnalyzerFrontend \
	-lclangStaticAnalyzerCheckers \
	-lclangStaticAnalyzerCore \
	-lclangAnalysis \
	-lclangARCMigrate \
	-lclangRewriteCore \
	-lclangEdit \
	-lclangAST \
	-lclangLex \
	-lclangBasic \


all: simple

simple: simple.cpp top_level_decl_order_checking.cpp private_data_members_matching.cpp
	$(CXX) $^ $(CXXFLAGS) -o $@ \
	$(CUSTOM_INCLUDEPATH) $(CLANG_INCLUDEPATH) \
	$(CUSTOM_LIBS) $(CLANG_LIBS) \
	$(LLVM_CONFIG)

