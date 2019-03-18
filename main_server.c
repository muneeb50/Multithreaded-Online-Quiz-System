
/* 
 * File:   Main_Server.c
 * Author: Muneeb Ahmad
 */
#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include <stdlib.h>
#include <pthread.h>

/*
 * Main Server
 */

int check_format_of_sub_server_msg(char str[])
{
    int i=0;
    int count=0;
    for(i=0;i<strlen(str);i++)
    {
        if(str[i]==',')
            count++;
    }
    return count;
}

void *sub_server_thread_func (int *client_sock)
{
    printf("starting sub_server_thread_func\n");

    char server_message[2000], client_message[2000];

    //Cleaning the Buffers

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    //Receive the message from the client

    if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
    {
            printf("sub_server_thread_func Recieve Failed. Error!!!!!\n");
            return;
    }


    printf("\nsub_server_thread_func Client Sock: %i\n",client_sock);
    printf("\nsub_server_thread_func Client Message: %s\n",client_message);
    
    if(check_format_of_sub_server_msg(client_message)==2)
    {
        FILE *sub_server_info_File;
        sub_server_info_File = fopen("sub_server_info.txt", "a");
        char entry[200];

        strcpy(entry, client_message);
        strcat(entry, "\n");

        printf("Sub Server info Received: %s",client_message);

        fputs(entry, sub_server_info_File);
        fclose(sub_server_info_File);

    }
    else if(check_format_of_sub_server_msg(client_message)==4)
    {
        FILE *clients_records_File;
        clients_records_File = fopen("clients_records.txt", "a");
        char entry[200];

        strcpy(entry, client_message);
        strcat(entry, "\n");

        printf("Sub Server Message Recieved\nClient Record: %s",client_message);

        fputs(entry, clients_records_File);
        fclose(clients_records_File);
    }
    else
        printf("\nSub_server with socket %i msg format is not correct!!!\n",client_sock);

    

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    //Closing the Socket

    close(client_sock);
    
    pthread_exit(NULL);       
}

int get_sub_server_info(char test_name[],char* info)
{
    memset(info,'\0',sizeof(info));
    
    FILE *fp;
    char str[100];
    
    fp = fopen("sub_server_info.txt", "r");
    if (fp == NULL){
        printf("Could not open file!!\n");
        return 1;
    }
    int flag=0;
    while (fgets(str, sizeof(str), fp) != NULL)
    {
        int i=0;
        flag=1;
        while(i<strlen(test_name))
        {
            if(str[i]!=test_name[i])
            {
                flag=0;
                break;
            }
            i++;
        }
        if(flag==1)
        {    
            strcpy(info,str);
            
            char *newline,*carriage_return;
            newline = strchr(info,'\n');
            if(newline != NULL)
            *newline = '\0';

            carriage_return = strchr(info,'\r');
            if(carriage_return != NULL)
            *carriage_return = '\0';
            
            return 0;
        }
    }
    fclose(fp);
    return 1;

    
}


void *client_thread_func (int *client_sock)
{

    printf("starting client_thread_func\n");
    char server_message[2000], client_message[2000];
    char str[]="Please Enter your Test option\nScience\nMath\nEnglish\n\n";

    //Cleaning the Buffers

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));
    
    strcpy(server_message,str);
    if (send(client_sock, server_message, strlen(server_message),0)<0)
    {
        printf("client_thread_func Send Failed. Error!!!!!\n");
        return;
    }

    //while(1)
    //{
        //Receive the message from the client

        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("client_thread_func Receive Failed. Error!!!!!\n");
                return;
        }

        printf("client_thread_func Client Sock: %i\n",client_sock);
        printf("client_thread_func Client Message: %s\n",client_message);
		
        if(get_sub_server_info(client_message,server_message)==1)
            strcpy(server_message, "Invalid Input!!!");
        

        //Send the message back to client
        if (send(client_sock, server_message, strlen(server_message),0)<0)
        {
                printf("client_thread_func Send Failed. Error!!!!!\n");
                return;
        }

        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));


    //}
    //Closing the Socket

    close(client_sock);
    
    pthread_exit(NULL);       
}


