# .SILENT:
# .PHONY: all clean fclean fsanitize re

# NAME=libft.a

# #------------------------------------------------------------------------------#
# # 							VARIABLES										   #
# #------------------------------------------------------------------------------#

# SRCS_DIR= cfiles/

# SRCS = \
# 	isdigit                     \
# 	isalpha                     \
# 	isalnum                     \
# 	isascii                     \
# 	isprint                     \
# 	strlen                      \
# 	memset                      \
# 	bzero                       \
# 	memcpy                      \
# 	memmove                     \
# 	strlcpy                     \
# 	strlcat                     \
# 	toupper                     \
# 	tolower                     \
# 	strchr                      \
# 	strrchr                     \
# 	strncmp                     \
# 	memchr                      \
# 	memcmp                      \
# 	strnstr                     \
# 	atoi                        \
# 	strdup                      \
# 	calloc                      \
# 	split                       \
# 	substr                      \
# 	strjoin                     \
# 	strcmp				        \
# 	strtrim                     \
# 	itoa                        \
# 	putchar_fd                  \
# 	putstr_fd                   \
# 	putendl_fd                  \
# 	putnbr_fd                   \
# 	strmapi                     \
# 	striteri                    \
# 	printf		                \
# 	putchar			            \
# 	putstr			            \
# 	putnbrbase		            \
# 	handle                      \
# 	lstnew_bonus                \
# 	lstadd_front_bonus          \
# 	lstsize_bonus               \
# 	lstlast_bonus               \
# 	lstadd_back_bonus           \
# 	lstdelone_bonus             \
# 	lstclear_bonus              \
# 	lstiter_bonus               \
# 	lstmap_bonus

# OBJS_DIR      = .objs/

# SRC			  = $(patsubst %, $(SRCS_DIR)ft_%.c, $(CFILES))

# OBJS		  = $(patsubst $(SRCS_DIR)%.c, .objs/%.o, $(SRC))

# OBJS_DIR= ./OBJS

# INCS= includes

# DEPS= $(OBJS:.o=.d)


# #------------------------------------------------------------------------------#
# # 							COMMANDS									       #
# #------------------------------------------------------------------------------#

# CC= cc

# CFLAGS= -Werror -Wextra -Wall -MMD -MP

# RM= rm -rf

# CFSIGSEV = -fsanitize=address

# DIR_DUP= mkdir -p $(@D)

# AR = ar rcs

# MAKEFLAGS += --no-print-directory

# #------------------------------------------------------------------------------#
# # 							RULES											   #
# #------------------------------------------------------------------------------#

# all:$(NAME)

# -include $(DEPS)

# $(NAME): $(OBJS) $(INCS)
# 	$(AR) $(NAME) $(OBJS)

# $(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
# 	@$(DIR_DUP)
# 	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@

# fsanitize:
# 	$(MAKE) CFLAGS="$(CFLAGS) $(CFSIGSEV)"

# clean:
# 	$(RM) $(OBJS_DIR)

# fclean:clean
# 	$(RM) $(NAME)
# 	rm -f a.out

# re:fclean all

# .PHONY: all clean fclean re

NAME=libft.a

#------------------------------------------------------------------------------#
# 							VARIABLES										   #
#------------------------------------------------------------------------------#

SRCS_DIR= ./cfiles

SRCS = \
	ft_isdigit.c                      \
	ft_isalpha.c                      \
	ft_isalnum.c                      \
	ft_isascii.c                      \
	ft_isprint.c                      \
	ft_strlen.c                       \
	ft_memset.c                       \
	ft_bzero.c                        \
	ft_memcpy.c                       \
	ft_memmove.c                      \
	ft_strlcpy.c                      \
	ft_strlcat.c                      \
	ft_toupper.c                      \
	ft_tolower.c                      \
	ft_strchr.c                       \
	ft_strrchr.c                      \
	ft_strncmp.c                      \
	ft_memchr.c                       \
	ft_memcmp.c                       \
	ft_strnstr.c                      \
	ft_atoi.c                         \
	ft_strdup.c                       \
	ft_calloc.c                       \
	ft_split.c                        \
	ft_substr.c                       \
	ft_strjoin.c                      \
	ft_strtrim.c                      \
	ft_itoa.c                         \
	ft_putchar_fd.c                   \
	ft_putstr_fd.c                    \
	ft_putendl_fd.c                   \
	ft_putnbr_fd.c                    \
	ft_strmapi.c                      \
	ft_striteri.c                     \
	ft_printf.c 		              \
	ft_putchar.c 			          \
	ft_putstr.c 			          \
	ft_putnbrbase.c 		          \
	ft_handle.c                       \
	ft_lstnew_bonus.c                 \
	ft_lstadd_front_bonus.c           \
	ft_lstsize_bonus.c                \
	ft_lstlast_bonus.c                \
	ft_lstadd_back_bonus.c            \
	ft_lstdelone_bonus.c              \
	ft_lstclear_bonus.c               \
	ft_lstiter_bonus.c                \
	ft_lstmap_bonus.c 				  \
	ft_atoi_only_num.c

SRCS:= $(SRCS:%=$(SRCS_DIR)/%)

OBJS_DIR= ./OBJS

OBJS=$(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

INCS= includes

DEPS= $(OBJS:.o=.d)


#------------------------------------------------------------------------------#
# 							COMMANDS									       #
#------------------------------------------------------------------------------#

CC= cc

CFLAGS= -Werror -Wextra -Wall

RM= rm -rf

CFSIGSEV = -fsanitize=address

DIR_DUP= mkdir -p $(@D)

AR = ar rcs

MAKEFLAGS += --no-print-directory

#------------------------------------------------------------------------------#
# 							RULES											   #
#------------------------------------------------------------------------------#

all:$(NAME)


$(NAME): $(OBJS) $(INCS)
	$(AR) $(NAME) $(OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@$(DIR_DUP)
	$(CC) $(CFLAGS) -I$(INCS) -c $< -o $@

fsanitize:
	$(MAKE) CFLAGS="$(CFLAGS) $(CFSIGSEV)"

clean:
	$(RM) $(OBJS_DIR)

fclean:clean
	$(RM) $(NAME)
	rm -f a.out

re:fclean all

.PHONY: all clean fclean re