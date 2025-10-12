//Precisa refatorar as funções dos módulos de estudante, professor e disciplina.
//Criar geração de relatórios em listas por módulos.
//Adicionar no módulo de atualização do estudante e do professor as opções de atualizar CPF, NOME e SEXO.
//Necessário validar CPF e validar os números de matrícula e CPF (não podem se repetir).

#include <stdio.h>
#include <string.h>

#define studentSize 3
#define professorSize 3

//Constantes de retorno.
#define REG_SUCCESS -1
#define INVALID_REG_NUMBER -2
#define FULL_LIST -3
#define INVALID_SEX -4
#define NOT_FOUND_REG -5
#define UPDATE_SUCCESS -6
#define DELETED_SUCCESS -7
#define ERROR_DATE -8
#define VALIDATE_DATE_SUCCESS -9
#define INVALID_DATE -10

//Struct definition
typedef struct stu{
    int studentRegistrationNumber;
    char studentName[100];
    char studentSex;
    int day, month, year;
    char studentCPF[15];
    int active;
}student;

typedef struct prof{
    int professorRegistrationNumber;
    char professorName[100];
    char professorSex;
    int day, month, year;
    char professorCPF[15];
    int active;
}professor;

//Functions prototypes
int generalMenu();
int studentMenu();
int professorMenu();
int registerStudent(student studentList[], int sCount);
int registerprofessor(professor professorList[], int sCount);
void listStudent(student studentList[], int sCount);
void listprofessor(professor professorList[], int countprofessor);
int updateStudent(student studentList[], int sCount);
int updateprofessor(professor professorList[], int sCount);
int deleteStudent(student studentList[], int sCount);
int deleteProfessor(professor professorList[], int sCount);
int validate_St_Date (student studentList [], int sCount);
int validate_Prof_Date (professor professorList[], int sCount);
int validateStCPF(student studentList[], int sCount);

