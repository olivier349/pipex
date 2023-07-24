

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		:=	pipex
NAME_BONUS	:=	checker
CC			:=	gcc
FLAGS		:=	-Wall -Wextra #-Werror

ifeq ($(DEBUG), 1)
	FLAGS	+=	-g3 -fsanitize=address
endif
################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################



SRCS		:=	pipex.c \
				 

				
				
BONUS_SRCS  = NULL
OBJS		:=	$(SRCS:.c=.o)
OBJS_BONUS	:=	$(SRCS_BONUS:.c=.o)


.c.o:
	@ $(CC) $(FLAGS) -c $< -o $(<:.c=.o)

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:=	\033[0m
RED			:=	\033[1;31m
GREEN		:=	\033[1;32m
YELLOW		:=	\033[1;33m
BLUE		:=	\033[1;34m
CYAN 		:=	\033[1;36m
RM			:=	rm -f

all:			$(NAME)

bonus:			$(NAME_BONUS)

$(NAME):		$(OBJS)
				@ echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
				@ $(CC) $(FLAGS) -o $(NAME) $(OBJS)
				@ echo "$(GREEN)$(NAME) created[0m ✔️"

$(NAME_BONUS):	$(OBJS_BONUS)
				@ echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME_BONUS) $(CLR_RMV)..."
				@ $(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS)
				@ echo "$(GREEN)$(NAME_BONUS) created[0m ✔️"

clean:
				@ $(RM) $(OBJS) $(OBJS_BONUS)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

fclean:			clean
				@ $(RM) $(NAME)
				@ echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"

re:				fclean all

.PHONY:			all clean fclean re