#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void display();
FILE *fs;



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



int main()
{ 	
	int i,n;
	
	
	fs=fopen("Student.dat","ab+");
	
	struct student s[100];
	printf("Enter number of entries that you wanna make\n");
	scanf("%d",&n);
	
	
	
	for(i=0;i<n;i++)
	{
	printf("\nName: "); scanf("\n%[^\n]s",s[i].s_name);
	printf("Age: "); scanf("%d",&s[i].age);
	printf("Roll: "); scanf("%d",&s[i].roll);
	printf("CGPA: "); scanf("%f",&s[i].cgpa);
	printf("ADDRESS: "); scanf("\n%[^\n]s",s[i].address);
	printf("GENDER: "); scanf("\n%c",&s[i].gender);
	printf("CONTACT NO: "); scanf("\n%d",&s[i].contact_no);
		
		fwrite(&s[i],sizeof(s[i]),1,fs);
	}	
		
		printf("final result:\n");
		fclose(fs);	
		display();
		
	
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

