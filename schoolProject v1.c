#include <stdio.h>
#include <string.h>

#define studentSize 3

#define REG_STUDENT_SUCCESS -1
#define INVALID_REG_NUMBER -2
#define FULL_LIST -3
#define INVALID_SEX -4
#define NOT_FOUND_REG -5
#define STUDENT_UPDATE_SUCCESS -6
#define DELETED_STUDENT_SUCCESS -7
#define ERROR_DATE -8
#define VALIDATE_DATE_SUCCESS -9
#define INVALIDE_DATE -10

//Struct definition
typedef struct stu{
    int studentRegistrationNumber;
    char studentName[100];
    char studentSex;
    int day, month, year;
    char studentCPF[15];
    int active;
}student;

//Functions prototypes
int generalMenu();
int studentMenu();
int registerStudent(student studentList[], int sCount);
void listStudent(student studentList[], int sCount);
int updateStudent(student studentList[], int sCount);
int deleteStudent(student studentList[], int sCount);
int validateDate (student studentList [], int sCount);

int main(void) {
    int option = -1;
    student studentList[studentSize];
    int sCount = 0;

    printf("School Project\n");

    while(option != 0){
        option = generalMenu();

        switch(option){
            case 0:{
                printf("Exiting...\n");
                break;
            }
            
            case 1:{
                int studentOption = -1;

                while(studentOption != 0){
                    studentOption = studentMenu();

                    switch(studentOption){
                        case 0:{
                            printf("Returning to main menu...\n");
                            break;
                        }

                        case 1:{
                            int returnFunction = registerStudent(studentList, sCount);

                            switch (returnFunction){
                                case FULL_LIST:{
                                    printf("The student list is full.\n");
                                    break;
                                }

                                case INVALID_REG_NUMBER: {
                                     printf("Invalid registration number.\n");
                                     break;
                                }
                                case INVALID_SEX: {
                                    printf("Invalid sex. Try again.\n");
                                    break;
                                }
                                case INVALIDE_DATE: {
                                    printf("Invalid date. Try again.\n");
                                    break;
                                }
                                default: {
                                    printf("Successfully registration\n");
                                    sCount++;
                                    break;
                                }
                            }
                            break;
                        }

                        case 2:{
                            printf("Update student\n");
                            
                            if(sCount == 0){
                                printf("There are no students registered.\n");
                            }
                            else{
                                int returnUpdateFunction = updateStudent(studentList, sCount);
                                
                                if(returnUpdateFunction == INVALID_REG_NUMBER){
                                    printf("Invalid registration number.\n");
                                }
                                else if(returnUpdateFunction == NOT_FOUND_REG){
                                    printf("Student not found.\n");
                                }
                                else{
                                    printf("Updated student successfully.\n");
                                }
                            }
                            break;
                        }

                        case 3:{
                            printf("List student\n");
                            listStudent(studentList, sCount);
                            break;
                        }

                        case 4:{
                            printf("Delete student\n");
                            
                            if(sCount == 0){
                                printf("There are no students registered.\n");
                            }
                            else{
                                int returnDeleteFunction = deleteStudent(studentList, sCount);
                                
                                if(returnDeleteFunction == INVALID_REG_NUMBER){
                                    printf("Invalid registration number.\n");
                                }
                                else if(returnDeleteFunction == NOT_FOUND_REG){
                                    printf("Student not found.\n");
                                }
                                else{
                                    printf("Deleted student successfully.\n");
                                    sCount--;
                                }
                            }
                            break;
                        }

                        default:{
                            if(studentOption != 0){
                                printf("Invalid option. Try again.\n");
                            }
                            break;
                        }
                    }
                }
                break;
            }

            case 2:{
                printf("Professor module\n");  
                break;
            }

            case 3:{
                printf("Course module\n");  
                break;
            }

            default:{
                printf("Invalid option. Try again.\n");
                break;
            }
        }
    }
    
    return 0;
} 

