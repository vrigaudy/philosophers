###########
# COMMANDS
CC = cc
LD = cc
RM = rm -rf
MKDIR = mkdir -p

# EXECUTABLE
NAME = philo

# DIRECTORIES
SRC_DIR = ./srcs/
OBJ_DIR = ./objs/
INC_DIR = ./includes/
LFT_DIR = ./libft/
LFT_INC_DIR = $(LFT_DIR)

# LIBRARIES
LFT_A = $(LFT_DIR)libft.a

# SOURCES
SRCS =	main.c \
		parse.c \
		utils.c \
		init.c \
		routine.c \

# OBJETS
OBJS = $(SRCS:.c=.o)
OBJS := $(addprefix $(OBJ_DIR), $(OBJS))
DEPS = $(OBJS:.o=.d)

# FLAGS
CFLAGS = -c 
CFLAGS += -Wall -Wextra -Werror 
CFLAGS += -I $(INC_DIR)
CFLAGS += -MMD -MP
CFLAGS += -pthread
ifeq ($(DEBUG), 1)
	CFLAGS += -fsanitize=address -fsanitize=leak -fsanitize=undefined -g3
endif

LDFLAGS += -lm
LDFLAGS += -Wall -Wextra -Werror
LDFLAGS += -pthread
ifeq ($(DEBUG), 1)
	LDFLAGS += -fsanitize=leak -fsanitize=undefined -fsanitize=thread -g3
endif

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) $(OUTPUT_OPTION)

$(LFT_A):
	$(MAKE) $(@F) -C $(@D)

$(MLX_A):
	$(MAKE) -C $(@D)

-include $(DEPS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $< $(OUTPUT_OPTION)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

