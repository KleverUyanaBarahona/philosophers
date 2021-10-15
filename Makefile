NAME	= philo

SRCS	= ./philosophers.c ./utils.c ./status_philo.c ./fork_mutex.c ./create_philo.c ./loop_philo.c ./threads_process.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Werror -Wextra
CFLAGS	+= -g -fsanitize=address

LIBS	= -pthread

${NAME}:	${OBJS}
			@echo "\033[36mCompiled..."
			@${CC} ${CFLAGS} ${LIBS} ${OBJS} -o ${NAME}
			@sleep 3
			@clear
			@echo "\033[1;36m [N_FHILOS] [Time dead] [Time eating] [Time sleep] [N eats]...\033[0m\n"

all:	${NAME}

run: 
	@./philo 1 800 200 200
	@echo "The philosopher should not eat and should die!"

run2:
	@./philo 5 800 200 200
	@echo "No one should die!"

run3:
	@./philo 5 800 200 200 7 
	@echo "o one should die and the simulation should stop when all the philosopher has eaten at least 7 times each"

run4:
	@./philo 4 410 200 200 
	@echo "No one should die!"

run5:
	@./philo 4 310 200 100 
	@echo "a philosopher should die"

run6:
	@./philo 2 210 200 200 
	@echo "a philosopher should die"

run7:
	@./philo 2 403 200 200 
	@echo "a philosopher should die"


clean:
		@${RM} ${OBJS}
		@echo "\033[1;31mDeleted-files" ${OBJS}

fclean:		clean
			@${RM} ${NAME}
			@echo "\033[1;31mDeleted-program"  ${NAME}

re: fclean all

.PHONY: all clean re 
