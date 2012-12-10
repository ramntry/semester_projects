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

ALL_OPTIONS = $(CXXFLAGS) $(CUSTOM_INCLUDEPATH) $(CLANG_INCLUDEPATH) $(CUSTOM_LIBS) $(CLANG_LIBS) $(LLVM_CONFIG)

BASE_DIR = ./src/base
RULES_DIR = ./src/rules
OBJ_DIR = ./obj

all: simple2

$(OBJ_DIR)/simple2.o: simple2.cpp $(BASE_DIR)/ASTUnitWrapper.h $(BASE_DIR)/BaseAction.h $(RULES_DIR)/private_data_members_matching.h $(RULES_DIR)/top_level_decl_order_checking.h
	$(CXX) simple2.cpp -o $@ -c $(ALL_OPTIONS)

$(OBJ_DIR)/BaseConsumer.o: $(BASE_DIR)/BaseConsumer.cpp $(BASE_DIR)/BaseConsumer.h
	$(CXX) $(BASE_DIR)/BaseConsumer.cpp -o $@ -c $(ALL_OPTIONS)

$(OBJ_DIR)/private_data_members_matching.o: $(RULES_DIR)/private_data_members_matching.cpp $(RULES_DIR)/private_data_members_matching.h $(BASE_DIR)/BaseConsumer.h $(BASE_DIR)/BaseVisitor.h
	$(CXX) $(RULES_DIR)/private_data_members_matching.cpp -o $@ -c $(ALL_OPTIONS)

$(OBJ_DIR)/top_level_decl_order_checking.o: $(RULES_DIR)/top_level_decl_order_checking.cpp $(RULES_DIR)/top_level_decl_order_checking.h $(BASE_DIR)/BaseConsumer.h $(BASE_DIR)/BaseVisitor.h
	$(CXX) $(RULES_DIR)/top_level_decl_order_checking.cpp -o $@ -c $(ALL_OPTIONS)

simple2: $(OBJ_DIR)/simple2.o $(OBJ_DIR)/private_data_members_matching.o $(OBJ_DIR)/top_level_decl_order_checking.o $(OBJ_DIR)/BaseConsumer.o
	$(CXX) $^ -o $@ $(ALL_OPTIONS)

run:
	./simple2 example.cpp $(SYSTEM_INCLUDE_PATH)

clean:
	rm $(OBJ_DIR)/*.o
