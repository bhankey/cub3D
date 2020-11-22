# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bhankey <bhankey@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/31 01:59:37 by bhankey           #+#    #+#              #
#    Updated: 2020/10/31 01:59:39 by bhankey          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c \
          ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
          ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c \
          ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c ft_split.c

SRCSB	= ft_lstnew.c ft_lstadd_front.c ft_lstlast.c ft_lstsize.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstmap.c ft_lstiter.c

NAME	= libft.a

OBJS	= $(SRCS:.c=.o)

OBJSB 	= $(SRCSB:.c=.o)

CC		= gcc

MKLIB	= ar rc

CFLAGS	= -Wall -Wextra -Werror -I ./

all:		$(NAME)

$(NAME):	$(OBJS)
					$(MKLIB) $(NAME) $(OBJS)
					ranlib $(NAME)

bonus:		$(OBJS) $(OBJSB)
					$(MKLIB) $(NAME) $(OBJS) $(OBJSB)
					ranlib $(NAME)

clean:
					rm -f $(OBJS) $(OBJSB)

fclean:		clean
						rm -f $(NAME)
re:			fclean all

.PHONY: 	all clean fclean re bonus
		
