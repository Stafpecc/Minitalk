
.SILENT:
.PHONY: all clean fclean re help fsanitize valgrind bonus run_terminals_bonus run_terminals go


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
LIBFT_DIR		= ./libft
LIBFT_NAME		= libft.a

INCLUDES   		= includes
INC_NAME		= minitalk.h
INC_NAMEB		= minitalk_bonus.h
LIBFT 			= $(LIBFT_DIR)/libft.a
SRC_CLIENT		= cfiles/client.c
SRC_SERVER 		= cfiles/server.c

SRCB_CLIENT		= cfiles/client_bonus.c

SRCB_SERVER 	= cfiles/server_bonus.c

OBJ_CLIENT 		= $(OBJ_DIR)/client.o
OBJ_SERVER 		= $(OBJ_DIR)/server.o

OBJB_CLIENT 	= $(OBJ_DIR)/client_bonus.o

OBJB_SERVER 	= $(OBJ_DIR)/server_bonus.o

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


all: libft $(NAME_CLIENT) $(NAME_SERVER)
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

bonus: libft $(NAMEB_CLIENT) $(NAMEB_SERVER)
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

libft: FORCE
	$(MAKE) -sC $(LIBFT_DIR) all

run_terminals: all
	gnome-terminal --geometry=105x54+0+0 -- bash -c "\
		cd exec &&\
		echo -e '\033[1;34m\033[1;4m				Welcome to Minitalk !\n\033[0m\
		\033[1;35m\nPLEASE ENTER :\n\
		\033[0m \033[1;31m\n./client \033[0m\033[1;31m<PID displayed in the second terminal>\033[0m\033[1;31m <message you want to send>\033[0m';\
		exec bash" &
	sleep 1
	gnome-terminal --geometry=105x54+1920+0 -- bash -c "\
		cd exec &&\
		sleep 1 && ./$(SERVER_EXEC);\
		exec bash" &

run_terminals_bonus: bonus
	gnome-terminal --geometry=105x54+0+0 -- bash -c "\
		cd exec &&\
		echo -e '\033[1;35mWelcome to \033[1;34m\033[1;4mMinitalk !\n\033[0m\
		\033[1;35mPLEASE ENTER :\n\033[0m \033[1;31m\n./client_bonus \033[0m\033[1;31m<PID displayed in the second terminal>\033[0m\033[1;31m <message you want to send>\033[0m';\
		exec bash" &
	sleep 1
	gnome-terminal --geometry=105x54+0+0 -- bash -c "\
		cd exec &&\
		sleep 1 && ./$(SERVER_EXECB);\
		exec bash" &

valgrind: $(EXEC_G3)
		$(MAKE) $(EXEC_G3)
		if [ -z "$(FLAGS)" ]; then \
			echo "$(PURPLE)Please define FLAGS (e.g., make valgrind FLAGS=1).$(RESET)"; \
		elif [ "$(FLAGS)" -eq 1 ]; then \
			valgrind --leak-check=full ./$(EXEC)/$(NAME_SERVER); \
		elif [ "$(FLAGS)" -eq 2 ]; then \
			valgrind --track-origins=yes ./$(EXEC)/$(NAME_SERVER); \
		elif [ "$(FLAGS)" -eq 3 ]; then \
			valgrind --tool=massif ./$(EXEC)/$(NAME_SERVER); \
		else \
			echo "$(RED)Invalid FLAGS value. Use 1, 2, or 3.$(RESET)"; \
		fi;

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


go: fclean help run_terminals

re: fclean all

test: all
	chmod 0777 ./tests/tests.sh ./tests/valgrind_tests.sh
	./tests/valgrind_tests.sh
	./tests/tests.sh

test_bible: all
	chmod 0777 ./tests/bible.sh
	./tests/bible.sh

