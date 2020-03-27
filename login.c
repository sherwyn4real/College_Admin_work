#include<stdio.h>
#include<stdlib.h>
struct admin
{
	char user_name[15];
	int pin;
}a[10];
FILE * fp;
void data();




int main()
{  
	
	menu();
}
	
	
	
	
	
	
void menu()
{
	 struct check
	{
		char u-name;
		int p;
	}s; 
	
	
	data();   //data to be filled in admin.dat beforehand
	int i=1;
	char name;
	int code;
	fp=fopen("Admin.dat","rb");
		
	printf("Please enter your username\n");
	scanf("%s",&name);
	printf("Please enter your unique 4-digit pin\n");
	scanf("%d",&code);
	while(i++==10)
	{
		fread(&s,sizeof(s),1,fp);
		if(strcmp(s.u-name,name)==0 && s.p==code)
			break;
		}	
		
		
	if(i<=10)
		{	do
			{
				printf("Welcome %s!\n",name);
				printf("Please select your operation:\n");
				printf("1.Search for a student's record	2.Delete student's record	3.Obtain overall performance	0.logout\n");
				scanf("%d",&c);
				switch(c)
				{
					case 1:search(fp);break;
					case 2:delete(fp);break;
					case 3:result(fp);break;
					default:printf("Invalid choice. Please try again\n");
				}
				}while(c!=0);
				
					
	
	
	
	


void data()
{
	int i=1;
	fp=fopen("Admin.dat","wb");
	a[1].name="tesslyn";
	a[1].pin=5491;
	a[2].user_name="sherwyn";
	a[2].pin=7791;
	a[3].user_name="sajal"
	a[3].pin=6979;
	a[4].user_name="sebastian";
	a[4].pin=5523;
	a[5].user_name="ironman";
	a[5].pin=3000;
	a[6].user_name="joker";
	a[6].pin=6666;
	a[7].user_name="deadshot"
	a[7].pin=6190;
	a[8].user_name="hulk";
	a[8].pin=7721;
	a[9].user_name="chairman";
	a[9].pin=7000;
	a[10].user_name="bot";
	a[10].pin=0000;
	while(i++==10)
		fwrite(&a[i],sizeof(a[i]),1,fp);
	fclose(fp);
	}
