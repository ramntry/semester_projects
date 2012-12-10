LLVM_BASE_PATH  = /home/ramntry/clang/llvm
LLVM_SRC_PATH   = $(LLVM_BASE_PATH)/llvm
LLVM_BUILD_PATH = $(LLVM_BASE_PATH)/build_cmake
LLVM_BIN_PATH   = $(LLVM_BUILD_PATH)/bin

LLVM_CONFIG_OPTIONS = --cxxflags --ldflags --libs core mc mcparser
LLVM_CONFIG = `$(LLVM_BIN_PATH)/llvm-config $(LLVM_CONFIG_OPTIONS)` -ldl

CXX                 = clang++ -Qunused-arguments
DEFINES             =
STANDARD            = -std=c++0x
CXXFLAGS            = -fno-rtti -O2 -g3 $(STANDARD) $(DEFINES)

CUSTOM_INCLUDEPATH = \

CLANG_INCLUDEPATH = \
	-I$(LLVM_SRC_PATH)/tools/clang/include \
	-I$(LLVM_BUILD_PATH)/tools/clang/include \

SYSTEM_INCLUDE_PATH = \
	-I/usr/include \
	-I/usr/include/x86_64-linux-gnu \
	-I/usr/include/c++/4.7 \
	-I/usr/include/c++/4.7/x86_64-linux-gnu \
	-I/usr/lib/gcc/x86_64-linux-gnu/4.7/include \

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

ALL_CXX_OPTIONS = $(CXXFLAGS) $(CUSTOM_INCLUDEPATH) $(CLANG_INCLUDEPATH) $(LLVM_CONFIG)
ALL_LINK_OPTIONS = $(CUSTOM_LIBS) $(CLANG_LIBS) $(LLVM_CONFIG)

all: simple2

simple2.o: simple2.cpp
	$(CXX) $^ -o $@ -c $(ALL_CXX_OPTIONS)

BaseConsumer.o: BaseConsumer.cpp BaseConsumer.h
	$(CXX) BaseConsumer.cpp -o $@ -c $(ALL_CXX_OPTIONS)

private_data_members_matching.o: private_data_members_matching.cpp private_data_members_matching.h
	$(CXX) private_data_members_matching.cpp -o $@ -c $(ALL_CXX_OPTIONS)

top_level_decl_order_checking.o: top_level_decl_order_checking.cpp top_level_decl_order_checking.h
	$(CXX) top_level_decl_order_checking.cpp -o $@ -c $(ALL_CXX_OPTIONS)

simple2: simple2.o BaseConsumer.o private_data_members_matching.o top_level_decl_order_checking.o
	$(CXX) $^ -o $@ $(ALL_LINK_OPTIONS)

run:
	./simple2 example.cpp $(SYSTEM_INCLUDE_PATH)

clean:
	rm *.o
