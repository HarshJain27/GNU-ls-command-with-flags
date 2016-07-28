
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<time.h>
#include<dirent.h>
#include<grp.h>
#include<pwd.h>

#define RESET_COLOR "\e[m" 
#define MAKE_BLUE "\e[36m"
#define MAKE_PURPLE "\e[35m"

char* files[20];
char* allFiles[1000];
int tf=0;
char options[6]={' '};
int parseInput(int argc1,char **argv1);
void scanOptions(int);
void checkFileExist();
void alignAndPrint(struct stat, struct group* , struct passwd* , char* ,int );
void parseFiles(int);
void parseFilesAndPrintIndexNumber();
void parseFilesAndList(int);
int countTotal();

int main(int argc, char *argv[])
{
int ifOptions;
ifOptions=parseInput(argc,argv);
scanOptions(ifOptions);
return 0;
}

int parseInput(int argc2, char** argv2)
{
int i,j,k=0;
char* tempArr;
int flag=0;
for(i=1;i<argc2;i++)
{
tempArr=argv2[i];
if(tempArr[0]=='-')
{
for(j=1;j<strlen(tempArr);j++)
{
if(tempArr[j]=='a' || tempArr[j]=='t' || tempArr[j]=='i' || tempArr[j]=='l' || tempArr[j]=='S' || tempArr[j]=='R')
{
flag=1;
if(tempArr[j]=='i') options[0]='i';
if(tempArr[j]=='t') options[1]='t';
if(tempArr[j]=='a') options[2]='a';
if(tempArr[j]=='l') options[3]='l';
if(tempArr[j]=='S') options[4]='S';
if(tempArr[j]=='R') options[5]='R';
}
else
{
printf("ls: invalid option -- '%c'",tempArr[j]);
exit(0);
}
}
}
else
{
files[k]=tempArr;
k++;
}
}
if(flag==0)
{
return -1;
}
return 1;
}




void scanOptions(int ifOptions)
{
if(ifOptions==-1){int flagI=0; checkFileExist(); parseFiles(flagI); }
else if(options[0]=='i' && options[3]==0) { int flagI=2; checkFileExist();   parseFilesAndList(flagI); }
else if(options[0]=='i' && options[3]=='l') { int flagI=1; checkFileExist(); parseFilesAndList(flagI);}
else if(options[3]=='l') {  int flagI=0; checkFileExist(); parseFilesAndList(flagI);  }
else if(options[2]=='a'){ int flagI=0; checkFileExist();   parseFiles(flagI);}
else if(options[3]=='a' && options[0]=='l') { int flagI=1; checkFileExist(); parseFilesAndList(flagI);}
else if(options[2]=='a' && options[0]=='i'){ int flagI=1; checkFileExist();   parseFiles(flagI);}
}





void parseFilesAndList(int flagI)
{
int x=0;
int flag1=0;
if(files[0]==00)
{
flag1=1;
files[0]="./";
}

while(files[x]!=NULL || flag1==1)
{
struct stat buff;
int temp=lstat(files[x],&buff);
if(temp==-1)
{


}
struct group* buff1;
struct passwd* buff2;
int gid=buff.st_gid;
int uid=buff.st_uid;
buff1=getgrgid(gid);
buff2=getpwuid(uid);

if(((buff.st_mode)&(S_IFMT))==S_IFDIR)
{
struct dirent** filesList;
int fno = scandir(files[x], &filesList, NULL, alphasort);
while(fno--)
{
struct stat currentBuff;
int temp2=lstat(filesList[fno]->d_name,&currentBuff);
if(temp2==-1)
{

}
allFiles[tf]=filesList[fno]->d_name;
tf++;
char* temp1=filesList[fno]->d_name;
if(temp1[0] == '.' && options[2]!='a')
{
x++;flag1=0; continue;
}
else
{
alignAndPrint(currentBuff,buff1,buff2,filesList[fno]->d_name,flagI);
flag1=0;
}
}
}
else
{
allFiles[tf]=files[x];
tf++;
alignAndPrint(buff,buff1,buff2,files[x],flagI);
}
x++;
}
}




