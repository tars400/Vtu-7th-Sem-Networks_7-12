#include<stdio.h>
#include<fcntl.h> 
//included for file handling using write(), read(), open() methods
#include<unistd.h>

// included to access inet_addr(), bind(), socket(), send(), recv(), accept() method
#include<arpa/inet.h>

int main()
{
  char fname[50],buffer[1024];
  int s,n,source,file;
  struct sockaddr_in address;
  address.sin_family=AF_INET;
  address.sin_port=htons(15000);

  // The htons() function converts the unsigned short integer hostshort from 
  // host byte order to network byte order 
  address.sin_addr.s_addr=INADDR_ANY;

  // any address can access the server
  printf("waiting for request...\n");
  s=socket(AF_INET,SOCK_STREAM,0);
  bind(s,(struct sockaddr*)&address,sizeof(address));
  listen(s,3);

  // listen - listen for connections on a socket
  source=accept(s,(struct sockaddr*)NULL,NULL);

  // accept a connection
  recv(source,fname,sizeof(fname),0);

  // receive a message from the client
  printf("request for file %s\n", fname);
  file=open(fname,O_RDONLY);

  // open file in read-only mode
  if(file<0)
        send(source,"file not found\n",20,0);
  else
        while((n=read(file,buffer,sizeof(buffer)))>0)

                // read the input being sent by the client
                send(source,buffer,n,0);
  printf("request sent\n");
  close(file);
  return 0;
}