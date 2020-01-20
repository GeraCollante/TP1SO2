clear
gcc -o server sock_srv_i_cc.c
gcc -o cliente sock_cli_i_cc.c
konsole --noclose -e xterm -hold -e ./cliente && ./server