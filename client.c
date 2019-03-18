
/* 
 * File:   client.c
 * Author: Muneeb Ahmad
 *
 */

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>

/*
 * client
 */



int main(int argc, char** argv) {


    
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("\nCould Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("\nSocket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("\nConnection Failed. Error!!!!!");
                return -1;
        }
        
        printf("\nConnected\n");
        
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("\nReceive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("\nServer Message: \n%s\n",server_message);
        
        
        //Get Input from the User
        
        printf("\nEnter Message: ");
        gets(client_message);
        
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("\nSend Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        memset(server_message,'\0',sizeof(server_message));
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("\nReceive Failed. Error!!!!!\n");
                return -1;
        }
        

        //strcpy(server_message,"Science,127.0.0.1,2000");
        printf("\nServer info Message: %s\n",server_message);
        
        char port[10],ip[20],name[10];
        
        int i=0;
        int j=0;
        for(i=0;server_message[i]!=',';i++)
        {
            name[i]=server_message[i];
        }
        i++;
        for(j=0;server_message[i]!=',';i++,j++)
        {
            ip[j]=server_message[i];
        }
        i++;
        for(j=0;server_message[i]!='\0';i++,j++)
        {
            port[j]=server_message[i];
        }
        
        
        int sub_server_port=atoi(port);
        
        printf("\nName:%s\n",name);
        printf("IP:%s\n",ip);
        printf("port: %i\n",sub_server_port);

        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        // Now Connection with Sub-Server
        
        //Cleaning the Buffers
        //memset(server_message,'\0',sizeof(server_message));
        //memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        socket_desc = -1;
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("\nCould Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("\nSocket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(sub_server_port);
        server_addr.sin_addr.s_addr = inet_addr(ip);
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("\nConnection Failed with Sub Server. Error!!!!!");
                return -1;
        }
        
        printf("\nConnected to Sub Server\n");
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("\nReceive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("\nSub Server Message: \n%s\n",server_message);
        
        
        //Get Input from the User
        
        printf("\nEnter Message: ");
        gets(client_message);
        
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("\nSub Server Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        memset(server_message,'\0',sizeof(server_message));
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("\nSub Server Receive Failed. Error!!!!!\n");
                return -1;
        }
        

        //strcpy(server_message,"Science,127.0.0.1,2000");
        printf("\nSub Server Message: %s\n",server_message);
        
        
        close(socket_desc);
        
    
    
    return (EXIT_SUCCESS);
}

