#include <stdio.h>


#define studentSize 3

int main (void) {

    int option;
    int studentList[studentSize];
    int countStudent = 0;

    printf("School Project\n");

    while(option != 0){
        printf("0 - Exit\n");
        printf("1 - Student\n");
        printf("2 - Professor\n");
        printf("3 - Course\n");
        scanf("%d", &option);

        switch (option) { 
            
        case 1:{
            int studentOption;

            while(studentOption!=0){
                printf ("Student module\n"); 
                printf("0. Back\n");
                printf("1. Register student\n");
                printf("2. Update student\n");
                printf("3. List student\n");
                printf("4. Delete student\n");
                scanf("%d", &studentOption);

                switch (studentOption) {

                    case 1: {
                        printf("Register student\n");
                        printf("Enter the registration number: \n");
                        int studentRegistrationNumber=0;
                        scanf("%d", &studentRegistrationNumber);
                            if (studentRegistrationNumber<0){
                                printf("Invalid registration number.\n");
                                scanf("%d", &studentRegistrationNumber);
                            }
                            else {
                                if (countStudent == studentSize){
                                    printf("The student list is full.");
                                }
                                else {
                                    studentList[countStudent];
                                    countStudent++;
                                }
                            }
                        break;
                    }
                    case 2: {
                        printf("Update student\n");
                        break;
                    }

                    case 3: {
                        printf("List student\n");
                        break;
                    }
                    case 4: {
                        printf("Delete student\n");
                        break;
                    }
                }

            }
            break;
        }

        case 2:{
            printf ("Professor module\n");  
            break;
        }

        case 3: {
            printf ("Course module\n");  
            break;
        }
        default: {
            printf ("Invalid option. Try again.\n");
            break;
        }
    }
 }

    return 0;
}