CC 			:= gcc
RP 			:= arm-linux-gnueabihf-gcc
CFLAGS 		:= -Iinclude
BIN			:= bin
SRC			:= src
INCLUDE		:= include
CLIENT 		:= client
SERVER 		:= server

##
SRCSCLIENT 	:= client.c sock_cli_tcp.c

##
OBJSCLIENT 	:= $(SRCSCLIENT:.c=.o)

SRCSSERVER 	:= server.c sock_srv_tcp.c
OBJSSERVER 	:= $(SRCSSERVER:.c=.o)

##
SOURCESCLIENT	:= $(patsubst %,src/%, $(OBJSCLIENT))

SOURCESSERVER	:= $(patsubst %,src/%, $(OBJSSERVER))
SRCCLIENT1 := $(patsubst %,src/%, client.c)
SRCCLIENT2 := $(patsubst %,src/%, sock_cli_tcp.c)
OBJCLIENT1 := $(SRCCLIENT1:.c=.o)
OBJCLIENT2 := $(SRCCLIENT2:.c=.o)

vpath %.c $(SRC)
vpath %.o $(SRC)

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

# $(BIN)/$(CLIENT): $(SOURCESCLIENT)
# 	@echo "Llegue cliente"
# 	$(CC) $(CFLAGS) $^ -o $@

$(BIN)/$(CLIENT): $(SOURCESCLIENT)
	@echo "Cross-compile" 
	$(RP) $(CFLAGS) -c -o $(OBJCLIENT1) $(SRCCLIENT1)
	$(RP) $(CFLAGS) -c -o $(OBJCLIENT2) $(SRCCLIENT2)
	$(RP) $(CFLAGS) $(OBJCLIENT1) $(OBJCLIENT2) -o $@

$(BIN)/$(SERVER) : $(SOURCESSERVER)
	@echo "Llegue server"
	$(CC) $(CFLAGS) $^ -o $@