void *sub_server_func (int *sub_socket_desc)
{
    printf("starting sub_server_func\n");
    int client_sock, client_size; 
    struct sockaddr_in client_addr;
    char server_message[2000], client_message[2000];
    pthread_t thread4;
    
    //Cleaning the Buffers

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    
    while(1){


        //Accept the incoming Connections

        client_size = sizeof(client_addr);
        client_sock = accept(sub_socket_desc, (struct sockaddr*)&client_addr, &client_size);

        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return;
        }
        else
        {
            
            int ret = pthread_create(&thread4, NULL, sub_server_thread_func, (int*)client_sock);
            if (ret!=0)
            {
                            printf("Error In Creating Thread\n");
            }
        }

        printf("1-Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        
    }
    close(sub_socket_desc);
    pthread_exit(NULL);    
}
void *client_func (int *socket_desc)
{
    printf("starting client_func\n");
    int client_sock, client_size; 
    struct sockaddr_in client_addr;
    char server_message[2000], client_message[2000];
    pthread_t thread3;
    
    //Cleaning the Buffers

    memset(server_message,'\0',sizeof(server_message));
    memset(client_message,'\0',sizeof(client_message));

    
    while(1){


        //Accept the incoming Connections

        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);

        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return;
        }
        else
        {
            
            int ret = pthread_create(&thread3, NULL, client_thread_func, (int*)client_sock);
            if (ret!=0)
            {
                            printf("Error In Creating Thread\n");
            }
        }

        printf("1-Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));

        
    }
    close(socket_desc);
    pthread_exit(NULL);   
}

int main(int argc, char** argv) {

    
    int socket_desc, sub_socket_desc, client_sock, client_size; 
    struct sockaddr_in server_addr, sub_server_addr, client_addr;
    pthread_t thread1,thread2;

    //Creating Socket

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    sub_socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc < 0)
    {
            printf("Could Not Create Socket. Error!!!!!\n");
            return -1;
    }
    printf("Socket Created\n");
    if(sub_socket_desc < 0)
    {
            printf("Could Not Create Sub Socket. Error!!!!!\n");
            return -1;
    }


    printf("Sub Socket Created\n");

    //Binding IP and Port to socket

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(2000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sub_server_addr.sin_family = AF_INET;
    sub_server_addr.sin_port = htons(2001);
    sub_server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
    {
            printf("Bind Failed. Error!!!!!\n");
            return -1;
    }        

    printf("Bind Done\n");
    
    if(bind(sub_socket_desc, (struct sockaddr*)&sub_server_addr, sizeof(sub_server_addr))<0)
    {
            printf("Sub Bind Failed. Error!!!!!\n");
            return -1;
    }        

    printf("Sub Bind Done\n");

    //Put the socket into Listening State

    if(listen(socket_desc, 1) < 0)
    {
            printf("Listening Failed. Error!!!!!\n");
            return -1;
    }

    printf("Listening for Incoming Connections.....\n");
    
    if(listen(sub_socket_desc, 1) < 0)
    {
            printf("Sub Listening Failed. Error!!!!!\n");
            return -1;
    }

    printf("Sub Listening for Incoming Connections.....\n");

    
    int ret1 = pthread_create(&thread1, NULL, sub_server_func, (int*)sub_socket_desc);
    if (ret1!=0)
    {
                    printf("Error In Creating Thread1\n");
    }
    int ret2 = pthread_create(&thread2, NULL, client_func, (int*)socket_desc);
    if (ret2!=0)
    {
                    printf("Error In Creating Thread2\n");
    }
    
    
    
    
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);
    //Closing the Socket

    //close(client_sock);
    
    close(socket_desc);
    pthread_exit(NULL); //Terminates the parent thread
    
    return (EXIT_SUCCESS);
}

