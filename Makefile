CC = gcc
CFLAGS = -Wall -Iinclude
SRCDIR 		:= src
BIN		:= bin
SRC		:= src
INCLUDE	:= include
LIB		:= lib
EXECUTABLE := main
SOURCEDIRS	:= $(shell find $(SRC) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
#SOURCESCLIENT		:= $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))
#OBJECTS= client.c sock_cli_tcp.c server.c sock_srv_tcp.c
OBJECTS:=$(wildcard *.c)
CLIENT = client
SERVER = server
SRCSCLIENT = client.c sock_cli_tcp.c
OBJSCLIENT := $(SRCSCLIENT:.c=.o)
SRCSSERVER = server.c sock_srv_tcp.c
OBJSSERVER := $(SRCSSERVER:.c=.o)
SOURCESCLIENT	:= $(patsubst %,src/%, $(OBJSCLIENT))
SOURCESSERVER	:= $(patsubst %,src/%, $(OBJSSERVER))
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
CLIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

vpath %.c src
#vpath %.h include
vpath %.o src

# test:
# 	@echo $(SOURCEDIRS)
# 	@echo $(INCLUDEDIRS)
# 	@echo $(SOURCESCLIENT)

# # all: cliente $(CLIENT) servidor $(SERVER)
# # 	@echo All done

# cliente : $(SRCSCLIENT)
# 	@echo "Compiling client..."
# 	$(CC) -c $(CFLAGS) $^

# $(CLIENT) : $(OBJSCLIENT)
# 	@echo "Linking client..."
# 	$(CC) -Iinclude $(SRCDIR)/$^ -o $@ 
# 	@echo $(OBJSCLIENT)

# servidor : $(SRCSSERVER)
# 	@echo "Compiling server..."
# 	$(CC) -c $(CFLAGS) $^

# $(SERVER) : $(OBJSSERVER)
# 	@echo "Linking server..."
# 	$(CC) -Iinclude $(OBJSCLIENT) -o $@ 
# 	@echo $(OBJSSERVER)

# clean:
# 	@echo "Cleaning..."
# 	rm -rf *o client server

#server:
#	gcc -o server server.c sock_srv_tcp.c

all: $(BIN)/$(CLIENT) $(BIN)/$(SERVER)

.PHONY: clean
clean:
	-$(RM) $(BIN)/$(CLIENT)
	-$(RM) $(BIN)/$(SERVER)
	-$(RM) $(SOURCESCLIENT)
	-$(RM) $(SOURCESSERVER)

run: all
	./$(BIN)/$(EXECUTABLE)

$(BIN)/$(CLIENT): $(SOURCESCLIENT)
	@echo "Llegue cliente"
	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/$(SERVER) : $(SOURCESSERVER)
	@echo "Llegue server"
	$(CC) $(CFLAGS) $^ -o $@