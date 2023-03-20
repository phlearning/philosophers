NAME 			= philosophers

# Colors
GREEN			=	\033[0;32m
RED				=	\033[0;31m
BLUE			=	\033[0;34m
END				=	\033[0m

# SRCS

SRC_DIR			= src

SOURCES			= 	main.c \
					parsing.c \
					utils.c

# SRCB_DIR		=	src_bonus

# SOURCESB		=	main_bonus.c \
# 					

SRC = $(addprefix $(SRC_DIR)/,$(SOURCES))
# SRCB = $(addprefix $(SRCB_DIR)/,$(SOURCESB))

# OBJS

OBJS_DIR 		= objs
TMP				= $(OBJS_DIR)
OBJS 			= $(addprefix ./$(OBJS_DIR)/,$(SOURCES:.c=.o))
OBJS_DIRFS 		= objsfs
TMPFS			= $(OBJS_DIRFS)
OBJSFS 			= $(addprefix ./$(OBJS_DIRFS)/,$(SOURCES:.c=.o))

# OBJSB_DIR		= objs_bonus
# TMPB			= $(OBJSB_DIR)
# OBJSB			= $(addprefix ./$(OBJSB_DIR)/,$(SOURCESB:.c=.o))

# Compiling

BONUSF			= .bonus

CC				= gcc

CFLAGS 			= -Wall -Werror -Wextra

INCLUDE 		= -I includes
# INCLUDEB		= -I includes_bonus

DEBUG			= debug

all:	$(NAME)

$(TMP):
	@mkdir -p $(OBJS_DIR)

$(TMPFS):
	@mkdir -p $(OBJS_DIRFS)

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -pthread
	@echo "Compiling $@..."

$(NAME): $(TMP) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -pthread
	@echo "$(GREEN) $(NAME) Compiled $(END)"

# $(TMPB):
# 	@mkdir -p $(OBJSB_DIR)

# $(OBJSB_DIR)/%.o: $(SRCB_DIR)/%.c
# 	@mkdir -p $(OBJSB_DIR)
# 	@$(CC) $(CFLAGS) $(INCLUDEB) -c $< -o $@
# 	@echo "Compiling $@..."

# bonus: $(BONUSF)

# $(BONUSF): $(TMPB) $(OBJSB)
# 	@echo "$(GREEN) Libft compiled $(END)"
# 	@$(CC) $(CFLAGS) $(OBJSB) -o $(NAME)
# 	@echo "bonuscache" > $(BONUSF)
# 	@echo "$(GREEN) $(NAME) Compiled $(END)"

$(OBJS_DIRFS)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJS_DIRFS)
	@$(CC) -g -fsanitize=thread $(CFLAGS) $(INCLUDE) -c $< -o $@ -pthread
	@echo "Compiling $@..."

fsanitize: $(TMPFS) $(OBJSFS)
	@$(CC) $(CFLAGS) -g -fsanitize=thread $(OBJSFS) $(INCLUDE) -o $(DEBUG) -pthread
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
	@rm -rf checkfunction.txt
	@echo "$(BLUE)$(NAME) Cleaning Done$(END)"
# @rm -rf $(OBJSB_DIR)
# @rm -f $(BONUSF)

fclean: clean
	@rm -rf $(NAME)
	@rm -f debug
	@echo "$(BLUE)$(NAME) Fcleaning Done$(END)"

re: fclean all

.PHONY: all fclean clean re temp