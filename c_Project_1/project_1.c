#include <stdio.h>
#include"C:\Users\kissh\Desktop\ManFree\Embedded C\Project\project_1code.c"
void main()
{
    int value;
    printf("Enter the number\n");
    printf("1 Register\n");
    printf("2 Login\n");
    printf("3 exit\n");
    scanf("%d",&value);

    switch (value)
    {
        case 1:
        registor();
        break;

        case 2:
        login();

        break;

        case 3:
        exit(0);

        default:
        printf("Invalid choice\n");
    }
}
