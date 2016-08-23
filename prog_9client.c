#include<stdio.h>
#include<fcntl.h>

// included for file handling using write()
#include<unistd.h>

// included to access inet_addr,socket(), send(), recv() method
#include<arpa/inet.h>

int main()
{ 
  char fname[50],buffer[1024];
  int s,n;
  struct sockaddr_in address;

  // sockaddr_in is used for ip manipulation
  address.sin_family=AF_INET;

  // default family address
  address.sin_port=htons(15000);

  // port through which IPC is established
  address.sin_addr.s_addr=INADDR_ANY;

  // any address can be asssigned to the client
  if((s=socket(AF_INET,SOCK_STREAM,0))<0) 
  {

  // socket() creates an endpoint for communication and returns a descriptor.
    perror("socket\n");
    connect(s,(struct sockaddr*)&address,sizeof(address)); 
  }

  // connect - initiate a connection on a socket
  printf("enter file name:\n");
  scanf("%s",fname);
  printf("sending request..\n");
  send(s,fname,sizeof(fname),0);

  // send() is used to transmit a message to another socket.
  printf("received response\n");
  while((n=recv(s,buffer,sizeof(buffer),0))>0) 
  {

  // recv() used to receive messages from a socket, and may be used to 
  // receive data on a socket whether or not it is connection-oriented. 
  // Returns a file descriptor
    write(1,buffer,n); 
  }

  // send a message to another user
  return 0;
}