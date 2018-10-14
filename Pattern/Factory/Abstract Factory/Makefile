CXX = g++

CXXFLAGS = -O2 -g -Wall -std=c++11

OBJS = main.cpp



COMPILE_OPTION = \
  -I./ \

  
INCLUDE_DIR = $(COMPILE_OPTION)

LINK_OPTION	= -L/usr/lib64/ -lpthread


TARGET = test

$(TARGET):$(OBJS_C)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(OBJS) -o $(TARGET) $(LINK_OPTION)

all:$(TARGET)
	
clean:
	rm -f  $(TARGET)
	