#include <stdio.h>


#define studentSize 3

#define REG_STUDENT_SUCCESS -1
#define INVALID_REG_NUMBER -2
#define FULL_LIST -3

//Struct definition
typedef struct stu{
    int studentRegistrationNumber;
    char studentName[100];
    char studentSex;
    char studentDOB[11];
    int studentCPF[15];
    int active;
}student;

//Functions prototypes
int generalMenu();
int studentMenu ();
int registerStudent (student studentList[], int countStudent);
void listStudent (student studentList[], int countStudent);

int main (void) {

        int option=-1, countOption=0;
        student studentList[studentSize];
        int countStudent = 0;

        printf("School Project\n");

        while(option != 0){
            generalMenu();
            option=generalMenu();

            switch (option) { 
                
            case 1:{
                int studentOption=-1;

                while(studentOption!=0){
                    studentOption=studentMenu();

                    int registrationNumber; //Verificar a criação da variável com mesmo nome da que está na função
                    int found=0;

                    switch (studentOption) {

                        case 1: {
                            //Ajustar bug de repetição do menu
                            int returnFunction = registerStudent(studentList, countStudent);
                            
                            if (returnFunction==FULL_LIST){
                                printf("The student list is full.");
                            }
                            if(returnFunction==INVALID_REG_NUMBER){
                                printf("Invalid registration number.");
                            }
                            else {
                                printf("Successfully registration");//Ajustar bug de mensagem repetida mesmo quando a lista está cheia.
                                countStudent++;
                            }
                            break;
                        }
                        case 2:{
                            printf("Update student\n");
                            printf("Enter the registration number: ");
                            scanf("%d", &registrationNumber);
                            if (registrationNumber<0){
                                printf("There are no student registered.");
                            }
                            else {
                                for (int i=0;i<countStudent;i++){
                                    if (registrationNumber==studentList[i].studentRegistrationNumber && studentList[i].active){
                                            studentList[i].studentRegistrationNumber = studentList[i+1].studentRegistrationNumber;
                                            //studentList[j].studentSex = studentList[j+1].studentSex;
                                            //studentList[j].active = studentList[j+1].active;
                                            int newRegistrationNumber;
                                            printf("Enter the new registration number: ");
                                            scanf("%d", &newRegistrationNumber);

                                            if (newRegistrationNumber<0){
                                                printf("Invalid new registration number.");
                                            }
                                            else {
                                                studentList[i].studentRegistrationNumber=newRegistrationNumber;
                                            }
                                            found=1;
                                            break;
                                    }
                                }
                                if (found)
                                    printf("Updated student successfully.");
                                else 
                                    printf("Student not found.");
                            }
                            break;
                        }

                        case 3:{
                            printf("List student\n");

                            listStudent(studentList, countStudent);
                            break;
                        }
                        case 4:{
                            printf("Delete student\n");
                            printf("Enter the registration number: ");
                            scanf("%d", &registrationNumber);
                            if (registrationNumber<0){
                                printf("There are no student registered.");
                            }
                            else {
                                for (int i=0;i<countStudent;i++){
                                    printf("Registered students.\n");
                                    if (registrationNumber==studentList[i].studentRegistrationNumber){
                                        studentList[i].active=-1;
                                        found=1;
                                        for (int j=i;j<countStudent;j++){
                                            studentList[j].studentRegistrationNumber = studentList[j+1].studentRegistrationNumber;
                                            studentList[j].studentSex = studentList[j+1].studentSex;
                                            studentList[j].active = studentList[j+1].active;
                                        }
                                        countStudent--;
                                        break;
                                    }
                                }
                                if (found)
                                    printf("Deleted student successfully.");
                                else 
                                    printf("Student not found.");
                            }
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
        countOption++;
    }
} 

int generalMenu () {
    int option;
    printf("0 - Exit\n");
    printf("1 - Student\n");
    printf("2 - Professor\n");
    printf("3 - Course\n");
    scanf("%d", &option);

    return option;
}

int studentMenu () {
    int option;
    printf ("\nStudent module\n"); 
    printf("0. Back\n");
    printf("1. Register student\n");
    printf("2. Update student\n");
    printf("3. List student\n");
    printf("4. Delete student\n");
    scanf("%d", &option);

    return option;
}

int registerStudent(student studentList[], int countStudent){

    int registrationNumber; 

    if (countStudent >= studentSize){
        return FULL_LIST;
    } 
    else {
        printf("Register student\n");
        printf("Enter the registration number: \n");
        scanf("%d", &registrationNumber);  
            if (registrationNumber<0){  
                return INVALID_REG_NUMBER;
            }
            else {
            studentList[countStudent].studentRegistrationNumber=registrationNumber;  
            studentList[countStudent].active=1;
                
            return REG_STUDENT_SUCCESS;
            }
        }
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

