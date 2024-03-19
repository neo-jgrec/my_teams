##
## EPITECH PROJECT, 2024
## Arcade
## File description:
## Makefile
##

include Makefile_colors.mk

LIB 		= libmyprotocol.a
CC 			= gcc

VPATH 		:= ./src

vpath %.c $(VPATH)

SRC 		:= p_client_create.c
SRC 		+= p_client_listen.c
SRC 		+= p_server_create.c
SRC 		+= p_server_listen.c
SRC 		+= p_client_send_packet.c
SRC 		+= p_server_send_packet.c

CFLAGS 		= -Wall -Werror

BUILD_DIR 	= build
OBJ 		:= $(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS 		= -iquote./include -iquote../include -Wall -Wextra
AR			= ar

DIE         = exit 1
ECHO        = echo -e

%.c:
	@ $(ECHO) "${_B_RED}[ERROR]${_END} File ${_B_WHITE}$@${_END} not found."
	@ $(ECHO) "${_B_RED}===============> $(LIB) <================${_END}\n\n"
	@ $(DIE)

all: $(LIB)
	@ $(ECHO) "${_B_GREEN}[OK]${_END} Compilation of ${_B_WHITE}$(LIB)${_END} done."
	@ $(ECHO) "${_B_GREEN}===============> $(LIB) <================${_END}\n\n"

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(@D)
	@ $(CC) -g $(LIBFLAGS) -c $< -o $@
	@ $(ECHO) "${_CYAN}[OK]$(_END)	-> $(CC)    $(_U_WHITE)$<$(_END)"

$(LIB): $(OBJ) $(SRC)
	@ mkdir -p $(BUILD_DIR)
	@ $(AR) rc $(LIB) $(OBJ)
	@ $(ECHO) "${_CYAN}[OK]$(_END)	-> $(AR)    $(_U_WHITE)$@$(_END)"
	@ $(ECHO) "$(_B_PURPLE)[STATS]$(_END)	-> \
	$(shell echo "$?" | wc -w) file(s) compiled${_END}."

clean:
	@ $(RM) *.gcda
	@ $(RM) *.gcno
	@ $(RM) *.gcov
	@ $(RM) vgcore.*
	@ $(RM) -rf $(BUILD_DIR)
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	*.gcda${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	*.gcno${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	*.gcov${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	vgcore.*${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	$(BUILD_DIR)${_END}"

fclean: clean
	@ $(RM) $(LIB)
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	$(LIB)${_END}"

re: fclean all

.PHONY: all clean fclean re
