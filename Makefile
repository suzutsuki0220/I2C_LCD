debug=1

TARGET=display
OBJECTS=i2c_access.o ST7032_I2C.o
CPP=g++
LIBS=

ifeq ($(debug), 1)
	CPPFLAGS=-g -Wall
else
	CPPFLAGS=-O2 -Wall
endif

.PHONY: all clean

all: $(TARGET)

%.o: %.c %.h
	$(CPP) $(CPPFLAGS) -o $@ -c $<

$(TARGET): $(OBJECTS) main.cpp
	$(CPP) $(CPPFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET) $(OBJECTS) *~
