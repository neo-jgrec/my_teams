##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

NAME		:=	libmyprotocol.a
EXT			:=	.c

DIR			:=	src/client
SRC			:=	$(addprefix $(DIR)/,								\
					p_client_close.c								\
					p_client_create.c								\
					p_client_listen.c								\
					p_client_send_packet.c							\
				)

DIR			+=	src/server
SRC			+=	$(addprefix $(lastword $(DIR))/,					\
					p_server_close.c								\
					p_server_create.c								\
					p_server_listen.c								\
					p_server_send_packet.c							\
				)

DIR			+=	src/server/utils
SRC			+=	$(addprefix $(lastword $(DIR))/,					\
					get_client.c									\
					new_client.c									\
					select_server.c									\
					server_bind.c									\
					server_listen.c									\
					server_setsockopt.c								\
					server_socket.c									\
				)

FU_DIR		:=	tests/func

UT_DIR		:=	tests/unit
UT_SRC		:=	$(filter-out src/main.c, $(SRC))
UT_SRC		+=	$(addprefix $(UT_DIR)/,								\
				)

DIR_BUILD	:=	build
DIR_BIN		:=	$(DIR_BUILD)/bin

DIR_OBJ		:=	$(DIR_BUILD)/obj
OBJ			:=	$(patsubst %$(EXT),$(DIR_OBJ)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

UT_DIR_OBJ	:=	$(DIR_BUILD)/tests/unit
UT_OBJ		:=	$(patsubst %$(EXT),$(UT_DIR_OBJ)/%.o,$(UT_SRC))
UT_DEP		:=	$(UT_OBJ:.o=.d)

DG_DIR_OBJ	:=	$(DIR_BUILD)/debug
DG_OBJ		:=	$(patsubst %$(EXT),$(DG_DIR_OBJ)/%.o,$(SRC))
DG_DEP		:=	$(DG_OBJ:.o=.d)

DEBUG		:=	$(DIR_BIN)/debug
FU_TEST		:=	$(FU_DIR)/tester.sh
UT_TEST		:=	$(DIR_BIN)/unit_test

RM			:=	rm -rf

CC			:=	gcc
CFLAGS		:=	-iquote./include -iquote../../include				\
				-Wall -Wextra -fPIC -g
LDFLAGS		:=
CLINKER		:=	ar rc

all:				$(NAME)

define CREATE_DIR
	@if [ ! -d $(dir $@) ]; then									\
		mkdir -p $(dir $@) 											\
		&& printf "\033[93m[CREATED]\033[0m %s\n" $(dir $@)			\
		|| printf "\033[31m[ERROR]\033[0m %s\n"   $(dir $@);		\
	fi
endef

define BUILD_OBJ
	@$(RM) $(patsubst %.o,%.gcda,$@)
	@$(RM) $(patsubst %.o,%.gcno,$@)
	$(CREATE_DIR)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@								\
	&& printf "\033[32m[OK]\033[0m %s\n" $<							\
	|| printf "\033[31m[KO]\033[0m %s\n" $<
endef

$(DIR_OBJ)/%.o:		%$(EXT); $(BUILD_OBJ)
$(UT_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)
$(DG_DIR_OBJ)/%.o:	%$(EXT); $(BUILD_OBJ)

define COMPILE
	$(CREATE_DIR)
	@$(CC) -o $@ $^ $(LDFLAGS)			 							\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

define COMPILE_LIB
	$(CREATE_DIR)
	@$(CLINKER) -o $@ $^											\
	&& printf "\033[32m[SUCCES]\033[0m %s\n" $@						\
	|| printf "\033[31m[ERROR]\033[0m %s\n"  $@
endef

-include $(DEP)
$(NAME):			$(OBJ); 	$(COMPILE_LIB)

tests_functional:	$(FU_TEST) $(NAME)
	@$^

-include $(UT_DEP)
$(UT_TEST):			LDFLAGS += -lcriterion --coverage
$(UT_TEST):			$(UT_OBJ);	$(COMPILE)
tests_unit:			$(UT_TEST)
	@cp $(UT_TEST) $(UT_DIR_OBJ)
	@$(UT_DIR_OBJ)/$(notdir $<)

-include $(DG_DEP)
$(DEBUG):			CFLAGS += -g -DDEBUG
$(DEBUG):			$(DG_OBJ); 	$(COMPILE_LIB)
debug:				$(DEBUG)

tests_run:			tests_functional tests_unit
	gcovr $(UT_DIR_OBJ) --exclude tests/
	gcovr $(UT_DIR_OBJ) --exclude tests/ --branches

clean:
	@[ -d $(DIR_BUILD) ]											\
	&& $(RM) $(DIR_BUILD)											\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean
	@[ -f $(NAME) ]													\
	&& $(RM) $(NAME)												\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(NAME) || true

re:					fclean all

.PHONY:				all tests tests_run debug clean fclean re doc

.SILENT:			all tests tests_run debug clean fclean re doc
