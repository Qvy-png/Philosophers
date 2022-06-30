# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdel-agu <rdel-agu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/25 09:36:05 by rdel-agu          #+#    #+#              #
#    Updated: 2022/05/24 17:54:09 by rdel-agu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
RM = rm
OBJ = $(SRC:.c=.o)
CFGLAGS = -Wall -Wextra -Werror
SRC =	ft_atoi.c\
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
		ft_free_array.c\
		
BONUS =	ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

BONUS_OBJ = $(BONUS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -o $@ -c $<

$(NAME): $(OBJ)
	ar rcs $@ $(OBJ)

clean:
	$(RM) -f $(OBJ) $(BONUS_OBJ)

fclean: clean
	$(RM) -f $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRC)

.PHONY: clean fclean

bonus:	$(OBJ) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJ) $(BONUS_OBJ)
