/* 
======================================================================
	Socket Programming:

   This progam is for creating a server socket. The server socket
       (a) is created with a socket() call
       (b) is bound with an IP address and Port
       (c) listens for connections with a listen() call 
       (d) accepts a connection with a accept() call
       (e) sends data with send() call and 
       (f) finshes its life with a close() call.
	---------------------------------------------------------------------- 
    *** htons(Port_No) is for converting HBO to NBO where
        ----> HBO: Host-Byte-Order
        ----> NBO: Network-Byte-Order
        Byte Order: Big Indian & Little Indian
	---------------------------------------------------------------------- 
    Necessary System Calls:
       1. socket(domain, type, protocol)
       2. bind()
       3. listen() 
       4. send()
       5. recv()
       6. close()         
   ----------------------------------------------------------------------
    A special message:

            "good bye" or "Good bye" or "Good Bye"

    any of these three messages from,
                            either sender's end or
                            receiver's end or
                            both

                            2 times
                        
                        will close the socket
   ----------------------------------------------------------------------
    SHAH MD. IMRAN HOSSAIN
    Dept. of CSE, University of Rajshahi,
    Rajshahi-6205, Bangladesh
   ---------------------------------------------------------------------- 
	======================================================================
*/

#include <sys/socket.h> 	// For system call: socket().
#include <netinet/in.h>     // For sockaddr_in, sockaddr, htons(). 
#include <unistd.h>         // For close().
#include <stdio.h>          // For standard input-output.
#include <stdbool.h>



int main() 
{
    // Create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    // Define server address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(12000);  // here 12000 is a port number
    server_address.sin_addr.s_addr = INADDR_ANY; // to connect any client

    // Bind the above socket to the specified IP and port
    int addr_len;
    struct sockaddr *sockaddr_ptr;
    addr_len = sizeof(server_address);
    sockaddr_ptr = (struct sockaddr *)&server_address;
    bind(server_socket, sockaddr_ptr, addr_len);
        
    // Listen
    listen(server_socket, 5); 

    // Here , 5 indicates how many clients can connect at a time

    // Accept
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    // Send and receive message to the client
    

	//declaring the variables

	char server_message[256];
	char client_response[256];
	bool write = true;
    int good_bye_count = 0;
    

	
	//just creating a infinite loop

	while(good_bye_count != 2)
	{
	
		printf("client waiting for your response\n");

		scanf ("%[^\n]%*c", server_message);

		
		
	    int sending = send(client_socket, server_message, sizeof(server_message), 0);
		
		if(sending < 0)
		{
			perror("In server sending");
		}

        if(strcmp(server_message,"good bye") == 0 || strcmp(server_message,"Good Bye") == 0 || strcmp(server_message,"Good bye") == 0)
        {
            good_bye_count++;
        }


		printf("waiting\n");

		int receiving = recv(client_socket,client_response,sizeof(client_response),0);

		if(receiving < 0)
		{
			perror("In server receiving");
		}

		printf("client: %s\n", client_response);

        if(strcmp(client_response,"good bye") == 0 || strcmp(client_response,"Good Bye") == 0 || strcmp(client_response,"Good bye") == 0)
        {
            good_bye_count++;
        }	

	}


    // Close socket
    close(server_socket);

}
