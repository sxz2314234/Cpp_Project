CXX=gcc
SRC=$(wildcard *.cc) 
BINARY=$(SRC:%.cc=%.o)
INCLUDE=-I /home/sxz/C++/database/includes

FLAG=-g -std=c++11 -lstdc++ `mysql_config --cflags --libs`
TARGET=Database
all:$(TARGET)

$(TARGET):$(BINARY)
	$(CXX) $(FLAG) $^ -o $@

%.o:%.cc
	$(CXX) $(FLAG) -c $< -o $@ $(INCLUDE)

clean:
	rm -rf ./*.o
	rm -f $(TARGET)

move:
	rm -rf $(BINARY)
	mv $(TARGET) ../bin