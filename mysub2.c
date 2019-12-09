

#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>

int send_msg_to_main_server(char msg[])
{

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
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2001);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Send the message to my information to Main Server
        
        strcpy(server_message,msg);
        printf("%s",server_message);

        if(send(socket_desc, server_message, strlen(server_message),0) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}

struct client_info
{
    int socket;
    int port;
    char ip[10];
    struct client_info* loc;
};

void *client_thread_func (void* c_info)
{
    printf("starting client_thread_func\n");
    
    char server_message[2000], client_message[2000],port_buffer[7];
    struct client_info *info=(struct client_info*) c_info;
    int client_sock=info->socket;
    printf("\nSocket: %i",client_sock);
    printf("\nPort: %i",info->port);
    printf("\nIP: %s",info->ip);
    printf("\nmalloc: %s ",info->loc);
    
    char test_type[]="Enter your test type:\nGeometry\nAlgebra\nIQ\n";
    
    //Cleaning the Buffers

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    strcpy(server_message,test_type);
    if (send(client_sock, server_message, strlen(server_message),0)<0)
    {
        printf("client_thread_func Send Failed. Error!!!!!\n");
        return;
    }
    
    //Receive the message from the client

        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("client_thread_func Receive Failed. Error!!!!!\n");
                return;
        }


        printf("client_thread_func Client Sock: %i\n",client_sock);
        printf("client_thread_func Client Message: %s\n",client_message);
        
        memset(server_message,'\0',sizeof(server_message));
        memset(port_buffer,'\0',sizeof(port_buffer));

        
        //Priyesh's contribution..
        
        int marks = 0 ;
        char pbuffer[20] ;
        if(strcmp(client_message,"Geometry")==0 )
        {
            marks = 0 ;
            memset(client_message,'\0',sizeof(client_message));
            char qus1[]  = "\nQus1\nIn a 30-60-90 triangle, the length of the hypotenuse is 6. What is the length of the shortest side?\na)2  b)3  c)3root2  d)3root3 " ;
            strcpy(server_message, qus1) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;

            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus2[]  = "\nQus2\nWhat is the area of a circle with a diameter of 16?\na)15pi  b)2225pi  c)3400pi  d)900pi " ;
            strcpy(server_message, qus2) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus3[]  = "\nQus3\nWhich of the following could be the side lengths of a right triangle?\na)3,13 and 14  b)4,5 and 6  c)5,10 and 15  d)5, 12 and 13 " ;
            strcpy(server_message, qus3) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"d") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus4[]  = "\nQus4\nWhat is the sum of the measures of the interior angles of a hexagon?\na)540deg  b)720deg  c)810deg  d)1080deg " ;
            strcpy(server_message, qus4) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus5[]  = "\nQus5\nIn a triangle two of the three angles are 95deg and 35deg. What is the third angle\na)35deg  b)40deg  c)45deg  d)50deg " ;
            strcpy(server_message, qus5) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;

            snprintf( pbuffer, 20 , "%d" , marks ) ;    

            memset(server_message,'\0',sizeof(server_message)) ;
 
            sprintf(port_buffer, "%d", info->port);
            strcpy(server_message,info->ip);
            strcat(server_message,",");
            strcat(server_message,port_buffer);
            strcat(server_message,",Math,");
            strcat(server_message,"Geometry");
            strcat(server_message,",");
            strcat(server_message,pbuffer) ;
        }
        else if(strcmp(client_message,"Algebra")==0 )
        {
            marks = 0 ;
            memset(client_message,'\0',sizeof(client_message));
            char qus1[]  = "\nQus1\nWhat is the product of -4 and +6?\na)2  b)5  c)24  d)-24 " ;
            strcpy(server_message, qus1) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;

            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus2[]  = "\nQus2\n Add: -5 + 7\na)15  b)2  c)12  d)-2 " ;
            strcpy(server_message, qus2) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus3[]  = "\nQus3\nWhat is the value of 5a + 2b when a = 2 and b = 6?\na)33  b)4  c)22  d)20 " ;
            strcpy(server_message, qus3) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus4[]  = "\nQus4\nWhat is the value of b^2 − 5 when b = 5?\na)54  b)20  c)30  d)10 " ;
            strcpy(server_message, qus4) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus5[]  = "\nQus5\nWhat is the value of 8x - 6 when x is equal to -1\na)14  b)40  c)-2  d)2 " ;
            strcpy(server_message, qus5) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;

            snprintf( pbuffer, 20 , "%d" , marks ) ;    

            memset(server_message,'\0',sizeof(server_message)) ;
 
            sprintf(port_buffer, "%d", info->port);
            strcpy(server_message,info->ip);
            strcat(server_message,",");
            strcat(server_message,port_buffer);
            strcat(server_message,",Math,");
            strcat(server_message,"Algebra");
            strcat(server_message,",");
            strcat(server_message,pbuffer) ;
        }
        else if(strcmp(client_message,"IQ")==0 )
        {
            marks = 0 ;
            memset(client_message,'\0',sizeof(client_message));
            char qus1[]  = "\nQus1\nWhich number should come next in the pattern? 37, 34, 31, 28\na)30  b)32  c)25  d)45 " ;
            strcpy(server_message, qus1) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;

            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus2[]  = "\nQus2\n1, 3, 5, 7, 8, 9, 11 – which one doesn’t belong to this series?\na)11  b)8  c)9  d)1 " ;
            strcpy(server_message, qus2) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus3[]  = "\nQus3\nWhich one of the five is least like the other four?\na)Dog  b)Mouse  c)Snake  d)Cat " ;
            strcpy(server_message, qus3) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus4[]  = "\nQus4\nIf all Bloops are Razzies and all Razzies are Lazzies, then all Bloops are definitely Lazzies?\na)False  b)True  " ;
            strcpy(server_message, qus4) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus5[]  = "\nQus5\nMary, who is 16 years old, is four times as old as her brother. How old will Mary be when she is twice as old as her brothers?\na)14  b)20  c)24  d)26 " ;
            strcpy(server_message, qus5) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;

            snprintf( pbuffer, 20 , "%d" , marks ) ;    

            memset(server_message,'\0',sizeof(server_message)) ;
 
            sprintf(port_buffer, "%d", info->port);
            strcpy(server_message,info->ip);
            strcat(server_message,",");
            strcat(server_message,port_buffer);
            strcat(server_message,",Math,");
            strcat(server_message,"IQ");
            strcat(server_message,",");
            strcat(server_message,pbuffer) ;
        }
        else
            strcpy(server_message, "Invalid Input!!!");
        

        //Send the message back to client
        if (send(client_sock, server_message, strlen(server_message),0)<0)
        {
                printf("client_thread_func Send Failed. Error!!!!!\n");
                return;
        }
        
        if(send_msg_to_main_server(server_message)==-1)
            return -1;
    
    close(client_sock);
    free(info->loc);
    pthread_exit(NULL); 
}

