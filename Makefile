NAME		= cub3D

CC			= cc
CFLAGS		= -Wall -Wextra -Wextra
RM			= rm -rf

SRCS_DIR		= ./srcs
OBJS_DIR		= ./objects
INC_DIR		= ./includes
LDFLAG		= .ldl -lglfw -pthread -lm

LIBFT_DIR	= # TO ADD: library directory for libft#
LIBFT_LIB	= # TO ADD: path to libft.a

MLX_DIR		= ./MLX42
MLX_LIB		= $(MLX_BUILD)/libmlx42.a
MLX_BUILD	= $(MLX_DIR)/build

SRCS		= # TO ADD

OBJS		= $(SRCS: %.c .c%.o)
INCLUDES	= -I$(INC_DIR) \
					-I$(MLX_DIR)/includes \
					# libft path-I$( ) \

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_DIR)/libft.a
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) $(MLX_LIB) $(LDFLAGS) -o $(NAME)
	@echo "✅ Build $(GREEN)$(NAME) $(NC)successfully! 🎉"

$(MLX_LIB):
		cmake $(MLX_DIR) -B $(MLX_BUILD) && make -C $(MLX_BUILD) -j4

$(LIBFT_LIB):
		$(MAKE) -C $(LIBFT_DIR)

clean:
	@$(RM) $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@echo "🧹 Objects of $(NAME) are removed! -> 🗑️"

fclean: clean
		$(RM) $(OBjS)
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(MAKE) -C $(MLX_DIR) fclean
		@echo "🧹 \033[0;31mFull clean complete.\033[0m 🗑️"

re: fclean all

.PHONY : all clean fclean re
.SECONDARY : $(OBJS)
