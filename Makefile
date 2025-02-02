
.SILENT:
.PHONY: all clean fclean re help fsanitize valgrind


#------------------------------------------------------------------------------#
# 							VARIABLES										   #
#------------------------------------------------------------------------------#


NAME_CLIENT		= exec/client
NAME_SERVER     = exec/server
NAMEB_CLIENT	= exec/client_bonus
NAMEB_SERVER    = exec/server_bonus

SERVER_EXEC		= server
SERVER_EXECB	= server_bonus

OBJ_DIR 		= .objs
EXEC_DIR 		= exec
LIBFT_DIR		= libft
LIBFT_NAME		= libft.a

INCLUDES   		= includes
LIBFT 			= $(LIBFT_DIR)/libft.a

SRC_CLIENT		= cfiles/client.c
SRC_SERVER 		= cfiles/server.c

SRCB_CLIENT		= cfiles/client_bonus.c \
			cfiles/utils_client_bonus.c

SRCB_SERVER 	= cfiles/server_bonus.c \
			cfiles/utils_serv_bonus.c

OBJ_CLIENT 		= $(OBJ_DIR)/client.o
OBJ_SERVER 		= $(OBJ_DIR)/server.o

OBJB_CLIENT 	= $(OBJ_DIR)/client_bonus.o \
			 $(OBJ_DIR)/utils_client_bonus.o

OBJB_SERVER 	= $(OBJ_DIR)/server_bonus.o \
			$(OBJ_DIR)/utils_serv_bonus.o


#------------------------------------------------------------------------------#
# 							COMMANDS									       #
#------------------------------------------------------------------------------#


RM 				= rm -f
RM_DIR			= rm -rf
CC				= cc
AR				= ar -rcs
MAKE			= make

CFLAGS 			= -Wall -Wextra -Werror
CFSIGSEV        = -fsanitize=address

