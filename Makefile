# Template rom A4
#
# Universal makefile for single C++ program
#
# Use gcc flag -MMD (user) or -MD (user/system) to generate dependencies among source files.
# Use make default rules for commonly used file-name suffixes and make variables names.
#
# % make [ a.out ]

########## Variables ##########

CXX = g++                    						# compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD     # compiler flags
TARGET = chess                    					# executable name

SOURCES = $(wildcard *.cc)          				# source files (.cc)
OBJECTS = ${SOURCES:.cc=.o}            				# object files forming executable
DEPS = ${OBJECTS:.o=.d}            					# substitute ".o" with ".d"

########## Targets ##########

all: $(TARGET)

${TARGET} : ${OBJECTS}                				# link step, additional object files before $^
	${CXX} ${CXXFLAGS} -o $@ $^        				

%.o: %.cc											# rule to compile source files into object files
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include ${DEPS}                					# include *.d files containing program dependences

clean :                        						# remove files that can be regenerated
	rm -f ${DEPS} ${OBJECTS} ${TARGET}

.PHONY: all clean                    				# not file names
