NAME		=	philo

HEADER		=	./include/

CC			=	clang

CFLAGS		=	-Werror -Wall -Wextra

INC = -I $(HEADER) -pthread

ifeq ($(d), 0)
CFLAGS += -g
CFLAGS += -fsanitize=address
endif

SRCS		=	srcs/philo.c srcs/philo_init.c srcs/philo_threads.c \
				srcs/philo_occup.c srcs/philo_utils_01.c srcs/philo_utils_02.c \
		
OBJS		=	$(SRCS:.c=.o)

all			:	$(NAME)

$(NAME)		:	$(OBJS) $(HEADER)
				@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INC)
				@echo "\033[32;1m [CREATED] $(NAME)\033[0m"

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean		:
				@rm -rf $(OBJS)
				@echo "\033[33;1m [DELETED] All .o files\033[0m"

fclean		:	clean
				@rm -rf $(NAME)
				@echo "\033[33;1m [DELETED] $(NAME)\033[0m"

re			:	fclean all