int main(void) {
    int option = -1;
    student studentList[studentSize];
    professor professorList[professorSize];
    int sCount = 0;
    int pCount = 0;

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
                                case INVALID_DATE: {
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
                int professorOption = -1;

                while(professorOption != 0){
                    professorOption = professorMenu();

                    switch(professorOption){
                        case 0:{
                            printf("Returning to main menu...\n");
                            break;
                        }

                        case 1:{
                            int returnFunction = registerprofessor(professorList, pCount);

                            switch (returnFunction){
                                case FULL_LIST:{
                                    printf("The professor list is full.\n");
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
                                case INVALID_DATE: {
                                    printf("Invalid date. Try again.\n");
                                    break;
                                }
                                default: {
                                    printf("Successfully registration\n");
                                    pCount++;
                                    break;
                                }
                            }
                            break;
                        }

                        case 2:{
                            printf("Update professor\n");
                            
                            if(pCount == 0){
                                printf("There are no professors registered.\n");
                            }
                            else{
                                int returnUpdateFunction = updateprofessor(professorList, pCount);
                                
                                if(returnUpdateFunction == INVALID_REG_NUMBER){
                                    printf("Invalid registration number.\n");
                                }
                                else if(returnUpdateFunction == NOT_FOUND_REG){
                                    printf("professor not found.\n");
                                }
                                else{
                                    printf("Updated professor successfully.\n");
                                }
                            }
                            break;
                        }
                        
                        case 3:{
                            printf("List professor: \n");
                            listprofessor(professorList, pCount);
                            break;
                        }

                        case 4:{
                            printf("Delete professor\n");
                            
                            if(pCount == 0){
                                printf("There are no professor registered.\n");
                            }
                            else{
                                int returnDeleteFunction = deleteProfessor(professorList, pCount);
                                
                                if(returnDeleteFunction == INVALID_REG_NUMBER){
                                    printf("Invalid registration number.\n");
                                }
                                else if(returnDeleteFunction == NOT_FOUND_REG) {
                                    printf("professor not found.\n");
                                }
                                else{
                                    printf("Deleted professor successfully.\n");
                                    pCount--;
                                }
                            }
                            break;
                        }

                        default:{
                            if(professorOption != 0){
                                printf("Invalid option. Try again.\n");
                            }
                            break;
                        }
                    }
                }
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


    
    printf ("Enter the birth date (DD/MM/YYYY): ");
    scanf("%d/%d/%d",&studentList[sCount].day, &studentList[sCount].month, &studentList[sCount].year);

    while (getchar () != '\n');

    int dateResult = validate_St_Date(studentList, sCount);
    if(dateResult == INVALID_DATE){
        return INVALID_DATE;
    }

    printf("Enter the CPF (123.456.789-10): ");
    fgets(studentList[sCount].studentCPF, 15, stdin);

    studentList[sCount].studentRegistrationNumber = registrationNumber;  
    studentList[sCount].studentName[strcspn(studentList[sCount].studentName, "\n")] = '\0';
    studentList[sCount].studentCPF[strcspn(studentList[sCount].studentCPF, "\n")] = '\0';
    studentList[sCount].active = 1;
    
    return REG_SUCCESS;
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
        return UPDATE_SUCCESS;
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
        return DELETED_SUCCESS;
    else 
        return NOT_FOUND_REG;
}

int validate_St_Date(student studentList[], int sCount) {
    int day = studentList[sCount].day;
    int month = studentList[sCount].month;
    int year=studentList[sCount].year;

    if (year>=1950 && year <=2022) {
        if (month > 0 && month < 13) {
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                if (day > 0 && day < 31) {
                    return VALIDATE_DATE_SUCCESS;
                }
                else {
                    return INVALID_DATE;
                }
            }
            else if (month == 2) {
                if (day > 0 && day <= 29) {
                    if (day == 29) {
                        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                            return VALIDATE_DATE_SUCCESS;
                        }
                        else {
                            return INVALID_DATE;
                        }
                    }
                    else if (day >= 1 && day <= 28) {
                        return VALIDATE_DATE_SUCCESS;
                    }
                    else {
                        return INVALID_DATE;
                    }
                }
                else {
                    return INVALID_DATE;
                }
            }
            else if (day > 0 && day < 32) {
                return VALIDATE_DATE_SUCCESS;
            }
            else {
                return INVALID_DATE;
            }
        }
        else {
            return INVALID_DATE;
        }
    }
    else {
        return INVALID_DATE;
    }
}

/*int validateStCPF(student studentList[], int sCount){

}*/

