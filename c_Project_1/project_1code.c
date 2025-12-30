#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int get_pass;
struct details p1;
char get_Uname[25];
int registor();
struct details
{
    int Reg;
    char Name[25];
    int DOB;
    char Gender[5];
    long long int Account_Num;
    char Mail[25];
    long long int Phone_Num;
    char User_name[25];
    int Password;
};

int file_handling(struct details *ptr)
{
    FILE *fptr = fopen("data.txt", "a");
    if (fptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }
    fprintf(fptr, "Reg: %d\n", ptr->Reg);
    fprintf(fptr, "Name: %s\n", ptr->Name);
    fprintf(fptr, "DOB: %d\n", ptr->DOB);
    fprintf(fptr, "Gender: %s\n", ptr->Gender);
    fprintf(fptr, "Account: %lld\n", ptr->Account_Num);
    fprintf(fptr, "Mail: %s\n", ptr->Mail);
    fprintf(fptr, "Phone: %lld\n", ptr->Phone_Num);
    fprintf(fptr, "Username: %s\n", ptr->User_name);
    fprintf(fptr, "Password: %d\n", ptr->Password);

    fclose(fptr);
}
int display(struct details *ptr)
{
    FILE *fptr = fopen("data.txt", "r");
    if (fptr == NULL)
    {
        printf("Error! opening file");
        exit(1);
    }

    printf("Reg: %d\n", ptr->Reg);
    printf("Name: %s\n", ptr->Name);
    printf("DOB: %d\n", ptr->DOB);
    printf("Gender: %s\n", ptr->Gender);
    printf("Account: %d\n", ptr->Account_Num);
    printf("Mail: %s\n", ptr->Mail);
    printf("Phone: %d\n", ptr->Phone_Num);
    printf("Username: %s\n", ptr->User_name);
    printf("Password: %d\n", ptr->Password);

}

int isString(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        char c = str[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')))
        {
            return 0;
        }
    }
    return 1;
}

int registor()
{
    do
    {
        printf("Enter Reg_num (11 to 99): ");
        scanf("%d", &p1.Reg);

        if (p1.Reg <= 10 || p1.Reg > 100)
            printf("\nInvalid! Enter number between 11 and 99.\n");

    } while (p1.Reg <= 10 || p1.Reg > 100);

    do
    {
        printf("Enter Name: ");
        scanf("%s", p1.Name);

        if (!isString(p1.Name))
            printf("\nInvalid! Enter name only with alphabets\n");

    } while (!isString(p1.Name));

    do
    {
        printf("Enter DOB (DDMMYYYY): ");
        scanf("%d", &p1.DOB);

        if(p1.DOB <= 1011950 || p1.DOB > 30122026)
        {
            printf("\nInvalid! Enter date correct formate\n");
        }

    } while (p1.DOB <= 1011950 || p1.DOB > 30122026) ;

    do
    {
        printf("Enter Gender: ");
        scanf("%s", p1.Gender);

        if (!strcmp(p1.Gender , "Male") && !strcmp(p1.Gender , "Female") && !strcmp(p1.Gender , "Others"))
            printf("\nInvalid! Enter Gender only Male , Female , Others\n");

    }while (!strcmp(p1.Gender , "Male") && !strcmp(p1.Gender , "Female") && !strcmp(p1.Gender , "Others"));

    do
    {
        printf("Enter Account Number: ");
        scanf("%lld", &p1.Account_Num);

        if(p1.Account_Num <= 11111111111 || p1.Account_Num > 99999999999)
            printf("\nInvalid! Enter account number correct formate\n");
        if(!p1.Account_Num < 0 || !p1.Account_Num > 9)
          printf("\nInvalid! Enter account number only in Number\n");

    } while (p1.Account_Num <= 11111111111 || p1.Account_Num > 99999999999) ;

    do
    {
        printf("Enter EMail: ");
        scanf("%s",p1.Mail);

        if(!strchr(p1.Mail, '@') && !strchr(p1.Mail, '.'))
            printf("\nInvalid! Enter email correct formate\n");
    }while (!strchr(p1.Mail, '@') && !strchr(p1.Mail, '.'));

    do
    {
        printf("Enter Phone Number: ");
        scanf("%lld", &p1.Phone_Num);

        if(p1.Phone_Num <= 8000000000 || p1.Phone_Num > 9999999999)
            printf("\nInvalid! Enter number correct formate\n");
        if(!p1.Phone_Num < 0 || !p1.Phone_Num > 9)
            printf("\nInvalid! Enter number only \n");
    } while (p1.Phone_Num <= 8000000000 || p1.Phone_Num > 9999999999) ;

    do
    {
        printf("Enter Username: ");
        scanf("%s", p1.User_name);

        if (!isString(p1.User_name)&&(!strchr(p1.User_name, '_')))
            printf("\nInvalid! Enter name only with alphabets\n");

    } while (!isString(p1.User_name)&&(!strchr(p1.User_name, '_')));

     do
    {
        printf("Enter Password: ");
        scanf("%d", &p1.Password);

        if(p1.Password <= 1000 || p1.Password > 9999)
            printf("\nInvalid! Enter number correct formate\n");
        if(!p1.Password < 0 || !p1.Password > 9)
            printf("\nInvalid! Enter number only \n");
    } while (p1.Password <= 1000 || p1.Password > 9999);

    char again;

    do
    {
        file_handling(&p1);
        display(&p1);
        printf("\nAre the details correct? (Y/N): ");
        scanf(" %c", &again);

    } while (again == 'N' || again == 'n');
        printf("Data saved successfully into data.txt\n");
        login();
}