int generalMenu() {
    int option;
    printf("\n=== MAIN MENU ===\n");
    printf("0 - Exit\n");
    printf("1 - Student\n");
    printf("2 - Professor\n");
    printf("3 - Course\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}

int studentMenu(){
    int option;
    printf("\n=== STUDENT MODULE ===\n"); 
    printf("0. Back\n");
    printf("1. Register student\n");
    printf("2. Update student\n");
    printf("3. List student\n");
    printf("4. Delete student\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}

int registerStudent(student studentList[], int sCount){
    int registrationNumber; 
    

    if(sCount >= studentSize){
        return FULL_LIST;
    }
    
    printf("Register student\n");
    printf("Enter the registration number: ");
    scanf("%d", &registrationNumber);
    
    while (getchar() != '\n');//Remove o \n causado pelo ENTER

    if(registrationNumber < 0){  
        return INVALID_REG_NUMBER;
    }

    printf("Enter the student full name: ");
    fgets(studentList[sCount].studentName, 100, stdin);

    printf("Sex: ");
    scanf(" %c", &studentList[sCount].studentSex);

    while (getchar() != '\n');  

    if (studentList[sCount].studentSex != 'M' && studentList[sCount].studentSex != 'm' && studentList[sCount].studentSex != 'F' && studentList[sCount].studentSex != 'f' ){
        return INVALID_SEX;
    }

    //Criar condições da data de nascimento
    printf ("Enter the birth date (DD/MM/YYYY): ");
    scanf("%d/%d/%d",&studentList[sCount].day, &studentList[sCount].month, &studentList[sCount].year);

    while (getchar () != '\n');

    // Valida a data imediatamente após ler
    int dateResult = validateDate(studentList, sCount);
    if(dateResult == INVALIDE_DATE){
        return INVALIDE_DATE;
    }

    printf("Enter the CPF (123.456.789-10): ");
    fgets(studentList[sCount].studentCPF, 15, stdin);

    studentList[sCount].studentRegistrationNumber = registrationNumber;  
    studentList[sCount].studentName[strcspn(studentList[sCount].studentName, "\n")] = '\0';
    studentList[sCount].studentCPF[strcspn(studentList[sCount].studentCPF, "\n")] = '\0';
    studentList[sCount].active = 1;
    
    return REG_STUDENT_SUCCESS;
}

void listStudent(student studentList[], int countStudent) {
    if (countStudent == 0) {
        printf("There are no students registered.\n");
    }
    else {
        for (int i=0;i<studentSize;i++){
            printf("Registered students.\n");
            if (studentList[i].active==1){
                    printf("%d: %d\n", i+1,studentList[i].studentRegistrationNumber);
            }
        }  
    }    
}

int updateStudent(student studentList[], int sCount){
    int found = 0;
    int registrationNumber;
    
    printf("Enter the registration number: ");
    scanf("%d", &registrationNumber);
    
    if(registrationNumber < 0){
        return INVALID_REG_NUMBER;
    }
    
    for(int i = 0; i < sCount; i++){
        if(registrationNumber == studentList[i].studentRegistrationNumber && studentList[i].active == 1){
            int newRegistrationNumber;
            printf("Enter the new registration number: ");
            scanf("%d", &newRegistrationNumber);

            if(newRegistrationNumber < 0){
                printf("Invalid new registration number.\n");
                return INVALID_REG_NUMBER;
            }
            
            studentList[i].studentRegistrationNumber = newRegistrationNumber;
            found = 1;
            break;
        }
    }
    
    if(found)
        return STUDENT_UPDATE_SUCCESS;
    else 
        return NOT_FOUND_REG;
}

int deleteStudent(student studentList[], int sCount){
    int registrationNumber;
    int found = 0;
    
    printf("Enter the registration number: ");
    scanf("%d", &registrationNumber);
    
    if(registrationNumber < 0){
        return INVALID_REG_NUMBER;
    }
    
    for(int i = 0; i < sCount; i++){
        if(registrationNumber == studentList[i].studentRegistrationNumber && studentList[i].active == 1){
            studentList[i].active = 0;
            found = 1;
            
            // Shift elements to fill the gap
            for(int j = i; j < sCount - 1; j++){
                studentList[j] = studentList[j + 1];
            }
            break;
        }
    }
    
    if(found)
        return DELETED_STUDENT_SUCCESS;
    else 
        return NOT_FOUND_REG;
}

int validateDate(student studentList[], int sCount) {
    if (studentList[sCount].month > 0 && studentList[sCount].month < 13) {
        if (studentList[sCount].month == 4 || studentList[sCount].month == 6 || studentList[sCount].month == 9 || studentList[sCount].month == 11) {
            if (studentList[sCount].day > 0 && studentList[sCount].day < 31) {
                return VALIDATE_DATE_SUCCESS;
            }
            else {
                return INVALIDE_DATE;
            }
        }
        else if (studentList[sCount].month == 2) {
            if (studentList[sCount].day > 0 && studentList[sCount].day <= 29) {
                if (studentList[sCount].day == 29) {
                    if ((studentList[sCount].year % 4 == 0 && studentList[sCount].year % 100 != 0) || studentList[sCount].year % 400 == 0) {
                        return VALIDATE_DATE_SUCCESS;
                    }
                    else {
                        return INVALIDE_DATE;
                    }
                }
                else if (studentList[sCount].day >= 1 && studentList[sCount].day <= 28) {
                    return VALIDATE_DATE_SUCCESS;
                }
                else {
                    return INVALIDE_DATE;
                }
            }
            else {
                return INVALIDE_DATE;
            }
        }
        else if (studentList[sCount].day > 0 && studentList[sCount].day < 32) {
            return VALIDATE_DATE_SUCCESS;
        }
        else {
            return INVALIDE_DATE;
        }
    }
    else {
        return INVALIDE_DATE;
    }
}