# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 19:07:37 by rdel-agu          #+#    #+#              #
#    Updated: 2022/07/11 11:19:51 by rdel-agu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc

CFLAGS = -Wall -Werror -Wextra -pthread -g #-fsanitize=thread

RM = rm

OBJ = $(SRC:.c=.o)

INCL = includes/philosophers.h

SRC =	src/main.c\
		src/utils.c\
		src/init.c\
		
all: $(NAME)

bonus: $(NAME)_bonus

%.o: %.c 
	@$(CC) $(CFLAGS)  -I/usr/include -I libft/ -c $< -o $@
		
$(NAME):  $(OBJ)
	@echo " \033[0;31mCompiling $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo " \033[0;32mSuccess\033[0m"
	
clean:
	@$(RM) -f $(OBJ) 
	@echo " \033[0;32mCleaning done!\033[0m"
	
fclean: clean
	@$(RM) -f $(NAME)
	@$(RM) -f $(NAME)_bonus

re: fclean all

norme:
	@echo " \033[0;31mChecking sources...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(SRC)
	@echo " \033[0;31mChecking libft...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(LFTSRC)
	@echo " \033[0;31mChecking includes...\033[0m"
	@norminette -R CheckForbiddenSourceHeader $(INCL)
	@echo " \033[0;32mDone!\033[0m"

sanit:
	@echo " \033[0;31mCompiling libft...\033[0m"
	@make -C libft/ -s
	@echo " \033[0;32mSuccess!\033[0m"
	@echo " \033[0;31mCompiling with fsanitize...\033[0m"
	$(CC) $(CFLAGS) $(OBJ) -fsanitize=address -g3 -L/usr/lib -o $(NAME) libft/libft.a
	@echo " \033[0;32mSuccess!\033[0m"
	
.PHONY: clean fclean
