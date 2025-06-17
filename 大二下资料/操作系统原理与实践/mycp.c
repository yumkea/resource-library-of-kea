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


int fd_src,fd_dest;	//�ļ������� 
char src[500],dest[500];	//�ļ�·�� 
char *buf;		//��������ȡԴ�ļ����ݮ�
int src_path_len,dest_path_len,buf_len; //·�������Լ���ȡ��Դ�ļ����ݵĳ��� 
int src_len;		//Դ�ļ����ݳ� 
char choice[10];	//����ĸ��ǻ�׷��д���ѡ�� 

bool isDirectory(char* path)
{
	struct stat ss;
	stat(path,&ss);
	return S_ISDIR(ss.st_mode)?true:false;
}
int main(int argc, char * argv[]){
	struct stat buff;
    	if(argc!=3){
        	printf("������ʧ���������������.\n");
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
			printf("ERROR:Դ�ļ�������\n");
			exit(1);	}
        		if(stat(argv[1],&buff)<0) //��ȡ�ļ�����ʧ�� 
		{       
           	 	printf("lstat error\n");	exit(1);	}
		
		if(isDirectory(argv[1]))
		{
		printf("ERROR:Դ�ļ���Ŀ¼�ļ�\n");	exit(1);	}


		if((src_len=lseek(fd_src,0,SEEK_END))==-1)
		 {
			printf("lseek��ȡԴ�ļ�ʧ��\n");	exit(1);	}

		buf = (char*)malloc(sizeof(char)*src_len*10);//Ϊ�����������ڴ� 
		lseek(fd_src,0,SEEK_SET);	//���ļ����¶�λ����ͷ�����ں����ȡ 

		if((read(fd_src, buf, src_len-1))==-1)
		{
			printf("��ȡԴ�ļ�ʧ��\n");	exit(1);	}
if(isDirectory(dest))
		{
			src_path_len=strlen(src);
			dest_path_len=strlen(dest);
			int pos=0;
			for(int i = 0; i < src_path_len; i++)   if(src[i]=='/') pos=i;
			if(pos==0) dest[dest_path_len++] = '/';
			for(int i = pos; i < src_path_len; i++) 
				dest[dest_path_len++] = src[i];//ʹĿ���ļ����¸��Ƶ��ļ���Դ�ļ�ͬ�� 
		}
 if((fd_dest=open(dest,O_RDWR))==-1)
		{
			printf("Ŀ���ļ������ڣ���������\n");
			if((fd_dest=open(dest,O_RDWR|O_CREAT,0666))==-1)
				printf("����ʧ��\n");
			}
else
		{
			printf("Ŀ���ļ��Ѵ��ڣ���ѡ�񸲸ǻ�׷��д��\n");
			printf("Please input overwrite or append?\n");
			scanf("%s",choice);
			while(1)
			{
				if(choice[0]=='o') //���� 
				{
					if((fd_dest=open(dest, O_RDWR|O_TRUNC))==-1){ printf("����ʧ��\n");
					exit(1);}
					break;
				}
				else if(choice[0]=='a')//׷������ 
				{
					if((fd_dest=open(dest, O_RDWR|O_APPEND))==-1){ printf("׷������ʧ��\n");
					exit(1);}
					break;
				}
				else printf("������overwrite or append?\n");
			}

		}
		
		if((write(fd_dest, buf, src_len-1))==-1)
		{
			printf("д���ļ�ʧ��\n");	exit(1);	}

		
	printf("��ϲ��ɿ���\n");

	close(fd_src);
	close(fd_dest);		
	free(buf);
	}
  	 return 0;	
}			
