EXE = p4_client p4_server
CFLAGS = -Wall
CXXFLAGS = -Wall
LDLIBS =
CC = gcc
CXX = g++

.PHONY: all
all: $(EXE)

# Implicit rules defined by Make, but you can redefine if needed
#
p4_client: p4_client.c
	$(CC) $(CFLAGS) p4_client.c $(LDLIBS) -o p4_client

p4_server: p4_server.c
	$(CC) $(CFLAGS) p4_server.c $(LDLIBS) -o p4_server
#
# OR
#
#p4_client: p4_client.cc
#	$(CXX) $(CXXFLAGS) p4_client.cc $(LDLIBS) -o p4_client
#
#p4_server: p4_server.cc
#	$(CXX) $(CXXFLAGS) p4_server.cc $(LDLIBS) -o p4_server
#

.PHONY: clean
clean:
	rm -f $(EXE)