int professorMenu(){
    int option;
    printf("\n=== PROFESSOR MODULE ===\n"); 
    printf("0. Back\n");
    printf("1. Register professor\n");
    printf("2. Update professor\n");
    printf("3. List professor\n");
    printf("4. Delete professor\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}

int registerprofessor(professor professorList[], int sCount){
    int registrationNumber; 
    

    if(sCount >= professorSize){
        return FULL_LIST;
    }
    
    printf("Register professor\n");
    printf("Enter the registration number: ");
    scanf("%d", &registrationNumber);
    
    while (getchar() != '\n');//Remove o \n causado pelo ENTER

    if(registrationNumber < 0){  
        return INVALID_REG_NUMBER;
    }

    printf("Enter the professor full name: ");
    fgets(professorList[sCount].professorName, 100, stdin);

    printf("Sex: ");
    scanf(" %c", &professorList[sCount].professorSex);

    while (getchar() != '\n');  

    if (professorList[sCount].professorSex != 'M' && professorList[sCount].professorSex != 'm' && professorList[sCount].professorSex != 'F' && professorList[sCount].professorSex != 'f' ){
        return INVALID_SEX;
    }

    printf ("Enter the birth date (DD/MM/YYYY): ");
    scanf("%d/%d/%d",&professorList[sCount].day, &professorList[sCount].month, &professorList[sCount].year);

    while (getchar () != '\n');

    int dateResult = validate_Prof_Date(professorList, sCount);
    if(dateResult == INVALID_DATE){
        return INVALID_DATE;
    }

    printf("Enter the CPF (123.456.789-10): ");
    fgets(professorList[sCount].professorCPF, 15, stdin);

    professorList[sCount].professorRegistrationNumber = registrationNumber;  
    professorList[sCount].professorName[strcspn(professorList[sCount].professorName, "\n")] = '\0';
    professorList[sCount].professorCPF[strcspn(professorList[sCount].professorCPF, "\n")] = '\0';
    professorList[sCount].active = 1;
    
    return REG_SUCCESS;
}

int updateprofessor(professor professorList[], int sCount){
    int found = 0;
    int registrationNumber;
    
    printf("Enter the registration number: ");
    scanf("%d", &registrationNumber);
    
    if(registrationNumber < 0){
        return INVALID_REG_NUMBER;
    }
    
    for(int i = 0; i < sCount; i++){
        if(registrationNumber == professorList[i].professorRegistrationNumber && professorList[i].active == 1){
            int newRegistrationNumber;
            printf("Enter the new registration number: ");
            scanf("%d", &newRegistrationNumber);

            if(newRegistrationNumber < 0){
                printf("Invalid new registration number.\n");
                return INVALID_REG_NUMBER;
            }
            
            professorList[i].professorRegistrationNumber = newRegistrationNumber;
            found = 1;
            break;
        }
    }
    
    if(found)
        return UPDATE_SUCCESS;
    else 
        return NOT_FOUND_REG;
}

void listprofessor(professor professorList[], int countprofessor) {
    if (countprofessor == 0) {
        printf("There are no professors registered.\n");
    }
    else {
        for (int i=0;i<professorSize;i++){
            printf("Registered professors.\n");
            if (professorList[i].active==1){
                    printf("%d: %d\n", i+1,professorList[i].professorRegistrationNumber);
            }
        }  
    }    
}

int deleteProfessor(professor professorList[], int sCount){
    int registrationNumber;
    int found = 0;
    
    printf("Enter the registration number: ");
    scanf("%d", &registrationNumber);
    
    if(registrationNumber < 0){
        return INVALID_REG_NUMBER;
    }
    
    for(int i = 0; i < sCount; i++){
        if(registrationNumber == professorList[i].professorRegistrationNumber && professorList[i].active == 1){
            professorList[i].active = 0;
            found = 1;
            
            // Shift elements to fill the gap
            for(int j = i; j < sCount - 1; j++){
                professorList[j] = professorList[j + 1];
            }
            break;
        }
    }
    
    if(found)
        return DELETED_SUCCESS;
    else 
        return NOT_FOUND_REG;
}

int validate_Prof_Date(professor professorList[], int sCount) {
    int day = professorList[sCount].day;
    int month = professorList[sCount].month;
    int year=professorList[sCount].year;

    if (year>=1950 && year <=2022) {
        if (month > 0 && month < 13) {
            if (month == 4 || month == 6 || month == 9 || month == 11) {
                if (day > 0 && day < 31) {
                    return VALIDATE_DATE_SUCCESS;
                }
                else {
                    return INVALID_DATE;
                }
            }
            else if (month == 2) {
                if (day > 0 && day <= 29) {
                    if (day == 29) {
                        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                            return VALIDATE_DATE_SUCCESS;
                        }
                        else {
                            return INVALID_DATE;
                        }
                    }
                    else if (day >= 1 && day <= 28) {
                        return VALIDATE_DATE_SUCCESS;
                    }
                    else {
                        return INVALID_DATE;
                    }
                }
                else {
                    return INVALID_DATE;
                }
            }
            else if (day > 0 && day < 32) {
                return VALIDATE_DATE_SUCCESS;
            }
            else {
                return INVALID_DATE;
            }
        }
        else {
            return INVALID_DATE;
        }
    }
    else {
        return INVALID_DATE;
    }
}