void parseFiles(int flagI)
{

int x=0;
int flag1=0;
if(files[0]==00)
{
flag1=1;
files[0]="./";
}

while(files[x]!=NULL || flag1==1)
{
struct stat buff;
int temp1=lstat(files[x],&buff);
if(temp1==-1)
{

}
if(((buff.st_mode)&(S_IFMT))==S_IFDIR)
{
struct dirent** filesList;
int fno = scandir(files[x], &filesList, NULL, alphasort);
while(fno--)
{
char* temp1=filesList[fno]->d_name;
	if(temp1[0] == '.' &&  options[2]!='a')
	{
	x++;flag1=0; continue;
	}
	else
	{
		struct stat buff1;
		int temp2=lstat(filesList[fno]->d_name,&buff1);
		if(temp2==-1)
		{
		
		}
		
		if(flagI==1)
		{
			printf("%ld ",buff1.st_ino);
		}
		else
		{
		
			if(((buff1.st_mode)&(S_IFMT))==S_IFDIR)
		printf(MAKE_BLUE"  %s     \n"RESET_COLOR,filesList[fno]->d_name); 
			else if(((buff1.st_mode)&(S_IFMT))==S_IFLNK)
			printf(MAKE_PURPLE"  %s     \n"RESET_COLOR,filesList[fno]->d_name);
			else
			{
			printf(" %s \n",filesList[fno]->d_name);
			}
	

		}
	flag1=0;
	}
}

}
else
{
	if(flagI==1)
	{
	printf("%ld ",buff.st_ino);
	}
	else
	{
	printf("%s \n ",files[x]);
	}
}
x++;
}
}





void alignAndPrint(struct stat temp, struct group* buff1, struct passwd* buff2, char* fname, int flagI)
{
if(flagI==2)
{
printf("%10ld %s\n",temp.st_ino,fname);
}
else
{
if(flagI==1)
{
printf("%10ld ",temp.st_ino);
}

if(((temp.st_mode)&(S_IFMT))==S_IFDIR) printf("d");
else if(((temp.st_mode)&(S_IFMT))==S_IFLNK) printf("l");
else printf("-");
 printf( (temp.st_mode & S_IRUSR) ? "r" : "-");
 printf( (temp.st_mode & S_IWUSR) ? "w" : "-");
 printf( (temp.st_mode & S_IXUSR) ? "x" : "-");
 printf( (temp.st_mode & S_IRGRP) ? "r" : "-");
 printf( (temp.st_mode & S_IWGRP) ? "w" : "-");
 printf( (temp.st_mode & S_IXGRP) ? "x" : "-");
 printf( (temp.st_mode & S_IROTH) ? "r" : "-");
 printf( (temp.st_mode & S_IWOTH) ? "w" : "-");
 printf( (temp.st_mode & S_IXOTH) ? "x" : "-");
printf(" %2ld",temp.st_nlink);
printf(" %s",buff1->gr_name);
printf(" %s",buff2->pw_name);
printf(" %8ld",temp.st_size);

char* time=ctime(&temp.st_mtime);
int k=0,count=1;
while(count!=3)
{
if(time[k]==':')
{
count++;
}
if(count==3) { time[k]=00; break;}
k++;
}
printf(" %15s",time+3);

if(((temp.st_mode)&(S_IFMT))==S_IFLNK){ printf(MAKE_PURPLE"   %s     \n"RESET_COLOR,fname); }
else
if(((temp.st_mode)&(S_IFMT))==S_IFDIR){ printf(MAKE_BLUE"   %s     \n"RESET_COLOR,fname); }
else
printf("   %s\n",fname);
}
}

void checkFileExist()
{

int i=0,flag=0,temp;
while(files[i]!= NULL)
{

struct stat buffer;
temp=lstat(files[i],&buffer);
if(temp==-1 || temp<0)
{
flag=1;
}
i++;
}

if(flag==1)
{
printf("ls: cannot access : No such file or directory\n");
flag=0;
}
}