PURPLE          = \033[1;35m
GREEN           = \033[1;32m
RED             = \033[1;31m
YELLOW          = \033[33m
BOLD_UNDERLINE  = \033[1;4m
RESET           = \033[0m



#------------------------------------------------------------------------------#
# 							COMPILATION RULES								   #
#------------------------------------------------------------------------------#


all: $(LIBFT) $(NAME_CLIENT) $(NAME_SERVER)
	echo "$(GREEN)"
	echo "┌───────────────────────────────────────────────────────────┐"
	echo "│      Compilation finished successfully! ᕕ(⌐■_■)ᕗ ♪♬       │"
	echo "└───────────────────────────────────────────────────────────┘"

	echo "                      ☆  *    .      ☆"
	echo "                        ∧＿∧   ∩    * ☆"
	echo "                 *  ☆ ( ・∀・)/ ."
	echo "                  .  ⊂      ノ* ☆"
	echo "                ☆ * (つ   ノ  .☆"
	echo "                      (ノ"

	echo "$(RESET)"


bonus: $(LIBFT) $(NAMEB_CLIENT) $(NAMEB_SERVER)
	echo "$(GREEN)"
	echo "┌───────────────────────────────────────────────────────────┐"
	echo "│      Compilation finished successfully! ᕕ(⌐■_■)ᕗ ♪♬       │"
	echo "└───────────────────────────────────────────────────────────┘"

	echo "                      ☆  *    .      ☆"
	echo "                        ∧＿∧   ∩    * ☆"
	echo "                 *  ☆ ( ・∀・)/ ."
	echo "                  .  ⊂      ノ* ☆"
	echo "                ☆ * (つ   ノ  .☆"
	echo "                      (ノ"

	echo "$(RESET)"


run_terminals: all
	gnome-terminal -- bash -c "\
		cd /home/tarini/Documents/Workspace/TC/Rank_2/Minitalk/exec &&\
		echo -e '\033[1;35mWelcome to \033[1;34m\033[1;4mMinitalk !\n\033[0m\
		\033[1;35mPLEASE ENTER :\n\033[0m \033[1;31m\n./client \033[0m\033[1;31m<PID displayed in the second terminal>\033[0m\033[1;31m <message you want to send>\033[0m';\
		exec bash" &
	sleep 1
	gnome-terminal -- bash -c "\
		cd /home/tarini/Documents/Workspace/TC/Rank_2/Minitalk/exec &&\
		sleep 1 && ./$(SERVER_EXEC);\
		exec bash" &


run_terminals_bonus: bonus
	gnome-terminal -- bash -c "\
		cd /home/tarini/Documents/Workspace/TC/Rank_2/Minitalk/exec &&\
		echo -e '\033[1;35mWelcome to \033[1;34m\033[1;4mMinitalk !\n\033[0m\
		\033[1;35mPLEASE ENTER :\n\033[0m \033[1;31m\n./client_bonus \033[0m\033[1;31m<PID displayed in the second terminal>\033[0m\033[1;31m <message you want to send>\033[0m';\
		exec bash" &
	sleep 1
	gnome-terminal -- bash -c "\
		cd /home/tarini/Documents/Workspace/TC/Rank_2/Minitalk/exec &&\
		sleep 1 && ./$(SERVER_EXECB);\
		exec bash" &


clean:
	echo "$(RED)Deleting object files...$(RESET)"

		$(RM) $(OBJ_CLIENT) $(OBJ_SERVER)
		$(RM) $(OBJB_CLIENT) $(OBJB_SERVER)
		$(MAKE) -sC $(LIBFT_DIR) clean
		$(RM) massif.out*

	echo "$(GREEN)Deleting object files completed successfully!$(RESET)"


fclean: clean
	echo "$(RED)Deleting $(EXEC_DIR) and $(OBJ_DIR)...$(RESET)"

		$(RM_DIR) $(EXEC_DIR) $(OBJ_DIR)
		$(MAKE) -sC $(LIBFT_DIR) fclean

	echo "$(GREEN)Deletion of executable and object directories completed successfully!$(RESET)"
	echo "$(RED)Kill all term...$(RESET)"

	if pgrep -x "gnome-terminal" > /dev/null || pgrep -x "bash" > /dev/null; then \
		echo "$(GREEN)Terminals are open, closing them now...$(RESET)"; \
		pkill gnome-terminal || true; \
		pkill bash || true; \
	else \
		echo "$(GREEN)No terminals are open.$(RESET)"; \
	fi

	echo "$(RED)"
	echo "┌──────────────────────────────────────────────────────────┐"
	echo "│      Deletion finished successfully! ( ◔ ω◔) ノシ        │"
	echo "└──────────────────────────────────────────────────────────┘"
	
	echo "                          ╱|、"
	echo "                        (˚ˎ 。7"
	echo "                         |、˜|"
	echo "                        じしˍ,)ノ"
	
	echo "$(RESET)"


re : fclean all


help:
	echo "$(YELLOW)\n                  =============================="
	echo "                        $(BOLD_UNDERLINE)AVAILABLE TARGETS:$(RESET)"
	echo "$(YELLOW)                  ==============================$(RESET)"
	echo " "
	echo "$(GREEN)───────────────────────────────────────────────────────────────────"
	echo " "
	echo "$(GREEN)  all$(RESET)              $(PURPLE)-$(RESET) Compile the library and generate $(NAME)"
	echo "$(GREEN)  clean$(RESET)            $(PURPLE)-$(RESET) Remove all object files and temporary build files"
	echo "$(GREEN)  fclean$(RESET)           $(PURPLE)-$(RESET) Perform 'clean' and remove the $(NAME) archive"
	echo "$(GREEN)  re$(RESET)               $(PURPLE)-$(RESET) Rebuild everything from scratch"
	echo "$(GREEN)  run_terminals$(RESET)    $(PURPLE)-$(RESET) Open terminals for running server and client"
	echo " "
	echo "$(GREEN)───────────────────────────────────────────────────────────────────"


#------------------------------------------------------------------------------#
# 							DIRECTORY CREATION RULES							   #
#------------------------------------------------------------------------------#


$(OBJ_DIR):
	echo "$(YELLOW)Creating $(OBJ_DIR) directory...$(RESET)"
	
		mkdir -p $(OBJ_DIR)


$(EXEC_DIR):
	echo "$(YELLOW)Creating $(EXEC_DIR) directory...$(RESET)"

		mkdir -p $(EXEC_DIR)


#------------------------------------------------------------------------------#
# 							BUILD RULES										   #
#------------------------------------------------------------------------------#

$(LIBFT):
	echo "$(PURPLE)Compiling $(LIBFT_NAME)...$(RESET)"

		$(MAKE) -sC $(LIBFT_DIR)

	echo "$(GREEN)$(LIBFT_NAME) compiled successfully!$(RESET)"

$(NAME_CLIENT): $(OBJ_CLIENT) $(LIBFT) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAME_CLIENT)...$(RESET)"

		$(CC) $(OBJ_CLIENT) -o $(NAME_CLIENT) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAME_CLIENT) created successfully!$(RESET)"

$(NAME_SERVER): $(OBJB_UTILS) $(OBJ_SERVER) $(LIBFT) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAME_SERVER)...$(RESET)"

		$(CC) $(OBJ_SERVER) -o $(NAME_SERVER) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAME_SERVER) created successfully!$(RESET)"

$(NAMEB_CLIENT): $(OBJB_UTILS) $(OBJB_CLIENT) $(LIBFT) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAMEB_CLIENT)...$(RESET)"

		$(CC) $(OBJB_CLIENT) -o $(NAMEB_CLIENT) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAMEB_CLIENT) created successfully!$(RESET)"

$(NAMEB_SERVER): $(OBJB_SERVER) $(LIBFT) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAMEB_SERVER)...$(RESET)"

		$(CC) $(OBJB_SERVER) -o $(NAMEB_SERVER) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAMEB_SERVER) created successfully!$(RESET)"

$(OBJ_DIR)/%.o: cfiles/%.c | $(OBJ_DIR)
	echo "$(PURPLE)Compiling $< into $@$(RESET)"

		$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

	echo "$(GREEN)Compilation of $< completed!$(RESET)"
