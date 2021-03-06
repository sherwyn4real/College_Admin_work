#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
	#define CLEAR_SCREEN "cls"		//command for windows cmd
#elif defined(linux)
	#define CLEAR_SCREEN "clear"		//command for linux terminal
#else
	#define CLEAR_SCREEN NULL
#endif

struct student
{
	char s_name[30];
	char address[100];
	char gender;
	int roll;
	int age;
	int contact_no;
	float cgpa;
};

FILE * fp;
FILE * fs;
void menu();
void delete();
void display();
void search();
void exam_result();
void sort_struct(struct student[],int);
void clearinputstream();
int go_back;

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
	int code,option;
	fp=fopen("Admin.dat","rb");
	char choice;
		
	start:
	printf("Please enter your username\n");
	scanf("%s",name);

	printf("Please enter your unique 4-digit pin\n");
	scanf("%d",&code);
	clearinputstream();
	
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
		system(CLEAR_SCREEN);
		printf("Incorrect username or password. Please enter again\n");
		rewind(fp);
		goto start;
	}
	else   
	{
		do
		{
			system(CLEAR_SCREEN);
			printf("Welcome %s!\n",name);
			printf("The file consists of the following entries\n");
			display();
			printf("\nPlease select your operation:\n");
			printf("1.Search for a student's record   2.Delete student's record   3.Obtain overall performance   0.logout\n");
			scanf("%d",&option);
			clearinputstream();
			switch(option)
			{
				case 1:
					do
					{
						go_back = 0;
						search();
						if(go_back == 0)
						{
							printf("Do you want to search another entry?(y/n):\n");
							scanf("\n%c",&choice);
							choice=tolower(choice);
						}
					}while(choice=='y' && go_back == 0);
					break;
				case 2:
					do
					{
						go_back = 0;
						delete();
						if(go_back==0)
						{
							printf("Successfully deleted record!\nDo you want to delete another record?\n");
							printf("Enter 'y' or 'n'\n");
							scanf("\n%c",&choice);
							choice=tolower(choice);
						}
					}while(choice=='y' && go_back==0);
					//goto begin;
					break;
				case 3:
					exam_result();
					break;
				case 0:
					system(CLEAR_SCREEN);
					printf("Successfully logged out\n");
					break;
				default:
					printf("Invalid choice! Hit Enter To try again\n");
					getchar();
			}
		}while(option!=0);
	}

}

void delete()
{
	struct student c;
	int r=-1; int f=0;
	
	start:
	system(CLEAR_SCREEN);
	display();
	printf("Enter roll number of student to be removed. Press 0 to return to Main Menu\n:");
	scanf("%d",&r);
	clearinputstream();

	if(r==0)
	{   
		go_back=1;
	}

	else
	{
		FILE * fd;
		fd=fopen("new.dat","wb");
		fs=fopen("Student.dat","rb");
		
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
			printf("invalid entry. Press enter to enter roll number again!\n");
			getchar();
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
		system(CLEAR_SCREEN);
	}
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

void search()
{
	int xroll;
	
	system(CLEAR_SCREEN);
	display();
	printf("\nEnter Student Roll no or Enter 0 to return to Main Menu\n:");
	scanf("%d",&xroll);
	while((getchar())!='\n'); //to clear the input stream
	system(CLEAR_SCREEN);
	
	if(xroll!=0) {
		printf("------------------------------------------------------------\n");
		struct student stu;
		int size = sizeof(struct student),flag=0;
		fs = fopen("Student.dat","rb");
	
		while(fread(&stu,size,1,fs)==1)
			if(stu.roll == xroll)
			{
				printf("Name: %s\nRoll no: %d\tCGPA: %f\nContact no: %d\n",stu.s_name,stu.roll,stu.cgpa,stu.contact_no);
				printf("Address: %s\nAge: %-5dGender: %c\n",stu.address,stu.age,stu.gender);
				flag = 1;
				break;
			}

		if(flag==0)
			printf("Record with roll no:%d not found! Check the number you entered!\n",xroll);
	
		fclose(fs);
		printf("------------------------------------------------------------\n");
	}
	else 
		go_back = 1;
}

void exam_result()
{
	system(CLEAR_SCREEN);
	fs = fopen("Student.dat","ab+");
	fseek(fs,0,SEEK_END);
	int size = sizeof(struct student);
	long int no_records = ftell(fs)/size;
	struct student stu[no_records];
	int pass=0,fail=0,distinction=0,firstclass=0,secondclass=0,passclass=0;
	rewind(fs);
	
	for(int i=0;fread(&stu[i],size,1,fs)==1;i++)
	{
		if(stu[i].cgpa>=7.5)
		{
			distinction++;
			pass++;
		}
		else if(stu[i].cgpa>=6.0)
		{
			firstclass++;
			pass++;
		}
		else if(stu[i].cgpa>=4.5)
		{
			secondclass++;
			pass++;
		}
		else if(stu[i].cgpa>=4.0)
		{
			passclass++;
			pass++;
		}
		else if(stu[i].cgpa<4.0)
		{
			fail++;
		}
	}
	
	sort_struct(stu,no_records);
	printf("\nEXAM RESULT");
	printf("\n-------------------------------------------------------------\n");
	printf("Pass: %d\nFail: %d\n",pass,fail);
	printf("Distinctions: %d\nFirst Class: %d\nSecond Class: %d\nPass Class: %d",distinction,firstclass,secondclass,passclass);
	printf("\n-------------------------------------------------------------");
	printf("\n\n%-6s%-20s%-10s%-6s\n","RANK","NAME","ROLL","CGPA");
	
	for(int i=0;i<=no_records-1;i++)
		printf("%-6d%-20s%-10d%-6f\n",i+1,stu[i].s_name,stu[i].roll,stu[i].cgpa);
	
	printf("\n-------------------------------------------------------------\n");
	printf("Press Enter To Return To Main Menu");
	getchar();
	
	fclose(fs);
}

//bubble sort technique
void sort_struct(struct student *e,int n)
{
	struct student temp;
	int i,j;
	
	for(j=0;j<n-1;j++)
		for(i=0;i<n-1-j;i++)
			if(e[i].cgpa < e[i+1].cgpa)
			{
				temp = e[i];
				e[i] = e[i+1];
				e[i+1] = temp;
			}
}

void clearinputstream()
{
	while((getchar())!='\n');
}
