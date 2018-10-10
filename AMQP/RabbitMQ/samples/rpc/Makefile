CXX = g++

CXXFLAGS = -O2 -g -Wall -std=c++11

OBJS_C = rpc_c.cpp
OBJS_P = rpc_p.cpp


RabbitMQ_DIR = ../../rabbitmq-c-0.9.0

INCLUDE_DIR = -I$(RabbitMQ_DIR)/include

LIBS =-L$(RabbitMQ_DIR)/lib64 -lrabbitmq


TARGET_C = rpc_c
TARGET_P = rpc_p

TARGET = $(TARGET_C) $(TARGET_P)

all:$(TARGET)

$(TARGET_C):$(OBJS_C)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(OBJS_C) -o $(TARGET_C) $(LIBS)

$(TARGET_P):$(OBJS_P)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(OBJS_P) -o $(TARGET_P) $(LIBS)
	

clean:
	rm -f  $(TARGET)
	