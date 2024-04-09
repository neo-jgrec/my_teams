##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

include Makefile_colors.mk

NAME		:=	myteams_server
CC			:=	gcc

VPATH		:=	./src

vpath %.c $(VPATH)

SRC			:=	main.c

CFLAGS		:=	-Wall -Wextra -Werror -iquote./include -iquote../include
LDFLAGS		:=	-L../../libs/protocol -lmyprotocol

BUILD_DIR	:=	build
OBJ			:=	$(SRC:%.c=$(BUILD_DIR)/%.o)

CFLAGS		:=	-iquote./include -iquote../include \
				-iquote../../libs/protocol/include \
				-Wall -Wextra
AR			:=	ar

DIE			:=	exit 1
ECHO		:=	echo -e

%.c:
	@ $(ECHO) "${_B_RED}[ERROR]${_END} File ${_B_WHITE}$@${_END} not found."
	@ $(ECHO) "${_B_RED}===============> $(NAME) <================${_END}\n\n"
	@ $(DIE)

all: $(NAME)
	@ $(ECHO) "${_B_GREEN}[OK]${_END} Compilation of ${_B_WHITE}$(NAME)${_END} done."
	@ mv $(NAME) ../$(NAME)
	@ $(ECHO) "${_B_GREEN}[OK]${_END} Binary moved to ${_B_WHITE}../${_END}."
	@ $(ECHO) "${_B_GREEN}===============> $(NAME) <================${_END}\n\n"

$(BUILD_DIR)/%.o: %.c
	@ mkdir -p $(@D)
	@ $(CC) -g $(CFLAGS) -c $< -o $@
	@ $(ECHO) "${_CYAN}[OK]$(_END)	-> $(CC)    $(_U_WHITE)$<$(_END)"

$(NAME): $(OBJ) $(SRC)
	@ mkdir -p $(BUILD_DIR)
	@ $(CC) -o $(NAME) $(OBJ) $(LDFLAGS)
	@ $(ECHO) "${_CYAN}[OK]$(_END)	-> $(CC)    $(_U_WHITE)$@$(_END)"
	@ $(ECHO) "$(_B_PURPLE)[STATS]$(_END)	-> \
	$(shell echo "$?" | wc -w) file(s) compiled${_END}."
	@ $(ECHO) "$(_B_PURPLE)[STATS]$(_END)	-> \
	$(shell du -sh $(BUILD_DIR) | cut -f1) build directory size${_END}."

clean:
	@ $(RM) *.gcda
	@ $(RM) *.gcno
	@ $(RM) -r $(BUILD_DIR)
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	*.gcda${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	*.gcno${_END}"
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	-r $(BUILD_DIR)${_END}"

fclean: clean
	@ $(RM) $(NAME)
	@ $(ECHO) "${_BLACK}${_BB_WHITE}-> $(RM)	$(NAME)${_END}"

re: fclean all
