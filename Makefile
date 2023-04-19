NAME = philosopher
TEST = testdir

all: philo

philo:
	make -sC $(NAME)
	@cp ./$(NAME)/philo .
	@mv philo a.out

test:
	make -sC $(TEST)
	@cp ./$(TEST)/test .
	@mv test a.out

clean:
	@make -C $(NAME) clean
	@make -C $(TEST) clean

fclean:
	@make -C $(NAME) fclean
	@make -C $(TEST) fclean
	@rm -f a.out