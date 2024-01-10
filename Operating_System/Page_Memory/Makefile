DIR_PATH=$(PWD)

SRC=$(shell ls $(DIR_PATH)/src/*.cc)

BINARY=$(SRC:*.cc=*.o)

TARGET=LRU
all:depend $(TARGET)
depend:
	g++ -MM $(SRC) > .depend

-include .depend

$(TARGET):$(BINARY)
	g++ $? -g -o $@
	mv $(DIR_PATH)/$(TARGET) $(DIR_PATH)/exe

#$(BINARY):$(SRC)
#	g++ $< -c -o $@

clean:
	@rm -f .depend

print:
	@echo "After restarting compiling......"
	@echo @?