help:
	echo "$(YELLOW)\n                  =============================="
	echo "                        $(BOLD_UNDERLINE)AVAILABLE TARGETS:$(RESET)"
	echo "$(YELLOW)                  ==============================$(RESET)"
	echo " "
	echo "$(GREEN)───────────────────────────────────────────────────────────────────"
	echo " "
	echo "$(GREEN)  all$(RESET)                   "
	echo "    $(PURPLE)-$(RESET) Generate $(NAME_CLIENT) and $(NAME_SERVER)"
	echo " "
	echo "$(GREEN)  bonus$(RESET)                 "
	echo "    $(PURPLE)-$(RESET) Generate $(NAMEB_CLIENT) and $(NAMEB_SERVER)"
	echo " "
	echo "$(GREEN)  clean$(RESET)                 "
	echo "    $(PURPLE)-$(RESET) Remove all object files and temporary build files"
	echo " "
	echo "$(GREEN)  fclean$(RESET)                "
	echo "    $(PURPLE)-$(RESET) Perform 'clean', close all term and remove the $(NAME) archive"
	echo " "
	echo "$(GREEN)  re$(RESET)                    "
	echo "    $(PURPLE)-$(RESET) Rebuild everything from scratch"
	echo " "
	echo "$(GREEN)  run_terminals$(RESET)         "
	echo "    $(PURPLE)-$(RESET) Open terminals for running server and client"
	echo " "
	echo "$(GREEN)  run_terminals_bonus$(RESET)   "
	echo "    $(PURPLE)-$(RESET) Open terminals for running bonus server and bonus client"
	echo " "
	echo "$(GREEN)  go$(RESET)   "
	echo "    $(PURPLE)-$(RESET) use fclean, help and run_terminals rule"
	echo " "
	echo "$(GREEN)  russian_roulette$(RESET)   "
	echo "    $(PURPLE)-$(RESET) you shouldn't try.. really don't try"
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
		$(MAKE) -sC $(LIBFT_DIR)

$(NAME_CLIENT): $(OBJ_CLIENT) $(INCLUDES)/$(INC_NAME) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAME_CLIENT)...$(RESET)"

		$(CC) $(OBJ_CLIENT) -o $(NAME_CLIENT) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAME_CLIENT) created successfully!$(RESET)"

$(NAME_SERVER): $(OBJ_SERVER) $(INCLUDES)/$(INC_NAME) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAME_SERVER)...$(RESET)"

		$(CC) $(OBJ_SERVER) -o $(NAME_SERVER) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAME_SERVER) created successfully!$(RESET)"


$(EXEC_G3): $(OBJB_CLIENT) $(OBJB_SERVER) $(INCLUDES)/$(INC_NAMEB) | $(EXEC_DIR)
	$(CC) $(OBJB_CLIENT) -g3 -o $(NAMEB_CLIENT) -L$(LIBFT_DIR) -lft
	$(CC) $(OBJB_SERVER) -g3 -o $(NAMEB_SERVER) -L$(LIBFT_DIR) -lft

#------------------------------------------------------------------------------#
# 							BUILD BONUS RULES								   #
#------------------------------------------------------------------------------#

$(NAMEB_CLIENT): $(OBJB_CLIENT) $(INCLUDES)/$(INC_NAMEB) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAMEB_CLIENT)...$(RESET)"

		$(CC) $(OBJB_CLIENT) -o $(NAMEB_CLIENT) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAMEB_CLIENT) created successfully!$(RESET)"

$(NAMEB_SERVER): $(OBJB_SERVER) $(INCLUDES)/$(INC_NAMEB) | $(EXEC_DIR)
	echo "$(PURPLE)Linking $(NAMEB_SERVER)...$(RESET)"

		$(CC) $(OBJB_SERVER) -o $(NAMEB_SERVER) -L$(LIBFT_DIR) -lft

	echo "$(GREEN)$(NAMEB_SERVER) created successfully!$(RESET)"

#------------------------------------------------------------------------------#
# 							BUILD DIR RULES									   #
#------------------------------------------------------------------------------#

$(OBJ_DIR)/%.o: cfiles/%.c | $(OBJ_DIR)
	echo "$(PURPLE)Compiling $< into $@$(RESET)"

		$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

	echo "$(GREEN)Compilation of $< completed!$(RESET)"


FORCE: