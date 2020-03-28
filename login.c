#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
struct admin
{
	char user_name[15];
	int pin;
}a[10];

struct student
{
	char s_name[30];
	char address[100];
	char gender;
	int roll;
	int age;
	float cgpa;
	};

FILE * fp;
FILE * fs;
void menu();
void delete();
void display();



int main()
{  
	
	menu();
}
	
	
	
	
	
	
void menu()
{
	 struct check
	{
		char u_name[15];
		int p;
	}x; 
	
	int i=0;
	char name[15];
	int code,c;
	fp=fopen("Admin.dat","rb");
	char choice;
		
    start:
	printf("Please enter your username\n");
	gets(name);
	
	printf("Please enter your unique 4-digit pin\n");
	scanf("%d",&code);
	while((getchar())!='\n');
	
	
	
	while(fread(&x,sizeof(x),1,fp)==1)
	{
		if((strcmp(x.u_name,name)==0) && x.p==code)
		{
			i=1;
			break;
		}
	}
	if (i==0)
	{
		printf("Incorrect username or password. Please enter again\n");
		rewind(fp);goto start;
	}
	
	else   
{
			do
			{
				printf("Welcome %s!\n",name);
				printf("The file consists of the following entries\n"); 
			    display();
				begin:
				printf("\nPlease select your operation:\n");
				printf("1.Search for a student's record   2.Delete student's record   3.Obtain overall performance   0.logout\n");
				scanf("%d",&c);		
				switch(c)
				{
					//search();break;
					case 2:do
							{
								delete();
					            printf("Do you want to delete another entry?\n");
					            printf("Enter 'y' or 'n'\n");
					            scanf("%c",&choice);
					            choice=tolower(choice);
							}while(choice=='y');printf("This is the final data:\n");display();goto begin;
					
					//result();break;
					case 0:printf("Successfully logged out\n");exit(0);
					default:printf("Invalid choice. Please try again\n");
				}
				}while(c!=0);
		}

}

void delete()
{
	struct student c;
	
	int r; int f=0;
	
	FILE * fd;
	fd=fopen("new.dat","wb");
	fs=fopen("Student.dat","rb");
	
	start:
	printf("Enter roll number of student\n");
	scanf("%d",&r);
	while((getchar())!='\n');

	while(fread(&c,sizeof(c),1,fs)==1)
		{
		if(r==c.roll)
		{
			f=1;
			break;
		}
	}

	if(f==0)
		{
			printf("invalid entry. Please enter roll number again\n");
			rewind(fs);
			goto start;
		}
	rewind(fs);
	while(fread(&c,sizeof(c),1,fs)==1)
		if(c.roll!=r)
			fwrite(&c,sizeof(c),1,fd);
			
	fclose(fs);
	fclose(fd);		
	remove("Student.dat");
	rename("new.dat","Student.dat");
}











void display()
{  
	fs=fopen("Student.dat","rb");
	printf("\n================================================================\n");
	struct student stu;
	
	rewind(fs);
	printf("%-20s%-10s%-50s%-10s%-10s%s\n","NAME","AGE","ADDRESS","GENDER","ROLL","CGPA");
	
	while(fread(&stu,sizeof(stu),1,fs)==1)
			printf("%-20s%-10d%-50s%-10c%-10d%f\n",stu.s_name,stu.age,stu.address,stu.gender,stu.roll,stu.cgpa);

	printf("================================================================\n");	
	fclose(fs);
}
