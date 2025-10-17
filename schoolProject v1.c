//Criar geração de relatórios em listas por módulos.

#include <stdio.h>
#include <string.h>

#define studentSize 3
#define professorSize 3
#define courseSize 3

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
#define FOUND -11
#define ALREADY_REGISTERED -12

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

typedef struct course {
    int code;
    char courseName[100];
    int professorRegistration; 
    int semester;
    int insertStudent[100];
    int studentCount;
    int active;
} course;

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
int courseMenu();
int registerCourse(course courseList[], int cCount, professor professorList[], int count);
int findProfessor(professor professorList[], int count, int professorRegistration);
int updateCourse(course courseList[], professor professorList[], int sCount, int cCount);
int findStudent(student studentList[], int sCount, int studentRegistration);
int insertStudent(course courseList[], student studentList[], int sCount, int cCount);
int deleteCourse (student studentList[], course courseList[], int sCount, int cCount);

int main(void) {
    int option = -1;
    student studentList[studentSize];
    professor professorList[professorSize];
    course courseList[courseSize];
    int sCount = 0;
    int pCount = 0;
    int cCount = 0;

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
                
                int courseOption = -1;

                while(courseOption != 0){
                    courseOption = courseMenu();

                    switch(courseOption){
                        case 0:{
                            printf("Returning to main menu...\n");
                            break;
                        }

                        case 1:{
                            int returnValue = registerCourse(courseList, cCount, professorList, pCount);

                            switch (returnValue){
                                case FULL_LIST:{
                                    printf("The course list is full.\n");
                                    break;
                                }

                                case INVALID_REG_NUMBER: {
                                     printf("Invalid registration number.\n");
                                     break;
                                }
                                case INVALID_DATE: {
                                    printf("Invalid semester. Try again.\n");
                                    break;
                                }
                                case NOT_FOUND_REG: {
                                    printf("There are no professor registered. Try again.\n");
                                    break;
                                }
                                default: {
                                    printf("Successfully registration\n");
                                    cCount++;
                                    break;
                                }
                            }
                            break;
                        }

                        case 2: {

                            int returnUpdate = updateCourse(courseList, professorList, pCount, cCount);
                            switch (returnUpdate) {
                                
                                case INVALID_REG_NUMBER: {
                                    printf("Invalid registration number. Try again.\n");
                                    break;
                                }
                                case NOT_FOUND_REG: {
                                    printf("There are no registration number. Try again.\n");
                                    break;
                                } 
                                case INVALID_DATE:{
                                    printf("Invalid semester. Try again.\n");
                                    break;
                                }
                                default: {
                                    printf("Updated professor success.\n");
                                    break;
                                }

                            }
                            break;
                        }
                        case 3: {
                            int returnInsert = insertStudent(courseList, studentList, sCount, cCount);

                            switch (returnInsert){
                                
                                case INVALID_REG_NUMBER: {
                                    printf("There are no course code registered.\n");
                                    break;
                                }
                                case NOT_FOUND_REG:{
                                    printf("Invalid reg number. Try again.\n");
                                    break;
                                }
                                case ALREADY_REGISTERED:{
                                    printf("Student already registered.\n");
                                    break;
                                }
                                case FULL_LIST:{
                                    printf("The list is already full.\n");
                                    break;
                                } 
                                default:{
                                    printf("Student successfully placed.\n");
                                    break;
                                }
                            }
                            break;
                        }
                        case 4:{
                            int deleteResult = deleteCourse(studentList, courseList, sCount, cCount);

                            if(deleteResult == DELETED_SUCCESS){
                                cCount--;
                                printf("Course count updated.\n");
                            }
                            break;
                        }

                        default:{
                            if(courseOption != 0){
                                printf("Invalid option. Try again.\n");
                            }
                            break;
                        }
                    }
                }
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
    
    while (getchar() != '\n');

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
            int updateOption = -1;
            
            while(updateOption != 0){
                printf("\n=== UPDATE STUDENT MENU ===\n");
                printf("0. Back\n");
                printf("1. Update registration number\n");
                printf("2. Update name\n");
                printf("3. Update sex\n");
                printf("4. Update CPF\n");
                printf("Choose an option: ");
                scanf("%d", &updateOption);
                
                switch(updateOption){
                    case 0:{
                        printf("Returning to main menu...\n");
                        break;
                    }
                    case 1:{
                        int newRegistrationNumber;
                        printf("Enter the new registration number: ");
                        scanf("%d", &newRegistrationNumber);

                        if(newRegistrationNumber < 0){
                            printf("Invalid new registration number.\n");
                            break;
                        }
                        
                        int isDuplicate = 0;
                        for(int j = 0; j < sCount; j++){
                            if(j != i && studentList[j].studentRegistrationNumber == newRegistrationNumber && studentList[j].active == 1){
                                printf("Registration number already exists.\n");
                                isDuplicate = 1;
                                break;
                            }
                        }
                        
                        if(!isDuplicate){
                            studentList[i].studentRegistrationNumber = newRegistrationNumber;
                            printf("Registration number updated successfully!\n");
                        }
                        break;
                    }
                    case 2:{
                        while(getchar() != '\n');
                        printf("Enter the new name: ");
                        fgets(studentList[i].studentName, 100, stdin);
                        studentList[i].studentName[strcspn(studentList[i].studentName, "\n")] = '\0';
                        printf("Name updated successfully!\n");
                        break;
                    }
                    case 3:{
                        char newSex;
                        printf("Enter the new sex (M/F): ");
                        scanf(" %c", &newSex);
                        
                        if(newSex != 'M' && newSex != 'm' && newSex != 'F' && newSex != 'f'){
                            printf("Invalid sex!\n");
                        } else {
                            studentList[i].studentSex = newSex;
                            printf("Sex updated successfully!\n");
                        }
                        break;
                    }
                    case 4:{
                        while(getchar() != '\n');
                        char newCPF[15];
                        printf("Enter the new CPF (123.456.789-10): ");
                        fgets(newCPF, 15, stdin);
                        newCPF[strcspn(newCPF, "\n")] = '\0';
                        
                        int isDuplicate = 0;
                        for(int j = 0; j < sCount; j++){
                            if(j != i && strcmp(studentList[j].studentCPF, newCPF) == 0 && studentList[j].active == 1){
                                printf("CPF already registered!\n");
                                isDuplicate = 1;
                                break;
                            }
                        }
                        
                        if(!isDuplicate){
                            strcpy(studentList[i].studentCPF, newCPF);
                            printf("CPF updated successfully!\n");
                        }
                        break;
                    }
                    default:{
                        if(updateOption != 0){
                            printf("Invalid option. Try again.\n");
                        }
                        break;
                    }
                }
            }
            
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

int courseMenu(){
    int option;
    printf("\n=== COURSE MODULE ===\n"); 
    printf("0. Back\n");
    printf("1. Register course\n");
    printf("2. Update\n");
    printf("3. Insert student\n");
    printf("4. Delete\n");
    printf("5. List\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}

int registerCourse(course courseList[], int cCount, professor professorList[], int count) {
    int courseCode;
    char courseName[100];
    int courseSemester;
    int professorRegistration;

    if (cCount >= courseSize) {
        return FULL_LIST;
    }

    printf("Register course\n");
    printf("Enter the course code: ");
    scanf("%d", &courseCode);
    while (getchar() != '\n');

    if (courseCode < 0) return INVALID_REG_NUMBER;

    printf("Enter the course name: ");
    fgets(courseName, 100, stdin);

    printf("Enter the course semester: ");
    scanf("%d", &courseSemester);
    while (getchar() != '\n');

    if (courseSemester < 1 || courseSemester > 8) return INVALID_DATE;

    printf("Enter the professor registration: ");
    scanf("%d", &professorRegistration);
    while (getchar() != '\n');

    int validateProf = findProfessor(professorList, count, professorRegistration);
    if (validateProf == NOT_FOUND_REG) return NOT_FOUND_REG;

    courseList[cCount].code = courseCode;
    strcpy(courseList[cCount].courseName, courseName);
    courseList[cCount].semester = courseSemester;
    courseList[cCount].professorRegistration = professorRegistration;
    courseList[cCount].studentCount = 0;
    courseList[cCount].active = 1;

    courseList[cCount].courseName[strcspn(courseList[cCount].courseName, "\n")] = '\0';

    return REG_SUCCESS;
}

int updateCourse(course courseList[], professor professorList[], int sCount, int cCount) {
    int courseCode;
    
    printf("Enter the course code: ");
    scanf("%d", &courseCode);
    
    if(courseCode < 0) 
        return INVALID_REG_NUMBER;
    
    for (int i = 0; i < cCount; i++){
        if (courseCode == courseList[i].code){
            
            int newCode;
            char newName[100];
            int newProfessor;
            int newSemester;

            printf("Enter new code: ");
            scanf("%d", &newCode);

            if (newCode<0){
                return INVALID_REG_NUMBER;
            }
            while (getchar() != '\n');

            printf("Enter new name: ");
            fgets(newName, 100,stdin);
            newName[strcspn(newName, "\n")] = '\0';

            printf("Enter new semester: ");
            scanf("%d", &newSemester);
            
            if (newSemester<1 || newSemester > 8){
                return INVALID_DATE;
            }
            printf("Current professor registration: %d\n", courseList[i].professorRegistration);
            printf("Enter the new professor registration: ");
            scanf("%d", &newProfessor);
            
            if(newProfessor< 0) 
                return INVALID_REG_NUMBER;
            int validateProf = findProfessor(professorList, sCount, newProfessor);
            if(validateProf == NOT_FOUND_REG){
                return NOT_FOUND_REG; 
            }
            courseList[i].code = newCode;
            strcpy(courseList[i].courseName, newName);
            courseList[i].semester = newSemester;
            courseList[i].professorRegistration = newProfessor;
            
            return UPDATE_SUCCESS;
        }
    }
    
    return NOT_FOUND_REG;
}

int findProfessor(professor professorList[], int count, int professorRegistration) {
    for (int i = 0; i < count; i++) {
        if (professorList[i].professorRegistrationNumber == professorRegistration && professorList[i].active == 1) {
            return FOUND;
        }
    }
    return NOT_FOUND_REG;
}

int findStudent(student studentList[], int sCount, int studentRegistration) {
    for (int i = 0; i < sCount; i++) {
        if (studentList[i].studentRegistrationNumber == studentRegistration && studentList[i].active == 1) {
            return FOUND;
        }
    }
    return NOT_FOUND_REG;
}

int insertStudent(course courseList[], student studentList[], int sCount, int cCount){
    int courseCode;
    int studentReg;
    int maxStudents;
    
    printf("Enter the course code: ");
    scanf("%d", &courseCode);
    
    if (courseCode < 0){
        return INVALID_REG_NUMBER;
    }
    
    int courseIndex = -1;
    for (int i = 0; i < cCount; i++){
        if (courseList[i].code == courseCode){
            courseIndex = i;
            break;
        }
    }
    
    if (courseIndex == -1)
        return NOT_FOUND_REG;
    
    printf("How many students do you want to register? ");
    scanf("%d", &maxStudents);
    
    if (maxStudents < 0){
        return INVALID_REG_NUMBER;
    }
    
    for (int count = 0; count < maxStudents; count++){
        printf("Enter student registration [%d/%d]: ", count + 1, maxStudents);
        scanf("%d", &studentReg);
        
        if (studentReg <= 0){
            return INVALID_REG_NUMBER;
        }
        
        int validateStu = findStudent(studentList, sCount, studentReg);
        if (validateStu == NOT_FOUND_REG){
            printf("Student not found! Try again.\n");
            count--; 
            continue;
        }
        
        int isDuplicate = 0;
        for (int i = 0; i < courseList[courseIndex].studentCount; i++){
            if (courseList[courseIndex].insertStudent[i] == studentReg){
                printf("Student already registered! Try again.\n");
                isDuplicate = 1;
                break;
            }
        }
        
        if (isDuplicate){
            count--;
            continue;
        }
        
        if (courseList[courseIndex].studentCount >= 50){
            printf("Course is full!\n");
            return FULL_LIST;
        }
        
        int index = courseList[courseIndex].studentCount;
        courseList[courseIndex].insertStudent[index] = studentReg;
        courseList[courseIndex].studentCount++;
    }
    
    return REG_SUCCESS;
}

int deleteCourse(student studentList[], course courseList[], int sCount, int cCount){

    int deleteOption = -1;

    while(deleteOption != 0){
        printf("\n====DELETE MODULE====\n");
        printf("0. Back\n");
        printf("1. Delete course\n");
        printf("2. Delete student\n");
        printf("Choose an option: ");
        scanf("%d", &deleteOption);
        
        switch(deleteOption){

            case 0:{
                printf("Returning to course menu...\n");
                break;
            }
            case 1: {
                int courseCode;
                int found = 0;

                printf("Enter the course code: ");
                scanf("%d", &courseCode);

                if(courseCode < 0){
                    printf("Invalid code. Try again.\n");
                    break;
                }
                    
                for(int i = 0; i < cCount; i++){
                    if(courseCode == courseList[i].code && courseList[i].active == 1){
                        courseList[i].active = 0;
                        found = 1;
                        
                        for(int j = i; j < cCount - 1; j++){
                            courseList[j] = courseList[j + 1];
                        }
                        break;
                    }
                }

                if(found){
                    printf("Deleted course successfully.\n");
                    return DELETED_SUCCESS;
                }
                else{
                    printf("Course not found. Try again.\n");
                }
                break;
            }
            case 2: {
                int courseCode;
                int studentReg;
                int found = 0;

                printf("Enter the course code: ");
                scanf("%d", &courseCode);

                if(courseCode < 0){
                    printf("Invalid code. Try again.\n");
                    break;
                }

                int courseIndex = -1;
                for(int i = 0; i < cCount; i++){
                    if(courseCode == courseList[i].code && courseList[i].active == 1){
                        courseIndex = i;
                        break;
                    }
                }

                if(courseIndex == -1){
                    printf("Course not found.\n");
                    break;
                }

                
                if(courseList[courseIndex].studentCount == 0){
                    printf("No students enrolled in this course.\n");
                    break;
                }

                
                printf("\n=== Students enrolled in this course ===\n");
                for(int i = 0; i < courseList[courseIndex].studentCount; i++){
                    int studentReg = courseList[courseIndex].insertStudent[i];
                    
                    for(int j = 0; j < sCount; j++){
                        if(studentList[j].studentRegistrationNumber == studentReg && studentList[j].active == 1){
                            printf("%d. Registration: %d - Name: %s\n", 
                                i+1, studentReg, studentList[j].studentName);
                            break;
                        }
                    }
                }

                printf("\nEnter student registration to remove: ");
                scanf("%d", &studentReg);

                if(studentReg <= 0){
                    printf("Invalid registration.\n");
                    break;
                }

                for(int i = 0; i < courseList[courseIndex].studentCount; i++){
                    if(courseList[courseIndex].insertStudent[i] == studentReg){
                        found = 1;
                        
                        for(int j = i; j < courseList[courseIndex].studentCount - 1; j++){
                            courseList[courseIndex].insertStudent[j] = courseList[courseIndex].insertStudent[j + 1];
                        }
                        
                        courseList[courseIndex].studentCount--;
                        printf("Student removed from course successfully.\n");
                        break;
                    }
                }

                if(!found){
                    printf("Student not found in this course.\n");
                }

                break;
            }
            default:{
                if(deleteOption != 0){
                    printf("Invalid option. Try again.\n");
                }
                break;
            }
        }
    }
    
    return 0;
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
    
    while (getchar() != '\n');

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
            int updateOption = -1;
            
            while(updateOption != 0){
                printf("\n=== UPDATE PROFESSOR MENU ===\n");
                printf("0. Back\n");
                printf("1. Update registration number\n");
                printf("2. Update name\n");
                printf("3. Update sex\n");
                printf("4. Update CPF\n");
                printf("Choose an option: ");
                scanf("%d", &updateOption);
                
                switch(updateOption){
                    case 0:{
                        printf("Returning...\n");
                        break;
                    }
                    case 1:{
                        int newRegistrationNumber;
                        printf("Enter the new registration number: ");
                        scanf("%d", &newRegistrationNumber);

                        if(newRegistrationNumber < 0){
                            printf("Invalid new registration number.\n");
                            break;
                        }
                        
                        // Verifica duplicata
                        int isDuplicate = 0;
                        for(int j = 0; j < sCount; j++){
                            if(j != i && professorList[j].professorRegistrationNumber == newRegistrationNumber && professorList[j].active == 1){
                                printf("Registration number already exists!\n");
                                isDuplicate = 1;
                                break;
                            }
                        }
                        
                        if(!isDuplicate){
                            professorList[i].professorRegistrationNumber = newRegistrationNumber;
                            printf("Registration number updated successfully!\n");
                        }
                        break;
                    }
                    case 2:{
                        while(getchar() != '\n');
                        printf("Enter the new name: ");
                        fgets(professorList[i].professorName, 100, stdin);
                        professorList[i].professorName[strcspn(professorList[i].professorName, "\n")] = '\0';
                        printf("Name updated successfully!\n");
                        break;
                    }
                    case 3:{
                        char newSex;
                        printf("Enter the new sex (M/F): ");
                        scanf(" %c", &newSex);
                        
                        if(newSex != 'M' && newSex != 'm' && newSex != 'F' && newSex != 'f'){
                            printf("Invalid sex!\n");
                        } else {
                            professorList[i].professorSex = newSex;
                            printf("Sex updated successfully!\n");
                        }
                        break;
                    }
                    case 4:{
                        while(getchar() != '\n');
                        char newCPF[15];
                        printf("Enter the new CPF (123.456.789-10): ");
                        fgets(newCPF, 15, stdin);
                        newCPF[strcspn(newCPF, "\n")] = '\0';
                        
                        // Verifica duplicata de CPF
                        int isDuplicate = 0;
                        for(int j = 0; j < sCount; j++){
                            if(j != i && strcmp(professorList[j].professorCPF, newCPF) == 0 && professorList[j].active == 1){
                                printf("CPF already registered!\n");
                                isDuplicate = 1;
                                break;
                            }
                        }
                        
                        if(!isDuplicate){
                            strcpy(professorList[i].professorCPF, newCPF);
                            printf("CPF updated successfully!\n");
                        }
                        break;
                    }
                    default:{
                        if(updateOption != 0){
                            printf("Invalid option. Try again.\n");
                        }
                        break;
                    }
                }
            }
            
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

int deleteProfessor(professor professorList[], int sCount) {
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
            
            for(int j = i; j < sCount - 1; j++){
                professorList[j] = professorList[j + 1];
            }
            break;
        }
    }
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

int courseMenu(){
    int option;
    printf("\n=== COURSE MODULE ===\n"); 
    printf("0. Back\n");
    printf("1. Register course\n");
    printf("2. Update\n");
    printf("3. Insert student\n");
    printf("4. Delete\n");
    printf("5. List\n");
    printf("Choose an option: ");
    scanf("%d", &option);

    return option;
}

int registerCourse(course courseList[], int cCount, professor professorList[], int count) {
    int courseCode;
    char courseName[100];
    int courseSemester;
    int professorRegistration;

    if (cCount >= courseSize) {
        return FULL_LIST;
    }

    printf("Register course\n");
    printf("Enter the course code: ");
    scanf("%d", &courseCode);
    while (getchar() != '\n');

    if (courseCode < 0) return INVALID_REG_NUMBER;

    printf("Enter the course name: ");
    fgets(courseName, 100, stdin);

    printf("Enter the course semester: ");
    scanf("%d", &courseSemester);
    while (getchar() != '\n');

    if (courseSemester < 1 || courseSemester > 8) return INVALID_DATE;

    printf("Enter the professor registration: ");
    scanf("%d", &professorRegistration);
    while (getchar() != '\n');

    int validateProf = findProfessor(professorList, count, professorRegistration);
    if (validateProf == NOT_FOUND_REG) return NOT_FOUND_REG;

    courseList[cCount].code = courseCode;
    strcpy(courseList[cCount].courseName, courseName);
    courseList[cCount].semester = courseSemester;
    courseList[cCount].professorRegistration = professorRegistration;
    courseList[cCount].studentCount = 0;
    courseList[cCount].active = 1;

    courseList[cCount].courseName[strcspn(courseList[cCount].courseName, "\n")] = '\0';

    return REG_SUCCESS;
}

int updateCourse(course courseList[], professor professorList[], int sCount, int cCount) {
    int courseCode;
    
    printf("Enter the course code: ");
    scanf("%d", &courseCode);
    
    if(courseCode < 0) 
        return INVALID_REG_NUMBER;
    
    for (int i = 0; i < cCount; i++){
        if (courseCode == courseList[i].code){
            
            int newCode;
            char newName[100];
            int newProfessor;
            int newSemester;

            printf("Enter new code: ");
            scanf("%d", &newCode);

            if (newCode<0){
                return INVALID_REG_NUMBER;
            }
            while (getchar() != '\n');

            printf("Enter new name: ");
            fgets(newName, 100,stdin);
            newName[strcspn(newName, "\n")] = '\0';

            printf("Enter new semester: ");
            scanf("%d", &newSemester);
            
            if (newSemester<1 || newSemester > 8){
                return INVALID_DATE;
            }
            printf("Current professor registration: %d\n", courseList[i].professorRegistration);
            printf("Enter the new professor registration: ");
            scanf("%d", &newProfessor);
            
            if(newProfessor< 0) 
                return INVALID_REG_NUMBER;
            int validateProf = findProfessor(professorList, sCount, newProfessor);
            if(validateProf == NOT_FOUND_REG){
                return NOT_FOUND_REG; 
            }
            courseList[i].code = newCode;
            strcpy(courseList[i].courseName, newName);
            courseList[i].semester = newSemester;
            courseList[i].professorRegistration = newProfessor;
            
            return UPDATE_SUCCESS;
        }
    }
    
    return NOT_FOUND_REG;
}

int findProfessor(professor professorList[], int count, int professorRegistration) {
    for (int i = 0; i < count; i++) {
        if (professorList[i].professorRegistrationNumber == professorRegistration && professorList[i].active == 1) {
            return FOUND;
        }
    }
    return NOT_FOUND_REG;
}

int findStudent(student studentList[], int sCount, int studentRegistration) {
    for (int i = 0; i < sCount; i++) {
        if (studentList[i].studentRegistrationNumber == studentRegistration && studentList[i].active == 1) {
            return FOUND;
        }
    }
    return NOT_FOUND_REG;
}

int insertStudent(course courseList[], student studentList[], int sCount, int cCount){
    int courseCode;
    int studentReg;
    int maxStudents;
    
    printf("Enter the course code: ");
    scanf("%d", &courseCode);
    
    if (courseCode < 0){
        return INVALID_REG_NUMBER;
    }
    
    int courseIndex = -1;
    for (int i = 0; i < cCount; i++){
        if (courseList[i].code == courseCode){
            courseIndex = i;
            break;
        }
    }
    
    if (courseIndex == -1)
        return NOT_FOUND_REG;
    
    printf("How many students do you want to register? ");
    scanf("%d", &maxStudents);
    
    if (maxStudents < 0){
        return INVALID_REG_NUMBER;
    }
    
    for (int count = 0; count < maxStudents; count++){
        printf("Enter student registration [%d/%d]: ", count + 1, maxStudents);
        scanf("%d", &studentReg);
        
        if (studentReg <= 0){
            return INVALID_REG_NUMBER;
        }
        
        int validateStu = findStudent(studentList, sCount, studentReg);
        if (validateStu == NOT_FOUND_REG){
            printf("Student not found! Try again.\n");
            count--; 
            continue;
        }
        
        int isDuplicate = 0;
        for (int i = 0; i < courseList[courseIndex].studentCount; i++){
            if (courseList[courseIndex].insertStudent[i] == studentReg){
                printf("Student already registered! Try again.\n");
                isDuplicate = 1;
                break;
            }
        }
        
        if (isDuplicate){
            count--;
            continue;
        }
        
        if (courseList[courseIndex].studentCount >= 50){
            printf("Course is full!\n");
            return FULL_LIST;
        }
        
        int index = courseList[courseIndex].studentCount;
        courseList[courseIndex].insertStudent[index] = studentReg;
        courseList[courseIndex].studentCount++;
    }
    
    return REG_SUCCESS;
}

int deleteCourse(student studentList[], course courseList[], int sCount, int cCount){

    int deleteOption = -1;

    while(deleteOption != 0){
        printf("\n====DELETE MODULE====\n");
        printf("0. Back\n");
        printf("1. Delete course\n");
        printf("2. Delete student\n");
        printf("Choose an option: ");
        scanf("%d", &deleteOption);
        
        switch(deleteOption){

            case 0:{
                printf("Returning to course menu...\n");
                break;
            }
            case 1: {
                int courseCode;
                int found = 0;

                printf("Enter the course code: ");
                scanf("%d", &courseCode);

                if(courseCode < 0){
                    printf("Invalid code. Try again.\n");
                    break;
                }
                    
                for(int i = 0; i < cCount; i++){
                    if(courseCode == courseList[i].code && courseList[i].active == 1){
                        courseList[i].active = 0;
                        found = 1;
                        
                        for(int j = i; j < cCount - 1; j++){
                            courseList[j] = courseList[j + 1];
                        }
                        break;
                    }
                }

                if(found){
                    printf("Deleted course successfully.\n");
                    return DELETED_SUCCESS;
                }
                else{
                    printf("Course not found. Try again.\n");
                }
                break;
            }
            case 2: {
                int courseCode;
                int studentReg;
                int found = 0;

                printf("Enter the course code: ");
                scanf("%d", &courseCode);

                if(courseCode < 0){
                    printf("Invalid code. Try again.\n");
                    break;
                }

                int courseIndex = -1;
                for(int i = 0; i < cCount; i++){
                    if(courseCode == courseList[i].code && courseList[i].active == 1){
                        courseIndex = i;
                        break;
                    }
                }

                if(courseIndex == -1){
                    printf("Course not found.\n");
                    break;
                }

                
                if(courseList[courseIndex].studentCount == 0){
                    printf("No students enrolled in this course.\n");
                    break;
                }

                
                printf("\n=== Students enrolled in this course ===\n");
                for(int i = 0; i < courseList[courseIndex].studentCount; i++){
                    int studentReg = courseList[courseIndex].insertStudent[i];
                    
                    for(int j = 0; j < sCount; j++){
                        if(studentList[j].studentRegistrationNumber == studentReg && studentList[j].active == 1){
                            printf("%d. Registration: %d - Name: %s\n", 
                                i+1, studentReg, studentList[j].studentName);
                            break;
                        }
                    }
                }

                printf("\nEnter student registration to remove: ");
                scanf("%d", &studentReg);

                if(studentReg <= 0){
                    printf("Invalid registration.\n");
                    break;
                }

                for(int i = 0; i < courseList[courseIndex].studentCount; i++){
                    if(courseList[courseIndex].insertStudent[i] == studentReg){
                        found = 1;
                        
                        for(int j = i; j < courseList[courseIndex].studentCount - 1; j++){
                            courseList[courseIndex].insertStudent[j] = courseList[courseIndex].insertStudent[j + 1];
                        }
                        
                        courseList[courseIndex].studentCount--;
                        printf("Student removed from course successfully.\n");
                        break;
                    }
                }

                if(!found){
                    printf("Student not found in this course.\n");
                }

                break;
            }
            default:{
                if(deleteOption != 0){
                    printf("Invalid option. Try again.\n");
                }
                break;
            }
        }
    }
    
    return 0;
}