int login()
{
    FILE *fptr = fopen("data.txt", "r");
    if (fptr == NULL)
    {
        printf("Error! No user registered yet.\n");
        return 0;
    }

    char label[30];

    fscanf(fptr, "%s %d\n", label, &p1.Reg);
    fscanf(fptr, "%s %s\n", label, p1.Name);
    fscanf(fptr, "%s %d\n", label, &p1.DOB);
    fscanf(fptr, "%s %s\n", label, p1.Gender);
    fscanf(fptr, "%s %lld\n", label, &p1.Account_Num);
    fscanf(fptr, "%s %s\n", label, p1.Mail);
    fscanf(fptr, "%s %lld\n", label, &p1.Phone_Num);
    fscanf(fptr, "%s %s\n", label, p1.User_name);
    fscanf(fptr, "%s %d\n", label, &p1.Password);

    fclose(fptr);

    printf("Enter Username: ");
    scanf("%s", get_Uname);
    printf("Enter Password: ");
    scanf("%d", &get_pass);

    if (strcmp(get_Uname, p1.User_name) == 0 && get_pass == p1.Password)
    {
        printf("Welcome %s!\n", p1.Name);
        payment();
    }
    else
    {
        printf("Invalid Username or Password\n");
    }

    return 1;
}

int payment()
{
    int def_amount = 2000;
    int new_amount;
    int option;
    printf("Enter the number\n");
    printf("1 View Member’s Information\n");
    printf("2 Deposit Amount\n");
    printf("3 Withdraw Amount\n");
    printf("4 exit\n");
    scanf("%d",&option);
    switch (option)
    {
        case 1:
        display(&p1);
        break;

        case 2:
            printf("Enter Amount to deposit\n");
            scanf("%d",&new_amount);
            new_amount = def_amount + new_amount;
            printf("Your Balance Amount %d\n",new_amount);
        break;

        case 3:
            printf("Enter Amount to Withdraw \n");
            scanf("%d",&new_amount);
            new_amount = def_amount - new_amount;
            printf("Your Balance Amount %d\n",new_amount);
        break;

        case 4:
        login();

        default:
        printf("Invalid choice\n");
    }
}
