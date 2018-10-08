# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: baudiber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/29 00:57:22 by baudiber          #+#    #+#              #
#    Updated: 2018/10/08 18:16:19 by baudiber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fractol

SRC_DIR		=	./srcs
INC_DIR		=	./includes
OBJ_DIR		=	./obj
LIB_DIR		=	./libft
GLEW_DIR	=	./glew
MLX_DIR		=	./minilibx_opengl

SRC			=	main.c \
				init.c \
				fractol.c \
				keys.c \
				draw.c \
				mandelbrot.c \
				julia.c \
				burningship.c \
				tricorn.c \
				multibrot.c \
				multibrot3.c \
				threads.c \
				bresenham.c \
				tree.c \
				pixel.c \
				res.c \
				gl_main.c

CC 			=	gcc
FLAGS		=	-Wall -Werror -Wextra -pthread
INCLUDES	=	-I $(INC_DIR) -I $(MLX_DIR) -I $(GLEW_DIR)/include
HEADER_H	=	$(INC_DIR)/$(NAME).h
OBJ 		=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
MFLAGS		=	-lm -lmlx -framework OpenGL -framework Appkit
LIBS 		=	-L $(LIB_DIR) -lft -L $(MLX_DIR) $(MFLAGS)
GL_FLAGS	=	-L $(GLEW_DIR)/lib -lGLEW 

all: $(NAME)

$(NAME): obj_mkdir lib $(HEADER_H) $(OBJ) 
	@$(CC)  $(OBJ) -o $(NAME) $(LIBS) $(GL_FLAGS)
	@install_name_tool -change /usr/local/lib/libGLEW.2.1.0.dylib /Users/baudiber/42/fractol/glew/lib/libGLEW.2.1.0.dylib fractol
	@echo "$(NAME) binary \033[32mcreated\033[0m."

$(OBJ_DIR)/%.o:		$(SRC_DIR)/%.c $(HEADER_H)
	@echo "\033[33mCOMPILING\033[0m" $< 
	@$(CC) $(FLAGS) -o $@ -c $< -I $(INC_DIR)

obj_mkdir:
	@mkdir -p $(OBJ_DIR)

lib:
	@make -C $(LIB_DIR)
	@make -C $(MLX_DIR)
	#@brew install glew

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

gpu:
	@$(MAKE)	-j
	@./fractol mandelbrot GPU

re: 
	@$(MAKE) fclean
	@$(MAKE)

.PHONY: all clean fclean re build cbuild