int Set_connection_for_clients(char my_ip[], char my_port[])
{   
    int port=atoi(my_port);
    
    
    int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;
        pthread_t thread;
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        server_addr.sin_addr.s_addr = inet_addr(my_ip);
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        
        while(1)
        {
            //Accept the incoming Connections

            client_size = sizeof(client_addr);
            client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);

            if (client_sock < 0)
            {
                    printf("Accept Failed. Error!!!!!!\n");
                    return -1;
            }
            else
            {
                struct client_info *info;
                info=malloc(sizeof(struct client_info));
                strcpy(info->ip,inet_ntoa(client_addr.sin_addr));
                info->port=ntohs(client_addr.sin_port);
                info->socket=client_sock;
                info->loc=info;
                
                int ret = pthread_create(&thread, NULL, client_thread_func, (void *)info);
                if (ret!=0)
                {
                    printf("Error In Creating Thread\n");
                }
            }


            //printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        }
              
        //Closing the Socket


        close(socket_desc);
        pthread_exit(NULL); //Terminates the parent thread    
    
    
    return 0;
}


int main(int argc, char** argv) {

    char msg[100];
    char my_test_name[]="Math";
    char my_ip[]="127.0.0.1";
    char my_port[]="2020";
    
    memset(msg,'\0',sizeof(msg));

    strcpy(msg,my_test_name);
    strcat(msg,",");
    strcat(msg,my_ip);
    strcat(msg,",");
    strcat(msg,my_port);
        
    if(send_msg_to_main_server(msg)==-1)
        return -1;
    
    Set_connection_for_clients(my_ip,my_port);

    
    return (EXIT_SUCCESS);
}
