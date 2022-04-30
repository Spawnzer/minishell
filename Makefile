NAME= minishell

AR= ar rc
RM= rm -rf

CC= gcc
CFLAGS= -Wall -Werror -Wextra -g -c

SDIR= srcs
ODIR= objs
BDIR= srcs/builtins
EDIR= srcs/exec

SRCS= main.c

BUILTINS=  builtin_echo.c builtin_cd.c builtin_pwd.c builtin_export.c builtin_unset.c builtin_utils_env.c builtin_utils_env2.c builtin_utils_env3.c builtin_env.c builtin_exit.c env_init.c
EXEC= access.c heredoc.c signal.c
OBJS= $(SRCS:.c=.o) $(BUILTINS:.c=.o) $(EXEC:.c=.o)

SFIX= $(addprefix $(SDIR)/, $(SRCS))
OFIX= $(addprefix $(ODIR)/, $(OBJS))
BFIX= $(addprefix $(BDIR)/, $(BUILTINS)) 
EFIX= $(addprefix $(EDIR)/, $(EXEC)) 

VPATH= $(SDIR) $(BDIR) $(EDIR)


all: $(NAME)

$(ODIR)/%.o: %.c
			$(CC) $(CFLAGS) -I./libft/libsrcs -I./incls -I. $< -o $@

$(ODIR):
		mkdir -p $(ODIR)

$(NAME): $(ODIR) $(OFIX)
		$(MAKE) -C ./libft
		$(CC) $(OFIX) -lft -L./libft -Llibread -lreadline -lcurses -o $(NAME)

clean: 
		$(MAKE) clean -C ./libft
		$(RM) $(ODIR)


fclean: clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)


re: clean all


val: all
	valgrind ./minishell --leak-check-full --track-origins=yes -s --trace-children=yes --show-leak-kinds=all --show-reachable=yes

.PHONY: all clean fclean re val