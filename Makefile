NAME        = scop
CC          = clang
CFLAGS      = -Wall -Wextra -Werror -O3 -fsanitize=address

HEADERS_DIR = ./includes
SRCS_DIR    = ./srcs
OBJS_DIR    = ./objs

HEADERS     = scop.h typedefs.h
HEADERS    := $(addprefix $(HEADERS_DIR)/, $(HEADERS))
SRCS        = main.c gl_context.c loop.c create_shader_program.c
SRCS       += register_events.c handle_exit.c handle_keyboard.c
OBJS        = $(SRCS:.c=.o)

LIBFT       = libft.a
LIBFT_DIR   = ./libft
LIBFT_INCL  = $(LIBFT_DIR)/includes/

INCLUDES    = -I $(HEADERS_DIR) -I $(LIBFT_INCL)
LIBRARIES   = -L. -lft -lSDL2 -lGL -lGLEW

TO_LINKING  = $(addprefix $(OBJS_DIR)/, $(OBJS)) $(INCLUDES) $(LIBRARIES)

SUB_DIR     = opengl events
VPATH       = $(SRCS_DIR) $(addprefix $(SRCS_DIR)/, $(SUB_DIR)) $(OBJS_DIR)


.PHONY: all clean fclean re


all         : $(NAME)

$(NAME)     : $(LIBFT) $(OBJS_DIR) $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(NAME) $(TO_LINKING)
	@printf "\n\e[38;5;46m%-40s SUCCESSFUL BUILD 🖥\e[0m\n" ./$(NAME)

$(LIBFT)    :
	make -C $(LIBFT_DIR)
	cp $(LIBFT_DIR)/$(LIBFT) .

$(OBJS_DIR) :
	mkdir $(OBJS_DIR)

$(OBJS)     : %.o : %.c
	@$(CC) $(CFLAGS) -c $< -o $(OBJS_DIR)/$@ $(INCLUDES)
	@printf "%-40s \e[38;5;49mcompiled\e[0m\n" $<

clean       :
	rm -rf $(OBJS_DIR)

fclean      : clean
	rm -f $(LIBFT)
	rm -f $(NAME)

re          : fclean all
