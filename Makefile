##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

include Makefile_colors.mk

SERVER 	= 	server
CLIENT 	= 	client


ECHO        = echo -e

all: server client
	@ $(ECHO) "${_B_GREEN} =================== [ALL] =================== ${_END}"
	@ $(ECHO) "${_B_GREEN}[SUCCES]${_END} project compiled successfully !"

server:
	@ $(ECHO) "${_B_BLUE} =================== [SERVER] =================== ${_END}"
	@ make -s -C $(SERVER)

client:
	@ $(ECHO) "${_B_BLUE} =================== [CLIENT] =================== ${_END}"
	@ make -s -C $(CLIENT)

clean:
	@ $(ECHO) "${_B_RED} =================== [CLEAN] =================== ${_END}"
	@ make clean -s -C $(SERVER)
	@ make clean -s -C $(CLIENT)

fclean:
	@ $(ECHO) "${_B_RED} =================== [FCLEAN] =================== ${_END}"
	@ make fclean -s -C $(SERVER)
	@ make fclean -s -C $(CLIENT)

re: fclean all

.PHONY: clean fclean re
