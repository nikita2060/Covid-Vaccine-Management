#include<conio.h>
#include <stdio.h>
#include<stdlib.h>
#include <windows.h>

void gotoxy(int x,int y)//placing pointer in desired location
{
	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);

}

typedef struct Vaccine
{
    char name[50];
    int quantity; 
} Vaccine;

typedef struct Person
{
    char name[50], province[50], district[50], phone_number[10];
    int citizenship_id, doses;
} Person;

void registration ();
int book_appointment (int);
// void vaccine_stocks();
// void add_vaccine_stocks();
int search_person(int);
void person_details(int);

int main()
{
	int choice,citizenship_no;
    while(1)
    {
        printf("Enter your choice\n");
        printf("1. Registration\n");
        printf("2. Book appointment\n");
        printf("3. View vaccine stocks\n");
        printf("4. Add vaccine stocks\n");
        printf("5. Search details of a person\n");
		printf("6. Exit\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            registration();
            break;
            case 2:
			printf("Enter citizenship");
			scanf("%d",&citizenship_no);
            book_appointment(citizenship_no);
			
            break;
            // case 3:
            // vaccine_stocks();
			// break;
			// case 4:
			// add_vaccine_stocks();
			// break;
			case 5:
			person_details(citizenship_no);
			break;
			case 6:
			exit(0);
			default:
			printf("Invalid Choice\n");
			break;
        }
    }

    return 0;
}


void registration ()
{
    char ch;
    FILE *fp;
    fp=fopen("registration.txt","r+");
	if(fp == NULL)
	{
		fp = fopen("registration.txt","w+");
		if(fp == NULL)
		{
			printf("Unable to open file\n");
			exit(0);
		}
	}
	Person person;					//person in an instance of structure "Person"
    person.doses=0;
    printf("Enter name\n");
    scanf("%s", &person.name);
    printf("Enter citizenship id\n");
    scanf("%d", &person.citizenship_id);

	if ( search_person(person.citizenship_id) == 1) 
	{
		printf("Record Already exists\n");
		return;
	}



    printf("Enter province no\n");
    scanf("%s", &person.province);
    printf("Enter District\n");
    scanf("%s", &person.district);
    printf("Enter phone number\n");
    scanf("%s", &person.phone_number);

	//write structure into the file
    fwrite(&person,sizeof(person),1,fp);
    fclose(fp);
	printf("Do you want to book appointment(Y-Yes ans N-No)? ");
    scanf("%c",&ch);
    if(ch=='y')
    book_appointment(person.citizenship_id);
}  

int book_appointment (int citizenship_id)
{
    Person person;
    FILE *fp,*fp_temp;
    // Person person;

    fp = fopen ("registeration.txt", "r");
    fp_temp=fopen("temp.txt","w");
    
    if (fp == NULL)
    {
        //printf("Error opening file\n");
        return 0;
    }
	while( fread(&person,sizeof(person),1,fp) )
	{
		if(person.citizenship_id == citizenship_id)
        {
            if(person.doses >= 2)
            {
                printf("You can't book appointment.Already completed 2 doses!");
                fclose(fp_temp);
                rename("temp.txt","xyz.txt");
                remove("xyz.txt");
                return;
            }
            person.doses++;
        }
        fwrite(&person,sizeof(person),1,fp_temp);
	}
    fclose(fp);
    fclose(fp_temp);
    rename("registeration.txt","xyz.txt");
    remove("xyz.txt");
    rename("temp.txt","registeration.txt");
}

// void vaccine_stocks()
// {
	
// }

// void add_vaccine_stocks()
// {
	
// }

int search_person(int citizenship_id)		//return 0 if not found and return 1 if found
{
    FILE *fp;
    Person person;

    fp = fopen ("registeration.txt", "r");
    if (fp == NULL)
    {
        //printf("Error opening file\n");
        return 0;
    }
	while( fread(&person,sizeof(person),1,fp) )
	{
		if(person.citizenship_id == citizenship_id)
        {
            return 1;
        }     
	}
	return 0;
}

void person_details(int citizenship_id)
{
    FILE *fp;
    Person person;

    fp = fopen ("registeration.txt", "r");
    if (fp == NULL)
    {
        //printf("Error opening file\n");
        // return 0;
    }
	while( fread(&person,sizeof(person),1,fp) )
	{
		if(person.citizenship_id == citizenship_id)
        {
            printf("Name:%s\n",person.name);
            printf("Citizenship id:%d\n",person.citizenship_id);
            printf("Province no:%s\n",person.province);
            printf("District:%s\n",person.district);
            printf("Phone no:%s",person.phone_number);
            printf("No of dose taken:%d\n",person.doses);
        }
    }
}

