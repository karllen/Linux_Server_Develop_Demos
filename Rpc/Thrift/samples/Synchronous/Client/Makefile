CXX = g++

CXXFLAGS = -O2 -g -Wall -std=c++11

OBJS = StressTest_types.cpp StressTest_constants.cpp StressTestClient.cpp Service.cpp

G_THRIFT   = ../../../library/thrift
G_EVENT    = ../../../library/libevent
G_USR_LOCAL    = /usr/local/include

COMPILE_OPTION = \
  -I./ \
  -I$(G_THRIFT)/include \
  -I$(G_EVENT)/include \
  -I$(G_USR_LOCAL) \
  
INCLUDE_DIR = $(COMPILE_OPTION)

LINK_OPTION	= -L$(G_THRIFT)/lib -lthrift -lthriftz -lthriftnb\
			-L$(G_EVENT)/lib -levent\

TARGET = syncClient

$(TARGET):$(OBJS_C)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(OBJS) -o $(TARGET) $(LINK_OPTION)

all:$(TARGET)
	
clean:
	rm -f  $(TARGET)
	