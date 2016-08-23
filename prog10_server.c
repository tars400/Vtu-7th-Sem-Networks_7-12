 #include<stdio.h>
    #include<unistd.h>
    #include<fcntl.h>/*used for file handling*/
    #include<sys/stat.h>/*used for mkfifo function*/
    #include<sys/types.h>/*when compiled in gcc, mkfifo() has dependency on both types.h and stat.h*/
    int main()
    {
        char fname[50],buffer[1025];
        int req,res,n,file;
        mkfifo("req.fifo",0777);/*creates a fifo file of permission 777*/
        mkfifo("res.fifo",0777);
        printf("waiting for request...\n");
        req=open("req.fifo",O_RDONLY);/*opens a read-only file req.fifo and stores the file descriptor value in req*/
        res=open("res.fifo",O_WRONLY);/*opens a write & read file res.fifo and stores the file descriptor value in res*/
        read(req,fname,sizeof(fname));/* reads the content of the file req.fifo by referencing the file descriptor value req and stores it in fname array*/
        printf("received request for %s\n",fname);
        file=open(fname,O_RDONLY);/*opens fname as Read-only*/
        if(file<0)
            write(res,"File not found\n",15);
        else
        {
            while((n=read(file,buffer,sizeof(buffer)))>0)
            {
                write(res,buffer,n);
            }
        }
        close(req);
        close(res); 
        //unlink("req.fifo");
        //unlink("res.fifo");
        return 0;
    }
