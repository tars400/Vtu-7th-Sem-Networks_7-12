 #include<stdio.h>
    #include<unistd.h>
    #include<fcntl.h>/*used for file handling*/
    #include<sys/stat.h>/*used to access mkfifo() method*/
    #include<sys/types.h>/*when compiled in gcc, mkfifo() has dependency on both types.h and stat.h*/
    int main()
    {
        char fname[50],buffer[1025];
        int req,res,n;
        req=open("req.fifo",O_WRONLY);/*opens a write&read-only file req.fifo and stores the file descriptor value in req*/
        res=open("res.fifo",O_RDONLY);/*opens a read-only file req.fifo and stores the file descriptor value in res*/
        printf("enter filename to request:\n");
        scanf("%s",fname);
        write(req,fname,sizeof(fname));
        printf("received response\n");
        while((n=read(res,buffer,sizeof(buffer)))>0)
        {
            write(1,buffer,n);/*writes content into the buffer*/
        }
        close(req);/*close the file*/
        close(res);
        return 0;
    }
