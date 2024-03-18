##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

DIR_BUILD	:=	build

MAKEFILES	:=	./libs/protocol/Makefile								\
				./client/Makefile										\
				./server/Makefile

RM			:=	rm -rf

define EXECUTE
	@for MAKEFILE in $(MAKEFILES); do									\
		$(MAKE) -sC $$(dirname $$MAKEFILE) $@;							\
	done
endef

all:				; $(EXECUTE)

tests_functional:	; $(EXECUTE)

tests_unit:			; $(EXECUTE)

debug:				; $(EXECUTE)

tests_run:			; $(EXECUTE)

$(DIR_BUILD):
	@[ ! -d $(DIR_BUILD) ]											\
	&& mkdir -p $(DIR_BUILD) 										\
	&& printf "\033[93m[CREATED]\033[0m %s\n" $(DIR_BUILD)			\
	|| printf "\033[31m[ERROR]\033[0m %s\n"   $(DIR_BUILD)

docs:				$(DIR_BUILD)
	git submodule update --init --recursive
	doxygen docs/Doxyfile
	python -m webbrowser -t build/docs/index.html >/dev/null

clean:				; $(EXECUTE)
	@[ -d $(DIR_BUILD) ]											\
	&& $(RM) $(DIR_BUILD)											\
	&& printf "\033[31m[DELETED]\033[0m %s\n" $(DIR_BUILD) || true

fclean:				clean ; $(EXECUTE)

re:					fclean all

.PHONY:				all tests tests_run debug clean fclean re docs

.SILENT:			all tests tests_run debug clean fclean re docs
