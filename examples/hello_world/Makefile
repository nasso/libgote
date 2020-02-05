##
## EPITECH PROJECT, 2020
## libgote-example-hello_world
## File description:
## Makefile to build the project
##

CC		?=	gcc

SHELL	=	/bin/sh

MYFILE	=	Myfile.yml

readcfg	=	$(strip \
				$(shell sed -n '/^$(1):/,/^\S/s/^\s\+\-\|^$(1)://p' $(MYFILE)))

ALLOWED ?=	$(call readcfg,allowed)

BINTYPE	:=	$(call readcfg,type)

DEPS	:=	$(call readcfg,dependencies)

MAINSRC	:=	$(call readcfg,main)

SRC		:=	$(call readcfg,src)

NAME	:=	$(call readcfg,name)

NAMESPC :=	$(call readcfg,namespace)

TESTSRC	:=	$(call readcfg,tests_src)

LIBDIR	?=	$(abspath ./lib)

INCLUDE =	-I$(OUTDIR)/include -I$(LIBDIR)/include

CFLAGS	=	-fdiagnostics-color -fno-builtin -W -Wall -Wextra -pedantic \
			$(INCLUDE) $(if $(DEBUG),-g3) \
			$(patsubst %,-DMY_ALLOW_FUN_%,$(strip \
				$(shell echo $(ALLOWED) | tr a-z A-Z)))

CPPFLAGS =	-MD -MP

LIBS	=	$(DEPS:lib%=-l%)

TEST	=	unit-tests

OUTDIR	=	./target/$(if $(DEBUG),debug,release)

OUTNAME	=	$(OUTDIR)/$(notdir $(NAME))

OUTTEST	=	$(OUTDIR)/$(TEST)

CPPDEPS	=	$(SRC:%.c=$(OUTDIR)/%.d)

DEPSARC	=	$(DEPS:%=$(LIBDIR)/%.a)

MAINOBJ	:=	$(MAINSRC:%.c=$(OUTDIR)/%.o)

OBJ		=	$(SRC:%.c=$(OUTDIR)/%.o)

TESTOBJ	=	$(TESTSRC:%.c=$(OUTDIR)/%.o)

COVREPS	=	$(SRC:%.c=$(OUTDIR)/%.gcda) $(SRC:.c=$(OUTDIR)/%.gcno) \
			$(MAINSRC:.c=$(OUTDIR)/%.gcda) $(MAINSRC:.c=$(OUTDIR)/%.gcno) \
			$(TESTSRC:.c=$(OUTDIR)/%.gcda) $(TESTSRC:.c=$(OUTDIR)/%.gcno)

makelibs =	$(foreach lib,$(DEPS),$(MAKE) -sC $(LIBDIR) $(1) \
				NAME=$(lib) LIBDIR=$(LIBDIR);)

export CC

export SHELL

export ALLOWED

export DEBUG

all: $(NAME)

info:
	@echo "\033[0;32mname:\033[0m" $(NAME)
	@echo "\033[0;32mtype:\033[0m" $(BINTYPE)
	@echo "\033[0;32mnamespace:\033[0m" $(NAMESPC)
	@echo -n "\033[0;32mallowed:\033[0m"
	@for fn in $(ALLOWED); do echo -n " $$fn"; done
	@echo
	@echo -n "\033[0;32mdependencies:\033[0m"
	@for dep in $(DEPS); do echo -n " $$dep"; done
	@echo
	@echo "\033[0;32mmain:\033[0m" $(MAINSRC)
	@echo -n "\033[0;32msrc:\033[0m"
	@if [ '$(VERBOSE)' ]; then \
		for f in $(SRC); do echo -n "\n - $$f"; done; \
		echo; \
	else \
		echo '' $(shell echo $(SRC) | wc -w) 'file(s)'; \
	fi
	@echo -n "\033[0;32mtests:\033[0m"
	@if [ '$(VERBOSE)' ]; then \
		for f in $(TESTSRC); do echo -n "\n - $$f"; done; \
		echo; \
	else \
		echo '' $(shell echo $(TESTSRC) | wc -w) 'file(s)'; \
	fi

$(NAME): $(OUTNAME)
	@cp $< $@

$(OUTNAME): $(DEPSARC) $(OBJ) $(MAINOBJ)
	@if [ '$(BINTYPE)' = 'bin' ]; then \
		$(CC) $(CFLAGS) -o $@ $(OBJ) $(MAINOBJ) $(LIBDIR:%=-L%) $(LIBS); \
		printf '\r  \033[K\033[0;32m Finished\033[0m `%s` (binary)\n' "$@"; \
	fi
	@if [ '$(BINTYPE)' = 'lib' ]; then \
		ar -rc $@ $(OBJ); \
		printf '\r  \033[K\033[0;32m Finished\033[0m `%s` (library)\n' "$@"; \
	fi

$(DEPSARC):
	@$(call makelibs,all)

$(OUTDIR)/%.o: %.c | $(OUTDIR)
	@printf '\r  \033[K\033[0;32mCompiling\033[0m `$<`\n'
	@mkdir -p $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OUTDIR):
	@mkdir -p $@/include
	@ln -s $(abspath ./include) $@/include/$(NAMESPC)

$(TEST): $(OUTTEST)
	@cp $(OUTTEST) $(TEST)

$(OUTTEST): CFLAGS += --coverage
$(OUTTEST): LIBS += -lcriterion
$(OUTTEST): $(DEPSARC) $(OBJ) $(TESTOBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(TESTOBJ) $(LIBDIR:%=-L%) $(LIBS)
	@printf '\r  \033[K\033[0;32m Finished\033[0m %s test build\n' \
		$(if $(DEBUG),'debug','release')

run: $(NAME)
	@printf '\r  \033[K\033[0;32m  Running\033[0m `$(strip $(NAME) $(ARGS))`\n'
	@./$(NAME) $(ARGS) || printf '\033[0;31mProgram exited with %d\033[0m\n' $$?

tests_run: $(TEST)
	@printf '\r  \033[K\033[0;32m  Running\033[0m `$(TEST)`\n'
	@./$(TEST)

clean:
	@$(call makelibs,clean)
	@printf '\r  \033[K\033[0;34m Cleaning\033[0m `$(NAME)`\n'
	@rm -f $(OBJ) $(TESTOBJ) $(MAINOBJ) $(COVREPS) $(CPPDEPS) $(OUTNAME) \
		$(OUTTEST)

fclean:
	@$(call makelibs,fclean)
	@printf '\r  \033[K\033[0;36m   Wiping\033[0m `$(NAME)`\n'
	@rm -f $(OBJ) $(TESTOBJ) $(MAINOBJ) $(COVREPS) $(CPPDEPS) $(OUTNAME) \
		$(OUTTEST)
	@rm -f $(NAME) $(TEST)
	@rm -rf $(OUTDIR)

re: fclean all

retest: fclean tests_run

rerun: re run

.PHONY: all info run tests_run clean fclean re retest rerun

-include $(CPPDEPS)
