# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: qvy <qvy@student.42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/23 19:07:37 by rdel-agu          #+#    #+#              #
#    Updated: 2022/07/05 01:24:52 by qvy              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philosophers

CC = cc

CFLAGS = -Wall -Werror -Wextra -p

RM = rm

OBJ = $(SRC:.c=.o)

LFTSRC = libft

INCL = includes/philosophers.h

SRC =	src/main.c\
		src/utils.c\

LFT = 	ft_atoi.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_strlen.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strlcat.c\
		ft_tolower.c\
		ft_toupper.c\
		ft_strlcpy.c\
		ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_calloc.c\
		ft_split.c\
		ft_itoa.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_putstr_fd.c\
		ft_putchar_fd.c\
		ft_putnbr_fd.c\
		ft_putendl_fd.c\
		ft_strmapi.c\
		ft_striteri.c\

LFTB =	ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\		

all: $(NAME)

bonus: $(NAME)_bonus

%.o: %.c 
	@$(CC) $(CFLAGS)  -I/usr/include -I libft/ -c $< -o $@
		
$(NAME): libft/libft.a $(OBJ)
	@echo " \033[0;31mCompiling $(NAME)...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) libft/libft.a
	@echo " \033[0;32mSuccess\033[0m"

libft/libft.a :
	@echo " \033[0;31mCompiling libft...\033[0m"
	@make -C libft/ -s
	@echo " \033[0;32mSuccess!\033[0m"

clean:
	@$(RM) -f $(OBJ)
	@make clean -C libft -s 
	@echo " \033[0;32mCleaning done!\033[0m"
	
fclean: clean
	@$(RM) -f $(NAME)
	@make fclean -C libft -s
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
