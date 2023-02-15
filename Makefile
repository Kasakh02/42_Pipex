# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hcorrea- <hcorrea-@student.42lisboa.pt>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 11:42:38 by hcorrea-          #+#    #+#              #
#    Updated: 2023/02/15 16:10:14 by hcorrea-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN			=	\033[0;32m
RED				=	\033[0;31m
YELLOW			=	\033[0;33m
END				=	\033[0m

PIPEX 			=	pipex

PROJECTDIR		=	src
INC 			=	inc
OBJ_DIR			=	obj
HEADER			=	$(INC)

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror

SRC				=	mandatory/main.c		\
					mandatory/utils.c		\
					mandatory/cmd.c			\
					mandatory/free.c		\
					mandatory/init.c		\
					mandatory/ft_split.c	\

SRCB			=	bonus/main.c	\
					bonus/utils.c	\
					bonus/cmd.c		\
					bonus/free.c	\
					bonus/init.c	\

OBJ				:=	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJB			:=	$(addprefix $(OBJ_DIR)/, $(SRCB:.c=.o))

RM				=	rm -rf
MKDIR			=	mkdir -p
MAKE			=	make -C
ERRIGNORE		=	2>/dev/null

all:				$(PIPEX)
					@echo "$(GREEN)Pipex succesfully compiled!$(END)"
					@sleep 0.5
					@clear

$(PIPEX):			$(OBJ)
					@clear
					@echo "$(YELLOW)Compiling Pipex...$(END)"
					@$(CC) $(CFLAGS) -I $(HEADER) $(OBJ) -o $@

$(OBJ_DIR)/%.o:		$(PROJECTDIR)/%.c $(HEADER)
					@$(MKDIR) $(dir $@)
					@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
										
%.o:				%.c
					@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
					
clean:
					@$(RM) $(OBJ_DIR) $(ERRIGNORE)
					@clear
					@echo "$(RED)All objects deleted!$(END)"
					
fclean:				clean
					@$(RM) $(PIPEX) bonus
					@echo "$(RED)All executables deleted!$(END)"
					@sleep 0.5
					@clear

re:					fclean all

norminette:			
					norminette
					@clear
					@echo "$(GREEN)Norminette check!$(END)"

bonus:				$(PIPEX) $(OBJB)
					@clear
					@echo "$(YELLOW)Compiling Pipex Bonus...$(END)"
					@$(CC) $(CFLAGS) -I $(HEADER) $(OBJB) -o $@
					@echo "$(GREEN)Pipex Bonus succesfully compiled!$(END)"
					@sleep 0.5
					@clear

.PHONY: clean fclean re bonus norminette