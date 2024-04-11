##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

LIB 		= ../libs/protocol

CLIENT 		= ./client
SERVER 		= ./server

all:
	@ $(MAKE) -s -C $(LIB)
	@ $(MAKE) -s -C $(CLIENT)
	@ $(MAKE) -s -C $(SERVER)

clean:
	@ $(MAKE) clean -s -C $(LIB)
	@ $(MAKE) clean -s -C $(CLIENT)
	@ $(MAKE) clean -s -C $(SERVER)

fclean:
	@ $(MAKE) fclean -s -C $(LIB)
	@ $(MAKE) fclean -s -C $(CLIENT)
	@ $(MAKE) fclean -s -C $(SERVER)

re: fclean all