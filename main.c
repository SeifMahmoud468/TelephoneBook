#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>

typedef struct
{
    int day,month,year;
} DOB;
typedef struct
{
    char last_name[50],first_name[50];
    char number[30],email[100],address[100];
    DOB date;
} Contact;
Contact c[100];
int count=0;
char name[100];
void colorfuction(int ForgC)
{
    WORD wColor;
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}
int birthdayvalidation(DOB date)
{
    if(date.year>1500&&date.year<2021)
    {
        if(date.month>0&&date.month<13)
        {
            switch(date.month)
            {
            case 1:
                if(0<date.day&&date.day<32)
                    return 1;
                else
                    return 0;
                break;
            case 2:
                if((0<date.day&&date.day<29)||(date.year%4==0&&(0<date.day&&date.day<30)))
                    return 1;
                else
                    return 0;
                break;
            case 3:
                if(0<date.day&&date.day<32)
                    return 1;
                else
                    return 0;
                break;
            case 4:
                if(0<date.day&&date.day<31)
                    return 1;
                else
                    return 0;
                break;
            case 5:
                if(0<date.day&&date.day<32)
                    return 1;
                else
                    return 0;
                break;
            case 6:
                if(0<date.day&&date.day<31)
                    return 1;
                else
                    return 0;
                break;
            case 7:
                if(0<date.day&&date.day<31)
                    return 1;
                else
                    return 0;
                break;
            case 8:
                if(0<date.day&&date.day<32)
                    return 1;
                else
                    return 0;
                break;
            case 9:
                if(0<date.day&&date.day<31)
                    return 1;
                else
                    return 0;
                break;
            case 10:
                if(0<date.day&&date.day<32)
                    return 1;
                else
                    return 0;
                break;
            case 11:
                if(0<date.day&&date.day<31)
                    return 1;
                else
                    return 0;
                break;
            case 12:
                if(0<date.day&&date.day<32)
                    return 1;
                else
                    return 0;
                break;
            }
        }
        else
            return 2;
    }
    else
        return 3;
}
int phonenuumbervalidation(char number[])
{
    int i,x,index=0;
    x=strlen(number);
    if(number[0]=='+'||isdigit(number[0]))
    {
        for(i=1; i<=x; i++)
        {
            index+=isdigit(number[i]);
        }
        if(index==i-2)
            return 1;
        else
            return 0;
    }
    else
        return 0;
}
int Emailvalidation(char mail[])
{
    int AtIndex=0,DotIndex=0,ErroIndex=-2,i;
    for(i=1; i<strlen(mail); i++)
    {
        if(isalpha(mail[0])&&mail[0]!='.'&&mail[0]!='+'&&mail[0]!='-'&&mail[0]!='_'&&mail[0]!='*')
        {
            if(mail[i]=='@')
            {
                AtIndex=i;
                ErroIndex++;
            }
            if(mail[i]=='.')
                DotIndex=i;
        }
    }
    if(AtIndex==0||ErroIndex>=0||DotIndex+2>strlen(mail))
        return 0;
    if(DotIndex>AtIndex+1)
        return 1;
    else
        return 0;
}
void SortByName()
{
    int i, j;
    Contact swap;
    for (i = 0; i < count-1; i++)
    {
        for (j = 0; j < count-i-1; j++)
        {
            if (strcasecmp(c[j].last_name,c[j+1].last_name)>0)
            {
                swap=c[j+1];
                c[j+1]=c[j];
                c[j]=swap;
            }
            if (strcasecmp(c[j].last_name,c[j+1].last_name)==0)
            {
                if (strcasecmp(c[j].first_name, c[j+1].first_name)>0)
                {
                    swap=c[j+1];
                    c[j+1]=c[j];
                    c[j]=swap;
                }
            }
        }
    }
}
void SortByDOB()
{
    int i, j;
    Contact swap;
    for (i = 0; i < count-1; i++)
    {
        for (j = 0; j < count-i-1; j++)
        {
            if(c[j].date.year >c[j+1].date.year )
            {
                swap=c[j+1];
                c[j+1]=c[j];
                c[j]=swap;
            }
            else if(c[j].date.year==c[j+1].date.year )
            {
                if( c[j].date.month >c[j+1].date.month )
                {
                    swap=c[j+1];
                    c[j+1]=c[j];
                    c[j]=swap;
                }
                else if( c[j].date.month==c[j+1].date.month )
                {
                    if( c[j].date.day >c[j+1].date.day )
                    {
                        swap=c[j+1];
                        c[j+1]=c[j];
                        c[j]=swap;
                    }
                }
            }
        }
    }
}
int load()
{
    count=0;
    FILE *f=fopen(name,"r");
    if(f!=NULL)
    {
        while(!feof(f))
        {
            fscanf(f,"%[^,],",c[count].last_name );
            fscanf(f,"%[^,],",c[count].first_name);
            fscanf(f,"%d-%d-%d,",&c[count].date.day,&c[count].date.month,&c[count].date.year);
            fscanf(f,"%[^,],",c[count].address);
            fscanf(f,"%[^,],",c[count].number);
            fscanf(f,"%s\n",c[count].email);
            count++;
        }
        fclose(f);
        return 1;
    }
    else
    {
        colorfuction(12);
        printf("\n\tFile not found!!\n\n");
        colorfuction(15);
    }
    return 0;
}
void Quert(char search[50])
{
    int i,index=0;
    colorfuction(12);
    printf("\n\n\t\tSearch results\n\n");
    colorfuction(15);
    printf("The records of last name: %s\n\n",search);
    for(i=0; i<count; i++)
    {
        if(strcasecmp(c[i].last_name,search)==0)
        {
            printf("First Name: %s\n",c[i].first_name);
            printf("Date Of Birth: %d-%d-%d\n",c[i].date.day,c[i].date.month,c[i].date.year);
            printf("Address: %s\nPhone Number: %s\nEmail: %s\n",c[i].address,c[i].number,c[i].email);
            printf("------------------------------\n");
            index++;

        }

    }
    if(index==0)
        printf("Sorry,There is No Contact info. found for Mr/Mrs: %s\n",search);
}
void Add()
{
    int index=-500;
    colorfuction(11);
    printf("\n\n\t Adding New Contact\n\n");
    colorfuction(15);
    printf("Enter first name \"Without Spaces\": ");
    scanf("%s",c[count].first_name );
    printf("Enter last name \"Without Spaces\": ");
    scanf("%s",c[count].last_name );
    do
    {
        if(index==-500)
            printf("Date of birth \"DD-MM-YYYY\": ");
        colorfuction(12);
        if(index==0)
            printf("Invalid day,Enter Date of birth again \"DD-MM-YYYY\": ");
        if(index==2)
            printf("Invalid month,Enter Date of birth again \"DD-MM-YYYY\": ");
        if(index==3)
            printf("Invalid year,Enter Date of birth again \"DD-MM-YYYY\": ");
        colorfuction(15);
        scanf("%d-%d-%d",&c[count].date.day,&c[count].date.month,&c[count].date.year);
        index=birthdayvalidation(c[count].date);
    }
    while(index!=1);
    printf("Address: ");
    getchar();
    gets(c[count].address);
    index=0;
    do
    {
        if(index==0)
            printf("Enter Phone number \"Only Digits\": ");
        else
        {
            colorfuction(12);
            printf("Error,Enter Phone number again \"Only Digits\": ");
            colorfuction(15);
        }
        index++;
        scanf("%s",c[count].number);
    }
    while(!phonenuumbervalidation(c[count].number));
    index=0;
    do
    {
        if(index==0)
            printf("Enter Email \"Without Spaces as Example@gmail.com\": ");
        else
        {
            colorfuction(12);
            printf("Error,Enter Email again \"Without Spaces as Example@gmail.com\": ");
            colorfuction(15);
        }
        index++;
        scanf("%s",c[count].email);
    }
    while(Emailvalidation(c[count].email)!=1);
    printf("\n\n");
    count=count+1;
}
void Delete(char first[50],char last[50])
{
    int i,j;
    for(i=0; i<count; i++)
    {
        if(strcasecmp(c[i].last_name,last)==0 && strcasecmp(c[i].first_name,first)==0)
        {
            for(j=i; j<count-1; j++)
                c[j]=c[j+1];
            count=count-1;
            i--;
        }
    }
}
void Modify(char name3[])
{
    int i,index=0,n[count];
    memset(n,-500,sizeof n);
    for(i=0; i<count; i++)
    {
        if(strcasecmp(c[i].last_name,name3)==0)
        {
            colorfuction(12);
            printf("Contact No.%d\n",i+1);
            colorfuction(15);
            printf("First Name: %s\nLast Name: %s\n",c[i].first_name,c[i].last_name);
            printf("Date of birth: %d-%d-%d\nPhone: %s\n",c[i].date.day,c[i].date.month,c[i].date.year,c[i].number);
            printf("Address: %s\nEmail: %s\n",c[i].address,c[i].email);
            printf("----------------------------------------\n");
            n[index]=i;
            index++;
        }
    }
    int x=0,t_value=0;
    if(index==0)
    {
        colorfuction(12);
        printf("\n\nThere is No Contact info. for Mr/Mrs: %s\n\n",name3);
        colorfuction(15);
    }
    else if(index==1)
        x=n[0];
    else
    {
        index=0;
        do
        {
            if(index==0)
                printf("\nEnter No. of contact you want to Modify: ");
            else
            {
                colorfuction(12);
                printf("Error,Enter No. of contact you want to Modify again: ");
                colorfuction(15);
            }
            index++;
            scanf("%d",&x);
            x=x-1;
            for(i=0; i<count; i++)
            {
                if(x==n[i])
                    t_value=1;
            }
        }
        while(t_value!=1);
    }
    if(x)
    {
        int y=0;
        while(y!=8)
        {
            colorfuction(11);
            printf("\nPlease,Select Modifying Section.\n");
            colorfuction(15);
            printf("1.First Name\n2.Last Name\n");
            printf("3.Date Of Birth\n4.Phone\n");
            printf("5.Address\n6.Email\n7.All Records\n8.Exit\n");
            index=0,t_value=0;
            do
            {
                if(index==0)
                    printf("Answer: ");
                else
                {
                    colorfuction(12);
                    printf("Error,Enter Answer again: ");
                    colorfuction(15);
                }
                index++;
                scanf("%d",&y);
                for(i=1; i<=8; i++)
                {
                    if(y==i)
                        t_value=1;
                }
            }
            while(t_value!=1);
            printf("\n\n");
            switch(y)
            {
            case 1:
                printf("Enter first name \"Without Spaces\": ");
                scanf("%s",c[x].first_name);
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            case 2:
                printf("Enter last name \"Without Spaces\": ");
                scanf("%s",c[x].last_name);
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            case 3:
                index=-500;
                do
                {
                    if(index==-500)
                        printf("Date of birth \"DD-MM-YYYY\": ");
                    colorfuction(12);
                    if(index==0)
                        printf("Invalid day,Enter Date of birth again \"DD-MM-YYYY\": ");
                    if(index==2)
                        printf("Invalid month,Enter Date of birth again \"DD-MM-YYYY\": ");
                    if(index==3)
                        printf("Invalid year,Enter Date of birth again \"DD-MM-YYYY\": ");
                    colorfuction(15);
                    scanf("%d-%d-%d",&c[x].date.day,&c[x].date.month,&c[x].date.year);
                    index=birthdayvalidation(c[x].date);
                }
                while(index!=1);
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            case 4:
                index=0;
                do
                {
                    if(index==0)
                        printf("Enter Phone number \"Only Digits\": ");

                    else
                    {
                        colorfuction(12);
                        printf("Error,Enter Phone number again \"Only Digits\": ");
                        colorfuction(15);
                    }
                    index++;
                    scanf("%s",c[x].number);
                }
                while(!phonenuumbervalidation(c[x].number));
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            case 5:
                printf("Address: ");
                getchar();
                gets(c[x].address);
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            case 6:
                index=0;
                do
                {
                    if(index==0)
                        printf("Enter Email \"Without Spaces as Example@gmail.com\" : ");

                    else
                    {
                        colorfuction(12);
                        printf("Error,Enter Email again \"Without Spaces as Example@gmail.com\": ");
                        colorfuction(15);
                    }
                    index++;
                    scanf("%s",c[x].email);
                }
                while(!Emailvalidation(c[x].email));
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            case 7:
                printf("\nEnter first name \"Without Spaces\": ");
                scanf("%s",c[x].first_name);
                printf("Enter last name \"Without Spaces\": ");
                scanf("%s",c[x].last_name);
                index=-500;
                do
                {
                    if(index==-500)
                        printf("Date of birth \"DD-MM-YYYY\": ");
                    colorfuction(12);
                    if(index==0)
                        printf("Invalid day,Enter Date of birth again \"DD-MM-YYYY\": ");
                    if(index==2)
                        printf("Invalid month,Enter Date of birth again \"DD-MM-YYYY\": ");
                    if(index==3)
                        printf("Invalid year,Enter Date of birth again \"DD-MM-YYYY\": ");
                    colorfuction(15);
                    scanf("%d-%d-%d",&c[x].date.day,&c[x].date.month,&c[x].date.year);
                    index=birthdayvalidation(c[x].date);
                }
                while(index!=1);
                printf("Address: ");
                getchar();
                gets(c[x].address);
                index=0;
                do
                {
                    if(index==0)
                        printf("Enter Phone number \"Only Digits\": ");

                    else
                    {
                        colorfuction(12);
                        printf("Error,Enter Phone number again \"Only Digits\": ");
                        colorfuction(15);
                    }
                    index++;
                    scanf("%s",c[x].number);
                }
                while(!phonenuumbervalidation(c[x].number));
                index=0;
                do
                {
                    if(index==0)
                        printf("Enter Email \"Without Spaces as Example@gmail.com\": ");

                    else
                    {
                        colorfuction(12);
                        printf("Error,Enter Email again \"Without Spaces as Example@gmail.com\": ");
                        colorfuction(15);
                    }
                    index++;
                    scanf("%s",c[x].email);
                }
                while(!Emailvalidation(c[x].email));
                colorfuction(10);
                printf("\nModifying is successfully done....\n\n");
                colorfuction(15);
                break;
            }
        }
    }
}
void Saving()
{
    char a;
    colorfuction(11);
    printf("\n\nSaving Menu:\n\n");
    colorfuction(15);
    printf("Do you want to sort it(Y/N)?\n");
    printf("Answer: ");
    scanf("%c",&a);
    if(a=='Y'||a=='y')
    {
        int x;
        colorfuction(12);
        printf("\nChoose form the following:\n");
        colorfuction(15);
        printf("1.Sorting by lastname\n2.Sorting by date of birth\n");
        printf("Your choice: ");
        scanf("%d",&x);
        if(x==1)
            SortByName();
        else if (x==2)
            SortByDOB();
    }
    FILE *f=fopen(name,"w");
    colorfuction(10);
    printf("\n\n\t\tFile is Saved........\n\n");
    colorfuction(15);
    int i;
    for(i=0; i<count; i++)
    {
        fprintf(f,"%s,",c[i].last_name);
        fprintf(f,"%s,",c[i].first_name);
        fprintf(f,"%d-%d-%d,",c[i].date.day,c[i].date.month,c[i].date.year);
        fprintf(f,"%s,",c[i].address);
        fprintf(f,"%s,",c[i].number);
        fprintf(f,"%s\n",c[i].email);
    }
    fclose(f);
}
void printing()
{
    int x,i;
    colorfuction(11);
    printf("\n\n\tPrinting Menu:\n\n");
    colorfuction(12);
    printf("Choose form the following:\n");
    colorfuction(15);
    do
    {
        printf("1.Sorting by lastname\n2.Sorting by date of birth\n");
        printf("Your choice: ");
        scanf("%d",&x);
        if(x==1)
    {
        SortByName();
        colorfuction(10);
        printf("\n\nSorting by Last name:\n\n");
    }
    else if (x==2)
        {
            SortByDOB();
            colorfuction(10);
            printf("\n\nSorting by date of birth:\n\n");
        }
    else
        {
            colorfuction(12);
            printf("\nWrong Input\n\n");
            colorfuction(15);
        }
    }while(x>2||x<1);
    colorfuction(11);
    printf("\t\tThe Telephone Book \n\n\n");
    colorfuction(15);
    for(i=0; i<count; i++)
    {
        colorfuction(12);
        printf("contact number #%d:\n",i+1);
        colorfuction(15);
        printf("First Name: %s\nLast Name: %s\n",c[i].first_name,c[i].last_name);
        printf("Date of birth: %d-%d-%d\nPhone: %s\n",c[i].date.day,c[i].date.month,c[i].date.year,c[i].number);
        printf("Address: %s\nEmail: %s\n",c[i].address,c[i].email);
        printf("\n----------------------------------\n\n");
    }
}
void Exiting()
{
    char ans;
    colorfuction(12);
    printf("\n\nAre you sure you want to exit(Y/N)?\n");
    colorfuction(15);
    printf("Your Answer: ");
    scanf("%c",&ans);
    if(ans=='Y'||ans=='y')
    {
        colorfuction(10);
        printf("\n\n\t\tThank You for Using our Application\n\n");
        colorfuction(15);
        exit(0);
    }
}
int main()
{
    colorfuction(11);
    printf("\t\tWelcome To Telephone Book\n\n");
    colorfuction(15);
    int x=0,index;
    do
    {
        if(x==0)
            printf("Please,Enter file name in format \"example.txt\"\nOR File Destination: ");
        else
        {
            colorfuction(12);
            printf("\nError please,Enter file name again in format \"example.txt\"\nOR File Destination: ");
            colorfuction(15);
        }
        x++;
        gets(name);
        index=load();
    }
    while(index!=1);
    char x_name[50],x2_name[50],ans;
    while(index==1)
    {
        colorfuction(11);
        printf("\nMain Menu:\n");
        colorfuction(12);
        printf("Please,Choose an option.\n");
        colorfuction(15);
        printf("1-Load\n");
        printf("2-Search\n");
        printf("3-Add new contact\n");
        printf("4-Deleting contact\n");
        printf("5-Modifying contact\n");
        printf("6-Saving\n");
        printf("7-Printing All contacts\n");
        printf("8-Exit\n");
        colorfuction(14);
        printf("Your choice: ");
        colorfuction(15);
        scanf("%d",&x);
        getchar();
        if(x==1)
        {
            x=0,index;
            do
            {
                if(x==0)
                    printf("Please,Enter file name in format\"example.txt\"\nOR File Destination: ");
                else
                {
                    colorfuction(12);
                    printf("\nError please,Enter file name again in format\"example.txt\"\nOR File Destination: ");
                    colorfuction(15);
                }
                x++;
                gets(name);
                index=load();
            }
            while(index!=1);
            colorfuction(10);
            printf("\n\tFile has been loaded successfully........\n");
            colorfuction(15);
        }
        else if(x==2)
        {
            colorfuction(11);
            printf("\nSearching Menu:\n");
            colorfuction(15);
            printf("Enter the Last Name \"Without Spaces\": ");
            gets(x_name);
            Quert(x_name);
        }
        else if(x==3)
            Add();
        else if(x==4)
        {
            int i,index=0;
            char answer;
            colorfuction(11);
            printf("\nDeleting Menu:\n");
            colorfuction(15);
            printf("Enter the First Name \"Without Spaces\": ");
            gets(x2_name);
            printf("Enter the Last Name \"Without Spaces\": ");
            gets(x_name);
            printf("\n\n");
            for(i=0; i<count; i++)
            {
                if(strcasecmp(c[i].last_name,x_name)==0 && strcasecmp(c[i].first_name,x2_name)==0)
                    index++;
            }
            if(index>0)
            {
                colorfuction(12);
                printf("Are you sure you want to delete all records of this Name\"%s %s\"(Y/N)?\n",x2_name,x_name);
                colorfuction(15);
                printf("Answer: ");
                scanf("%c",&answer);
                if(answer=='Y'||answer=='y')
                {
                    colorfuction(12);
                    printf("\nContact(s) has been DELETED successfully....\n\n");
                    colorfuction(15);
                    Delete(x2_name,x_name);
                }
            }
            else
            {
                colorfuction(12);
                printf("Contact not found\n\n");
                colorfuction(15);
            }
        }
        else if(x==5)
        {
            colorfuction(11);
            printf("\n\tModifying current contact\n\n");
            colorfuction(15);
            printf("Enter the Last Name \"Without Spaces\": ");
            gets(x_name);
            Modify(x_name);
        }
        else if(x==6)
            Saving();
        else if(x==7)
            printing();
        else if(x==8)
            Exiting();
        else
        {
            colorfuction(14);
            printf("\n\nI can not understand your choice.\nPlease,Try again\n\n");
            colorfuction(15);
        }
    }
    return 0;
}
