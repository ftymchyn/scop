NAME        = scop
CC          = clang
CFLAGS      = -Wall -Wextra -Werror -O3 -fsanitize=address

HEADERS_DIR = ./includes
SRCS_DIR    = ./srcs
OBJS_DIR    = ./objs

HEADERS     = scop.h
HEADERS    := $(addprefix $(HEADERS_DIR)/, $(HEADERS))
SRCS        = main.c
OBJS        = $(SRCS:.c=.o)

INCLUDES    = -I $(HEADERS_DIR)

TO_LINKING  = $(addprefix $(OBJS_DIR)/, $(OBJS)) $(INCLUDES)

VPATH       = $(SRCS_DIR) $(OBJS_DIR)


.PHONY: all clean fclean re


all         : $(NAME)

$(NAME)     : $(OBJS_DIR) $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(NAME) $(TO_LINKING)
	@printf "\n\e[38;5;46m%-40s SUCCESSFUL BUILD 🖥\e[0m\n" ./$(NAME)

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)

$(OBJS)     : %.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $(OBJS_DIR)/$@ $(INCLUDES)
	@printf "%-40s \e[38;5;49mcompiled\e[0m\n" $<

clean       :
	rm -rf $(OBJS_DIR)

fclean      : clean
	rm -f $(NAME)

re          : fclean all
