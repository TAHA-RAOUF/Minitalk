FLAGS = -Wall -Wextra -Werror 
CC = gcc 
SERVER = server
CLIENT = client

ALL : $(SERVER) $(CLIENT)

$(SERVER) : server.c
		$(CC) $(FLAGS) 	server.c -o server
$(CLIENT) : client.c
		$(CC) $(FLAGS) client.c -o client

clean : ALL
	rm -rf  $(SERVER) $(CLIENT)

fclean : clean 
	
re : ALL 

.PHONY : ALL clean fclean re 
