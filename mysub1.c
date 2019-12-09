#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include<pthread.h>

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
    
    char test_type[]="Enter your test type:\nPhysics\nChemistry\nBiology\n";
    
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
        if(strcmp(client_message,"Physics")==0 )
        {
            marks = 0 ;
            memset(client_message,'\0',sizeof(client_message));
            char qus1[]  = "\nQus1\nWhich of the following pairs represent two scalar quantities?\na)Mass,Acceleration  b)Temperature,Torque  c)Distance,Speed  d)Grvitational Intensity,Work " ;
            strcpy(server_message, qus1) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;

            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus2[]  = "\nQus2\nThe acceleration at a given instant of time is called as:\naAvg Acceleration  b)Instantaneous Acceleration  c)Variable Accleration  d)Zero Acceleration " ;
            strcpy(server_message, qus2) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus3[]  = "\nQus3\nWhich of the these physical quantities is a vector quantity?\na)Temperature  b)Speed  c)Gravitational Intensity  d)Work " ;
            strcpy(server_message, qus3) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus4[]  = "\nQus4\nA projectile will achieve maximum horizontal range at which angle?\na)90deg  b)60deg  c)45deg  d)30deg " ;
            strcpy(server_message, qus4) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"c") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus5[]  = "\nQus5\nWhich of the following are Polar vectors?\na)Displacement  b)Force  c)Both a and b  d)None " ;
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
            strcat(server_message,",Science,");
            strcat(server_message,"Physics");
            strcat(server_message,",");
            strcat(server_message,pbuffer) ;
        }
        else if(strcmp(client_message,"Chemistry")==0 )
        {
            marks = 0 ;
            memset(client_message,'\0',sizeof(client_message));
            char qus1[]  = "\nQus1\nWhich among the following scientists had discovered Radium?\n  a)Marie Skłodowska-Curie and Pierre Curie\n  b)André-Louis Debierne\n  c)Kasimir Fajans\n  d)Oswald Helmuth Göhring " ;
            strcpy(server_message, qus1) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"a") == 0 )
                marks++ ;

            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus2[]  = "\nQus2\n Which among the following elemtns are generally find in free state?\n  a)Group 11 elements\n  b)Group 12 elements\n  c)Group 13 elements\n  d)Group 13 Elements " ;
            strcpy(server_message, qus2) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"a") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus3[]  = "\nQus3\nWhich among the following is the most abundant organic compound in nature?\na)Glucose  b)Fructose  c)Sucrose  d)Cellulose " ;
            strcpy(server_message, qus3) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"d") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus4[]  = "\nQus4\nWhich among the following is an example of a Chemical Change?\n  a)Rusting of iron\n  b)Magnetisation of iron\n  c)Melting of iron\n  d)Heating of iron " ;
            strcpy(server_message, qus4) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"a") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus5[]  = "\nQus5\nWhich among the following would cause the bright red colur due to bursting of crackers?\na)Strontium  b)Sodium  c)Sulphur  d)Magnesium " ;
            strcpy(server_message, qus5) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"a") == 0 )
                marks++ ;

            snprintf( pbuffer, 20 , "%d" , marks ) ;    

            memset(server_message,'\0',sizeof(server_message)) ;
 
            sprintf(port_buffer, "%d", info->port);
            strcpy(server_message,info->ip);
            strcat(server_message,",");
            strcat(server_message,port_buffer);
            strcat(server_message,",Science,");
            strcat(server_message,"Chemistry");
            strcat(server_message,",");
            strcat(server_message,pbuffer) ;
        }
        else if(strcmp(client_message,"Biology")==0 )
        {
            marks = 0 ;
            memset(client_message,'\0',sizeof(client_message));
            char qus1[]  = "\nQus1\nWho is known as father of Zoology\na)Darwin  b)Aristotle  c)Lamark  d)Theophrastus " ;
            strcpy(server_message, qus1) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;

            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus2[]  = "\nQus2\nAnimal without red blood cells?\na)Frog  b)Earthworm  c)Snake  d)Peacock " ;
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
            char qus4[]  = "\nQus4\nIThe energy released by 1 gram of glucose is?\na)6kcal  b)4kcal  c)5kcal  d)3kcal " ;
            strcpy(server_message, qus4) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"b") == 0 )
                marks++ ;


            memset(server_message,'\0',sizeof(server_message)) ;
            memset(client_message,'\0',sizeof(client_message));
            char qus5[]  = "\nQus5\nThe phenomenon of summer sleep by animals is called?\na)Hibernation  b)Aestivation  c)laziness  d)Lethargy " ;
            strcpy(server_message, qus5) ;
            send( client_sock, server_message, sizeof(server_message),0 ) ;
            recv(client_sock, client_message, sizeof(client_message),0) ;

            if( strcmp(client_message,"a") == 0 )
                marks++ ;

            snprintf( pbuffer, 20 , "%d" , marks ) ;    

            memset(server_message,'\0',sizeof(server_message)) ;
 
            sprintf(port_buffer, "%d", info->port);
            strcpy(server_message,info->ip);
            strcat(server_message,",");
            strcat(server_message,port_buffer);
            strcat(server_message,",Science,");
            strcat(server_message,"Biology");
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
    char my_test_name[]="Science";
    char my_ip[]="127.0.0.1";
    char my_port[]="2010";
    
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
