NAME		= cub3D
PARSER		= parser_test

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf

# --- PATHS ------ #
SRCS_DIR	= srcs
OBJS_DIR	= objects

LIBFT_DIR	= lib/libft
LIBFT_LIB	= $(LIBFT_DIR)/libft.a

# MLX_DIR		= ./MLX42
# MLX_LIB		= $(MLX_BUILD)/libmlx42.a
# MLX_BUILD	= $(MLX_DIR)/build

# --- Includes / Link ------ #
INCLUDES	= -I$(SRCS_DIR)/parsing -I$(LIBFT_DIR)/include
#-I$(MLX_DIR)/includes \#

#LDFLAG		= .ldl -lglfw -pthread -lm

# --- Sources (parsing module)-------------- #
PARSING_SRCS = \
	$(SRCS_DIR)/parsing/colors.c \
	$(SRCS_DIR)/parsing/get_line.c \
	$(SRCS_DIR)/parsing/map_flood.c \
	$(SRCS_DIR)/parsing/map_read.c \
	$(SRCS_DIR)/parsing/map_validate.c \
	$(SRCS_DIR)/parsing/parse.c \
	$(SRCS_DIR)/parsing/parse_meta.c \
	$(SRCS_DIR)/parsing/parse_scene.c \
	$(SRCS_DIR)/parsing/textures.c \
	$(SRCS_DIR)/parsing/utils.c

# Parser tester main (only for parser_test)
PARSER_MAIN = $(SRCS_DIR)/parsing/main.c

# For now cub3D uses the same main, until you add the real game main later.
CUB_MAIN    = $(PARSER_MAIN)

CUB_SRCS    = $(PARSING_SRCS) $(CUB_MAIN)
PARSER_SRCS = $(PARSING_SRCS) $(PARSER_MAIN)

CUB_OBJS    = $(CUB_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
PARSER_OBJS = $(PARSER_SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)
# --- RULES ---- #
all: $(NAME)

$(NAME): $(CUB_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(CUB_OBJS) $(LIBFT_LIB) -o $(NAME)
#$(MLX_LIB) $(LDFLAGS)

$(PARSER): $(PARSER_OBJS) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(PARSER_OBJS) $(LIBFT_LIB) -o $(PARSER)

# Create needed folders before compiling each .o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR)

#$(MLX_LIB):
# 	cmake -S $(MLX_DIR) -B $(MLX_BUILD)
# 	$(MAKE) -C $(MLX_BUILD) -j4

clean:
	$(RM) $(OBJS_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME) $(PARSER)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re $(PARSER)
.SECONDARY: $(CUB_OBJS) $(PARSER_OBJS)
