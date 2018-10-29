CXX = g++

CXXFLAGS = -O2 -g -Wall -std=c++11

OBJS = main.cpp

G_BOOST = /usr/local/include/
G_BOOST_LIB = /usr/local/lib

COMPILE_OPTION = \
	-I./ \
	-I$(G_BOOST)/ \


INCLUDE_DIR = $(COMPILE_OPTION)

LINK_OPTION = -L$(G_BOOST_LIB) -lboost_system -lboost_filesystem \
			-L/usr/local/lib64 -lpthread

TARGET = asio_threadpool

$(TARGET) :$(OBJS_C)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(OBJS) -o $(TARGET) $(LINK_OPTION)

all:$(TARGET)

clean:
	rm -f  $(TARGET)