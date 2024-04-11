##
## EPITECH PROJECT, 2024
## my_teams
## File description:
## Makefile
##

MAKEFILES	:=	./client/Makefile										\
				./server/Makefile

define EXECUTE
	@for MAKEFILE in $(MAKEFILES); do									\
		$(MAKE) -sC $${MAKEFILE%/*} $@;									\
	done
endef

all:				; $(EXECUTE)

debug:				; $(EXECUTE)

tests_functional:	; $(EXECUTE)

tests_unit:			; $(EXECUTE)

tests_run:			; $(EXECUTE)

clean:				; $(EXECUTE)

fclean:				clean ; $(EXECUTE)

re:					fclean all

.PHONY:				all debug tests_functional tests_unit tests_run	\
					clean fclean re

.SILENT:			all debug tests_functional tests_unit tests_run	\
					clean fclean re
