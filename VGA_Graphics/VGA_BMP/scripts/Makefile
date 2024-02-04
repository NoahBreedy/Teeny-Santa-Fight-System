CFLAGS += -I.. -I. -Os 
CPPFLAGS += $(CFLAGS) --std=c++17
ifeq ($(OS),Windows_NT)
	RMCMD = rm
else
	RMCMD = rm -f
	UNAME_S := $(shell uname -s)
endif

all:
	g++ BMP.cpp -o convert $(CPPFLAGS) 
