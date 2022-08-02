

NAME		=	ft_irc

# DIR
S_DIR			=	srcs/
S_IRC_DIR		=	IRC/
S_SERVER_DIR	=	server/
BIN_DIR			=	bin/
O_DIR			=	bin/obj/

# COMPILE
CC			=	g++
CFLAGS		=	-Werror -Wextra -Wall -I$(S_DIR)$(S_IRC_DIR) -I$(S_DIR)$(S_SERVER_DIR) -g3
LDFLAGS		=	
DBGFLAGS	=	-g3
FDBGFLAGS	=	-g3 -fsanitize=address

DEPEND_IRC		=	$(addprefix $(S_DIR)$(S_IRC_DIR), \
					Channel.hpp \
					IRCServer.hpp \
					Network.hpp \
					User.hpp)
DEPEND_SERVER	+=	$(addprefix $(S_DIR)$(S_SERVER_DIR), \
					EpollHandler.hpp \
					IEventListener.hpp \
					IRCEventListener.hpp \
					Socket.hpp \
					StreamSocket.hpp \
					DataSocket.hpp \
					ServerSocket.hpp \
					Client.hpp)

DEPENDS			=	$(DEPEND_IRC) \
					$(DEPEND_SERVER)

# SOURCES

IRC_SOURCES		=	Channel.cpp \
					IRCServer.cpp \
					Network.cpp \
					User.cpp

IRC_SRCS		=	$(addprefix $(S_DIR)$(S_IRC_DIR), $(IRC_SOURCES))

SERVER_SOURCES	=	EpollHandler.cpp \
					IRCEventListener.cpp \
					Socket.cpp \
					StreamSocket.cpp \
					DataSocket.cpp \
					ServerSocket.cpp \
					Client.cpp

SERVER_SRCS		=	$(addprefix $(S_DIR)$(S_SERVER_DIR), $(SERVER_SOURCES))

SOURCES			=	my_server.cpp
#SOURCES			+=	$(IRC_SOURCES) \
#					$(SERVER_SOURCES)

SRCS			=	my_server.cpp

OBJECTS			=	$(SOURCES:.cpp=.opp)

IRC_OBJECTS		=	$(IRC_SOURCES:.cpp=.opp)

SERVER_OBJECTS	=	$(SERVER_SOURCES:.cpp=.opp)

OBJS		=	$(addprefix $(O_DIR), $(OBJECTS))
IRC_OBJS	=	$(addprefix $(O_DIR), $(IRC_OBJECTS))
SERVER_OBJS	=	$(addprefix $(O_DIR), $(SERVER_OBJECTS))
#DBG_OBJS	=	$(addprefix $(O_DBG_DIR),$(OBJECTS))
#FDBG_OBJS	=	$(addprefix $(O_FDBG_DIR),$(OBJECTS))

all				:
				@echo "Building $(NAME):"
				@make --no-print-directory $(NAME)

$(NAME)			:	$(OBJS) $(IRC_OBJS) $(SERVER_OBJS)
				@echo "$^"
				@echo "Linking $(NAME)..."
				@$(CC) $(CFLAGS) $^ -o $@
				@echo "$(NAME) built successfully!"


$(OBJS)			:	$(O_DIR)%.opp: %.cpp $(DEPENDS)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(IRC_OBJS)		:	$(O_DIR)%.opp: $(S_DIR)$(S_IRC_DIR)%.cpp $(DEPEND_IRC)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJS)	:	$(O_DIR)%.opp: $(S_DIR)$(S_SERVER_DIR)%.cpp $(DEPEND_SERVER)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

clean			:
				@echo "$(NAME): cleaning objs"
				rm -r -f $(BIN_DIR)

fclean			:	clean
				@echo "$(NAME): cleaning binary"
				rm -r -f $(NAME)

re				:	fclean all

.PHONY			:	all clean fclean re
