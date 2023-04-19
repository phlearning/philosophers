NAME 			= philo

# Colors
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
END				=	\033[0m

# SRCS

SRC_DIR			= src

SOURCES			= 	main.c \
					atoi.c \
					eating.c \
					fork.c \
					free.c \
					parsing.c \
					time.c \
					utils.c \


SRC = $(addprefix $(SRC_DIR)/,$(SOURCES))

# OBJS

OBJS_DIR 		= objs
TMP				= $(OBJS_DIR)
OBJS 			= $(addprefix ./$(OBJS_DIR)/,$(SOURCES:.c=.o))
OBJS_DIRFS 		= objsfs
TMPFS			= $(OBJS_DIRFS)
OBJSFS 			= $(addprefix ./$(OBJS_DIRFS)/,$(SOURCES:.c=.o))
OBJS_DIRFT 		= objsft
TMPFT			= $(OBJS_DIRFT)
OBJSFT 			= $(addprefix ./$(OBJS_DIRFT)/,$(SOURCES:.c=.o))

# Compiling

CC				= gcc

CFLAGS 			= -Wall -Werror -Wextra

INCLUDE 		= -I includes

DEBUG			= debug

all:	$(NAME)

$(TMP):
	@mkdir -p $(OBJS_DIR)

$(TMPFS):
	@mkdir -p $(OBJS_DIRFS)

$(TMPFT):
	@mkdir -p $(OBJS_DIRFT)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -pthread
	@echo "Compiling $@..."

$(NAME): $(TMP) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread
	@echo "$(GREEN) $(NAME) Compiled $(END)"

$(OBJS_DIRFS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIRFS)
	@$(CC) -g -fsanitize=address $(CFLAGS) $(INCLUDE) -c $< -o $@ -pthread
	@echo "Compiling $@..."

$(OBJS_DIRFT)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIRFT)
	@$(CC) -g -fsanitize=thread $(CFLAGS) $(INCLUDE) -c $< -o $@ -pthread
	@echo "Compiling $@..."

fsanitize: $(TMPFS) $(OBJSFS)
	@$(CC) $(CFLAGS) -g -fsanitize=address $(OBJSFS) $(INCLUDE) -o $(DEBUG) -pthread
	@echo "$(BLUE) $(DEBUG) Compiled $(END)"

fthread: $(TMPFT) $(OBJSFT)
	@$(CC) $(CFLAGS) -g -fsanitize=thread $(OBJSFT) $(INCLUDE) -o $(DEBUG) -pthread
	@echo "$(BLUE) $(DEBUG) Compiled $(END)"

checkfunction:
	$(shell nm -A ./objs/*) > checkfunction.txt

check2:
	$(shell nm ./$(NAME) | grep U) > checkfunction.txt

git:
	git add .
	git commit -am "update"
	git push

clean:
	@rm -rf $(OBJS_DIR)
	@rm -rf $(OBJS_DIRFS)
	@rm -rf $(OBJS_DIRFT)
	@rm -rf checkfunction.txt
	@echo "$(BLUE)$(NAME) Cleaning Done$(END)"

fclean: clean
	@rm -rf $(NAME)
	@rm -f debug
	@echo "$(BLUE)$(NAME) Fcleaning Done$(END)"

re: fclean all

.PHONY: all fclean clean re temp