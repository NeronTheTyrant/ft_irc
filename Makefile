

NAME		=	ft_irc

# DIR
S_DIR			=	srcs/
S_IRC_DIR		=	IRC/
S_CMD_DIR		=	IRC/command/
S_SERVER_DIR	=	server/
S_UTILS_DIR		=	utils/
S_MESSAGE_DIR	=	message/
BIN_DIR			=	bin/
O_DIR			=	bin/obj/

# COMPILE
CC			=	c++
CFLAGS		=	-Werror -Wextra -Wall -I$(S_DIR)$(S_IRC_DIR) -I$(S_DIR)$(S_SERVER_DIR) -I$(S_DIR)$(S_UTILS_DIR) -I$(S_DIR)$(S_MESSAGE_DIR) -g3 --std=c++98
LDFLAGS		=
DBGFLAGS	=	-g3
FDBGFLAGS	=	-g3 -fsanitize=address

DEPEND_IRC		=	$(addprefix $(S_DIR)$(S_IRC_DIR), \
					Channel.hpp \
					IRCServer.hpp \
					Network.hpp \
					User.hpp)

DEPEND_SERVER	=	$(addprefix $(S_DIR)$(S_SERVER_DIR), \
					EpollHandler.hpp \
					IEventListener.hpp \
					IRCEventListener.hpp \
					Socket.hpp \
					StreamSocket.hpp \
					DataSocket.hpp \
					ServerSocket.hpp \
					Command.hpp \
					Parser.hpp \
					Client.hpp)

DEPEND_UTILS	=	$(addprefix $(S_DIR)$(S_UTILS_DIR), \
					Flag.hpp \
					charset.hpp \
					enable_if.hpp \
					u_nullptr.hpp \
					utils.hpp)

DEPEND_MESSAGE	=	$(addprefix $(S_DIR)$(S_MESSAGE_DIR), \
					commandResponses.hpp \
					Motd.hpp \
					messageBuilder.hpp)

DEPEND_CMD		=	$(DEPEND_IRC) \
					$(DEPEND_MESSAGE)

DEPENDS			=	$(DEPEND_IRC) \
					$(DEPEND_SERVER) \
					$(DEPEND_UTILS) \
					$(DEPEND_MESSAGE)

# SOURCES

IRC_SOURCES		=	Channel.cpp \
					IRCServer.cpp \
					Network.cpp \
					User.cpp
IRC_SRCS		=	$(addprefix $(S_DIR)$(S_IRC_DIR), $(IRC_SOURCES))

CMD_SOURCES		=	cap.cpp \
					nick.cpp \
					pass.cpp \
					user.cpp \
					quit.cpp \
					mode.cpp \
					away.cpp \
					part.cpp \
					join.cpp \
					privmsg.cpp \
					notice.cpp \
					topic.cpp \
					names.cpp \
					list.cpp \
					kill.cpp \
					oper.cpp \
					invite.cpp \
					die.cpp \
					kick.cpp \
					motd.cpp \
					restart.cpp \
					ping.cpp \
					wallops.cpp

CMD_SRCS		=	$(addprefix $(S_DIR)$(S_CMD_DIR), $(CMD_SOURCES))

SERVER_SOURCES	=	EpollHandler.cpp \
					IRCEventListener.cpp \
					Socket.cpp \
					StreamSocket.cpp \
					DataSocket.cpp \
					ServerSocket.cpp \
					Command.cpp \
					Parser.cpp \
					Client.cpp
SERVER_SRCS		=	$(addprefix $(S_DIR)$(S_SERVER_DIR), $(SERVER_SOURCES))

UTILS_SOURCES	=	Flag.cpp \
					ft_isdigit.cpp \
					ft_split.cpp \
					isCharset.cpp \
					stringUtils.cpp \
					signals.cpp
UTILS_SRCS		=	$(addprefix $(S_DIR)$(S_UTILS_DIR), $(UTILS_SOURCES))

MESSAGE_SOURCES	=	messageBuilder.cpp \
					Motd.cpp
MESSAGE_SRCS	=	$(addprefix $(S_DIR)$(S_MESSAGE_DIR), $(MESSAGE_SOURCES))

SOURCES			=	my_server.cpp
#SOURCES			+=	$(IRC_SOURCES) \
#					$(SERVER_SOURCES)
SRCS			=	my_server.cpp

OBJECTS			=	$(SOURCES:.cpp=.opp)
IRC_OBJECTS		=	$(IRC_SOURCES:.cpp=.opp)
CMD_OBJECTS		=	$(CMD_SOURCES:.cpp=.opp)
SERVER_OBJECTS	=	$(SERVER_SOURCES:.cpp=.opp)
UTILS_OBJECTS	=	$(UTILS_SOURCES:.cpp=.opp)
MESSAGE_OBJECTS	=	$(MESSAGE_SOURCES:.cpp=.opp)

OBJS			=	$(addprefix $(O_DIR), $(OBJECTS))
IRC_OBJS		=	$(addprefix $(O_DIR), $(IRC_OBJECTS))
CMD_OBJS		=	$(addprefix $(O_DIR), $(CMD_OBJECTS))
SERVER_OBJS		=	$(addprefix $(O_DIR), $(SERVER_OBJECTS))
UTILS_OBJS		=	$(addprefix $(O_DIR), $(UTILS_OBJECTS))
MESSAGE_OBJS	=	$(addprefix $(O_DIR), $(MESSAGE_OBJECTS))
#DBG_OBJS	=	$(addprefix $(O_DBG_DIR),$(OBJECTS))
#FDBG_OBJS	=	$(addprefix $(O_FDBG_DIR),$(OBJECTS))

all				:
				@echo "Building $(NAME):"
				@make --no-print-directory $(NAME)

$(NAME)			:	$(OBJS) $(IRC_OBJS) $(CMD_OBJS) $(SERVER_OBJS) $(MESSAGE_OBJS) $(UTILS_OBJS)
				@echo "$^"
				@echo "Linking $(NAME)..."
				@$(CC) $(CFLAGS) $^ -o $@
				@echo "$(NAME) built successfully!"

$(OBJS)			:	$(O_DIR)%.opp: %.cpp $(DEPENDS)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

$(IRC_OBJS)		:	$(O_DIR)%.opp: $(S_DIR)$(S_IRC_DIR)%.cpp $(DEPEND_IRC)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

$(CMD_OBJS)		:	$(O_DIR)%.opp: $(S_DIR)$(S_CMD_DIR)%.cpp $(DEPEND_CMD)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				@$(CC) $(CFLAGS) -c $< -o $@

$(SERVER_OBJS)	:	$(O_DIR)%.opp: $(S_DIR)$(S_SERVER_DIR)%.cpp $(DEPEND_SERVER)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

$(UTILS_OBJS)	:	$(O_DIR)%.opp: $(S_DIR)$(S_UTILS_DIR)%.cpp $(DEPEND_UTILS)
				@echo "Compiling $<"
				@mkdir -p $(@D)
				$(CC) $(CFLAGS) -c $< -o $@

$(MESSAGE_OBJS)	:	$(O_DIR)%.opp: $(S_DIR)$(S_MESSAGE_DIR)%.cpp $(DEPEND_MESSAGE)
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
