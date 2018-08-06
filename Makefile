# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baudiber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/29 00:57:22 by baudiber          #+#    #+#              #
#    Updated: 2018/08/06 19:56:03 by baudiber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

SRC_DIR		=	./srcs
INC_DIR		=	./includes
OBJ_DIR		=	./obj
LIB_DIR		=	./libft
MLX_DIR		=	./minilibx/minilibx_mac

SRC			=	main.c \
				init.c \
				fractol.c \
				splash.c \
				keys.c \
				draw.c \
				mandelbrot.c \
				julia.c \
				burningship.c \
				tricorn.c \
				multibrot.c \
				multibrot3.c \
				pixel.c

CC 			=	gcc
FLAGS		=	-Wall -Werror -Wextra -pthread
INCLUDES	=	-I $(INC_DIR)
HEADER_H	=	$(INC_DIR)/$(NAME).h
OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
MFLAGS		=	-lm -lmlx -framework OpenGL -framework Appkit
LIBS 		=	-L $(LIB_DIR) -lft -L $(MLX_DIR) $(MFLAGS)

all: $(NAME)

$(NAME): obj_mkdir lib $(HEADER_H) $(OBJ) 
	@$(CC)  $(OBJ) -o $(NAME) $(LIBS)
	@echo "$(NAME) binary \033[32mcreated\033[0m."

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c $(HEADER_H)
	@echo "\033[33mCOMPILING\033[0m" $< 
	@$(CC) $(FLAGS) -o $@ -c $< -I $(INC_DIR)

obj_mkdir:
	@mkdir -p $(OBJ_DIR)

lib:
	@make -C $(LIB_DIR)
	@make -C $(MLX_DIR)

clean:
	@rm -f $(OBJ)
	@rm -rf $(OBJ_DIR)
	@make -C $(LIB_DIR) clean 
	@make -C $(MLX_DIR) clean 

fclean: clean
	@make -C $(LIB_DIR) fclean 
	@make -C $(MLX_DIR) clean
	@rm -f $(NAME)

fast:
	@$(MAKE)	-j

run:
	@$(MAKE) -j
	@./fractol

re: 
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re build cbuild
