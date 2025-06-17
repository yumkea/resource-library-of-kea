#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdbool.h>


int fd_src,fd_dest;	//文件描述符 
char src[500],dest[500];	//文件路径 
char *buf;		//缓冲区读取源文件内容
int src_path_len,dest_path_len,buf_len; //路径长度以及读取到源文件内容的长度 
int src_len;		//源文件内容长 
char choice[10];	//输入的覆盖或追加写入的选择 

bool isDirectory(char* path)
{
	struct stat ss;
	stat(path,&ss);
	return S_ISDIR(ss.st_mode)?true:false;
}
int main(int argc, char * argv[]){
	struct stat buff;
    	if(argc!=3){
        	printf("参数丢失，请检查所输入参数.\n");
        	exit(1);
    	}
    	else{
		strcat(src,argv[1]);
        strcat(dest,argv[2]);
		if(isDirectory(src))
		{
			printf("ERROR:The source file cannot be a diretory\n");
			exit(-1);
		}
		if((fd_src=open(src,O_RDWR))==-1)
		{
			printf("ERROR:源文件不存在\n");
			exit(1);	}
        		if(stat(argv[1],&buff)<0) //获取文件属性失败 
		{       
           	 	printf("lstat error\n");	exit(1);	}
		
		if(isDirectory(argv[1]))
		{
		printf("ERROR:源文件是目录文件\n");	exit(1);	}


		if((src_len=lseek(fd_src,0,SEEK_END))==-1)
		 {
			printf("lseek读取源文件失败\n");	exit(1);	}

		buf = (char*)malloc(sizeof(char)*src_len*10);//为缓冲区分配内存 
		lseek(fd_src,0,SEEK_SET);	//将文件重新定位到开头，便于后面读取 

		if((read(fd_src, buf, src_len-1))==-1)
		{
			printf("读取源文件失败\n");	exit(1);	}
if(isDirectory(dest))
		{
			src_path_len=strlen(src);
			dest_path_len=strlen(dest);
			int pos=0;
			for(int i = 0; i < src_path_len; i++)   if(src[i]=='/') pos=i;
			if(pos==0) dest[dest_path_len++] = '/';
			for(int i = pos; i < src_path_len; i++) 
				dest[dest_path_len++] = src[i];//使目标文件下新复制的文件和源文件同名 
		}
 if((fd_dest=open(dest,O_RDWR))==-1)
		{
			printf("目标文件不存在，即将创建\n");
			if((fd_dest=open(dest,O_RDWR|O_CREAT,0666))==-1)
				printf("创建失败\n");
			}
else
		{
			printf("目的文件已存在，请选择覆盖或追加写入\n");
			printf("Please input overwrite or append?\n");
			scanf("%s",choice);
			while(1)
			{
				if(choice[0]=='o') //覆盖 
				{
					if((fd_dest=open(dest, O_RDWR|O_TRUNC))==-1){ printf("覆盖失败\n");
					exit(1);}
					break;
				}
				else if(choice[0]=='a')//追加输入 
				{
					if((fd_dest=open(dest, O_RDWR|O_APPEND))==-1){ printf("追加输入失败\n");
					exit(1);}
					break;
				}
				else printf("请输入overwrite or append?\n");
			}

		}
		
		if((write(fd_dest, buf, src_len-1))==-1)
		{
			printf("写入文件失败\n");	exit(1);	}

		
	printf("恭喜完成拷贝\n");

	close(fd_src);
	close(fd_dest);		
	free(buf);
	}
  	 return 0;	
}			
