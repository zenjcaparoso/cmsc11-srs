#include<stdio.h>
#include<dirent.h>
#include<malloc.h>

struct subject{
    int SubjectID;
    char SubjectCode[20];
    char SubjectTitle[50];
};

struct student{
    int StudentID;
    char FirstName[50];
    char LastName[50];
    char CMSC11Section[10];
    int HandsOnExams[3];
    struct subject *enrolled[3];
    int Total;
    char Grade[5];
};

struct statistics{
    int Lowest[4];
    int Highest[4];
    double Average[4];
    double StdDeviation[4];
};

struct student CMSC11[1000] = {0};
struct subject Units[100] = {11, "CMSC11", "Introduction to Computer Science"};
struct subject Empty = {0, "None", "None"};
struct statistics Data;

void StudentRecord(struct student *CMSC11, struct subject *Units);
void CreateStudentRecord(struct student *CMSC11);
void ReadFromFileStudent(struct student *CMSC11, char a[], struct subject *Units);
void CreateNewStudent(struct student *CMSC11, struct subject *Units, struct subject *Empty);
void StudentEnrollment(struct student *CMSC11, int index);
void SearchStudentRecord(struct student *CMSC11);
void SearchStudentID(struct student *CMSC11);
void SearchStudentLastName(struct student *CMSC11);
void EditStudentRecord(struct student *CMSC11, int index);
void DropSubject(struct student *CMSC11, int index);
void DisplayStudentSearchedRecord(struct student *CMSC11, int index);
void DeleteStudentRecord(struct student *CMSC11, int index);
void DisplayStudentRecord(struct student *CMSC11, struct subject *Units);
void StatisticsRecord(struct student *CMSC11, struct statistics *Data);
void ClearStudentRecord(struct student *CMSC11);
void ExportStudentRecord(struct student *CMSC11, struct statistics *Data);

void SubjectRecord(struct subject *Units);
void CreateSubjectRecord(struct subject *Units);
void ReadFromFileSubject(struct subject *Units, char a[]);
void CreateNewSubject(struct subject *Units);
void SearchSubjectRecord(struct subject *Units);
void SearchSubjectID(struct subject *Units);
void SearchSubjectCode(struct subject *Units);
void EditSubjectRecord(struct subject *Units, int index);
void DeleteSubjectRecord(struct subject *Units, int index);
void DisplaySubjectSearchedRecord(struct subject *Units, int index);
void DisplaySubjectRecord(struct subject *Units);
void ClearSubjectRecord(struct subject *Units);
void ExportSubjectRecord(struct subject *Units);

void ReadAllRecords(struct student *CMSC11, struct subject *Units);
void ExportAllRecords(struct student *CMSC11, struct subject *Units);

int Strcspn(char a[], char b[]);
int ToInteger(char st[]);
int Strcmp(char s1[], char s2[]);
int Substring(char s1[], char s2[]);

char ToLower(char ch);
char ToUpper(char ch);

void Strcat(char s1[], char s2[]);
void Strcpy(char src[], char dest[]);

double Sqrt(double number);

int main(void){
    int page1 = 1;
    while (page1 > 0){
        printf("\n\nWELCOME TO THE UP DEPARTMENT OF COMPUTER SCIENCE DATABASE\n\n");
        printf("Active Directories:\n");
        printf("\t1. Student Record\n\t2. Subject Record\n\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page1);
        fflush(stdin);
        switch (page1){
        case 1:
            StudentRecord(CMSC11, Units);
            break;
        
        case 2:
            SubjectRecord(Units);
            break;

        default:
            page1 = 0;
            /* Prompt "Save Changes?" */
            break;
        }
    }
    
    return 0;
};

void StudentRecord(struct student *CMSC11, struct subject *Units){
    int page2_1 = 1;
    while(page2_1 > 0){
        printf("\n\nDEPARTMENT OF COMPUTER SCIENCE: STUDENT RECORD\n\n");
        printf("Active Commands:\n");
        printf("\t1. Create a New Student Record\n");
        printf("\t2. Search and Update/Delete an Existing Student Record\n");
        printf("\t3. Display Student Record\n");
        printf("\t4. Clear Student Record\n");
        printf("\t5. Save and Export\n\t6. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page2_1);
        fflush(stdin);
        switch (page2_1){
        case 1:
            CreateStudentRecord(CMSC11);
            break;
        
        case 2:
            SearchStudentRecord(CMSC11);
            break;

        case 3:
            DisplayStudentRecord(CMSC11, Units);
            break;
        
        case 4:
            ClearStudentRecord(CMSC11);
            break;
        
        case 5:
            ExportStudentRecord(CMSC11, &Data);
            break;

        default:
            page2_1 = 0;
            /* Prompt "Student Record Terminated" */
            break;
        }
    }
};

void SubjectRecord(struct subject *Units){
    int page2_2 = 1;
    while(page2_2 > 0){
        printf("\n\nDEPARTMENT OF COMPUTER SCIENCE: SUBJECT RECORD\n\n");
        printf("Active Commands:\n");
        printf("\t1. Create a New Subject Record\n");
        printf("\t2. Search and Update/Delete an Existing Subject Record\n");
        printf("\t3. Display Subject Record\n");
        printf("\t4. Clear Student Record\n");
        printf("\t5. Save and Export\n\t6. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page2_2);
        fflush(stdin);
        switch (page2_2){
        case 1:
            CreateSubjectRecord(Units);
            break;
        
        case 2:
            SearchSubjectRecord(Units);
            break;

        case 3:
            DisplaySubjectRecord(Units);
            break;
        
        case 4:
            ClearSubjectRecord(Units);
            break;
        
        case 5:
            ExportSubjectRecord(Units);
            break;

        default:
            page2_2 = 0;
            /* Prompt "Subject Record Terminated" */
            break;
        }
    }
};

void ReadAllRecords(struct student *CMSC11, struct subject *Units){
    int index, index2;
    char directory[400];
    printf("\n\nREADING FROM DIRECTORY\n\n");
    printf("Please enter directory: ");
    fgets(directory, 400 , stdin);
    fflush(stdin);
    directory[Strcspn(directory, "\n")] = 0;
    for(index = 0; index < 400; index++){
        if(directory[index] == 92){
            directory[index] = 47;
        }
    }
    DIR *folder = opendir(directory);
    struct dirent *location;
    int fileCount = 0;
    if (folder == NULL){
        printf("\nUnable to read given directory\n");
    }else{
        printf("\nSuccessfully read the directory!\n");
    }
    while((location = readdir(folder)) != NULL){
        fileCount++;
    }
    closedir(folder);
    folder = opendir(directory);
    char filepath[fileCount][150];
    index = 0;
    while((location = readdir(folder)) != NULL){
        Strcpy(directory, filepath[index]);
        Strcat(filepath[index], "/");
        Strcat(filepath[index], location->d_name);
        printf("Filepath: %s\n", filepath[index]);
        index++;
    }
    closedir(folder);
};

void ExportAllRecords(struct student *CMSC11, struct subject *Units){

};

void CreateStudentRecord(struct student *CMSC11){
    int page3_1 = 1;
    char directory[100];
    printf("\n\nCREATING A NEW STUDENT RECORD\n\n");
    printf("Active Commands:\n");
    printf("\t1. Read from File\t2. Create Student Record\t3. Exit\n\n");
    printf("Select: ");
    scanf("%d", &page3_1);
    fflush(stdin);
    switch (page3_1){
    case 1:
        printf("\n\nREADING FROM FILE\n\n");
        printf("[Note: Use /] Please enter the directory of the file: ");
        fgets(directory, 100, stdin);
        fflush(stdin);
        directory[Strcspn(directory, "\n")] = 0;
        ReadFromFileStudent(CMSC11, directory, Units);
        break;
    
    case 2:
        CreateNewStudent(CMSC11, Units, &Empty);
        break;

    default:
        printf("\n\nYou left Create Student Record Page.\n\n");
        page3_1 = 0;
        break;
    }
};

void ReadFromFileStudent(struct student *CMSC11, char a[], struct subject *Units){
    FILE *dataset = fopen(a, "r");
    char data[10], data1[3][10], data2[3][10], tempID[2], tempTitle[100];
    int index, index2, index3, index4, error = 0, page3_2, line = 1;
    struct student temp;
    while (!feof(dataset)){
        printf("\n\nReading filepath[%s]: Line %d\n\n", a, line);
        for (index = 0; CMSC11[index].StudentID != 0; index++);
        fscanf(dataset, "\n%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", &data, &CMSC11[index].FirstName, &CMSC11[index].LastName, &CMSC11[index].CMSC11Section, &data1[0], &data1[1], &data1[2], &data2[0], &data2[1], &data2[2]);
        for (index2 = 0; index2 < 1000; index2++){
            if (CMSC11[index2].StudentID == ToInteger(data)){
                error = 1;
            }
        }
        if (error == 0){
            CMSC11[index].StudentID = ToInteger(data);
            error = 0;
        }else{
            printf("Basic Information:\n\n");
            printf("\tStudent ID: %d\n\tStudent First Name: %s\n\tStudent Last Name: %s\n\tStudent CMSC11 Section: %s\n\n", ToInteger(data), CMSC11[index].FirstName, CMSC11[index].LastName, CMSC11[index].CMSC11Section);
            printf("ID %d already taken, would you like to input a new ID?\n", ToInteger(data));
            printf("\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2);
            fflush(stdin);
            switch (page3_2){
            case 1:
                do{
                    printf("Enter New Student ID: ");
                    scanf("%d", &page3_2);
                    fflush(stdin);
                    for (index2 = 0; CMSC11[index2].StudentID != page3_2 && index2 < 1000; index2++);
                    if (index2 == 1000){
                        CMSC11[index].StudentID = page3_2;
                        printf("\n\nStudent ID successfully changed.\n\n");
                        error = 0;
                    }else{
                        printf("\n\nID already taken.\n\n");
                    }
                } while (error == 1);
                break;
            
            default:
                CMSC11[index].StudentID = 0;
                error = 1;
                printf("\n\nStudent Info discarded.\n\n");
                break;
            }
        }
        if (error == 0){
            for (index2 = 0; Units[index2].SubjectID != 0; index2++){
                if (Strcmp(data2[0], Units[index2].SubjectCode) != 0){
                    error = 1;
                }
                if (Strcmp(data2[0], Empty.SubjectCode) == 0){
                    error = 0;
                    break;
                }
                if (Strcmp(data2[0], Units[index2].SubjectCode) == 0){
                    error = 0;
                    break;
                }
            }
            if (error == 1){
                for (index2 = 0; Units[index2].SubjectID != 0; index2++);
                Strcpy(data2[0], Units[index2].SubjectCode);
                for (index3 = 0; ((data2[0][index3] > 64 && data2[0][index3] < 91) || (data2[0][index3] > 96 && data2[0][index3] < 123)) && index3 < 20; index3++);
                tempID[0] = data2[0][index3];
                tempID[1] = data2[0][index3+1];
                for (index3 = 0; Units[index3].SubjectID != 0; index3++){
                    if (ToInteger(tempID) == Units[index3].SubjectID){
                        error = 1;
                        break;
                    }else{
                        error = 0;
                    }
                }
                Units[index2].SubjectID = ToInteger(tempID);
                Strcpy("None",Units[index2].SubjectTitle);
                Units[index2].SubjectTitle[4] = '\0';
                printf("\n\nSubject %s with ID %d automatically added onto database.\n\n", Units[index2].SubjectCode, Units[index2].SubjectID);
                DisplaySubjectSearchedRecord(Units, index2);
                if (error == 1){
                    do{
                        printf("\n\nID already taken\n\n");
                        printf("Enter New Subject ID: ");
                        scanf("%d", &page3_2);
                        fflush(stdin);
                        for (index3 = 0; index3 < index2; index3++){
                            if (page3_2 != Units[index3].SubjectID){
                            error = 0;
                            }
                        }
                    } while (error == 1);
                    Units[index2].SubjectID = page3_2;
                }
                printf("\n\nPlease enter the Subject Title: ");
                fgets(Units[index2].SubjectTitle, 50, stdin);
                Units[index2].SubjectTitle[Strcspn(Units[index2].SubjectTitle, "\n")] = 0;
                fflush(stdin);
                Strcpy("",tempID);
            }
            error = 0;
            for (index2 = 0; Units[index2].SubjectID != 0; index2++){
                if (Strcmp(data2[1], Units[index2].SubjectCode) != 0){
                    error = 1;
                }
                if (Strcmp(data2[1], Empty.SubjectCode) == 0){
                    error = 0;
                    break;
                }
                if (Strcmp(data2[1], Units[index2].SubjectCode) == 0){
                    error = 0;
                    break;
                }                           
            }
            if (error == 1){
                for (index2 = 0; Units[index2].SubjectID != 0; index2++);
                Strcpy(data2[1], Units[index2].SubjectCode);
                for (index3 = 0; ((data2[1][index3] > 64 && data2[1][index3] < 91) || (data2[1][index3] > 96 && data2[1][index3] < 123)) && index3 < 20; index3++);
                tempID[0] = data2[1][index3];
                tempID[1] = data2[1][index3+1];
                for (index3 = 0; Units[index3].SubjectID != 0; index3++){
                    if (ToInteger(tempID) == Units[index3].SubjectID){
                        error = 1;
                        break;
                    }else{
                        error = 0;
                    }
                }
                Units[index2].SubjectID = ToInteger(tempID);
                Strcpy("None",Units[index2].SubjectTitle);
                Units[index2].SubjectTitle[4] = '\0';
                printf("\n\nSubject %s with ID %d automatically added onto database.\n\n", Units[index2].SubjectCode, Units[index2].SubjectID);
                DisplaySubjectSearchedRecord(Units, index2);
                if (error == 1){
                    do{
                        printf("\n\nID already taken\n\n");
                        printf("Enter New Subject ID: ");
                        scanf("%d", &page3_2);
                        fflush(stdin);
                        for (index3 = 0; index3 < index2; index3++){
                            if (page3_2 != Units[index3].SubjectID){
                            error = 0;
                            }
                        }
                    } while (error == 1);
                    Units[index2].SubjectID = page3_2;
                }
                printf("\n\nPlease enter the Subject Title: ");
                fgets(Units[index2].SubjectTitle, 50, stdin);
                Units[index2].SubjectTitle[Strcspn(Units[index2].SubjectTitle, "\n")] = 0;
                fflush(stdin);
                Strcpy("",tempID);
            }            
            error = 0;
            for (index2 = 0; Units[index2].SubjectID != 0; index2++){
                if (Strcmp(data2[2], Units[index2].SubjectCode) != 0){
                    error = 1;
                }
                if (Strcmp(data2[2], Empty.SubjectCode) == 0){
                    error = 0;
                    break;
                }
                if (Strcmp(data2[2], Units[index2].SubjectCode) == 0){
                    error = 0;
                    break;
                }                
            }
            if (error == 1){
                for (index2 = 0; Units[index2].SubjectID != 0; index2++);
                Strcpy(data2[2], Units[index2].SubjectCode);
                for (index3 = 0; ((data2[2][index3] > 64 && data2[2][index3] < 91) || (data2[2][index3] > 96 && data2[2][index3] < 123)) && index3 < 20; index3++);
                tempID[0] = data2[2][index3];
                tempID[1] = data2[2][index3+1];
                for (index3 = 0; Units[index3].SubjectID != 0; index3++){
                    if (ToInteger(tempID) == Units[index3].SubjectID){
                        error = 1;
                        break;
                    }else{
                        error = 0;
                    }
                }
                Units[index2].SubjectID = ToInteger(tempID);
                Strcpy("None",Units[index2].SubjectTitle);
                Units[index2].SubjectTitle[4] = '\0';
                printf("\n\nSubject %s with ID %d automatically added onto database.\n\n", Units[index2].SubjectCode, Units[index2].SubjectID);
                DisplaySubjectSearchedRecord(Units, index2);
                if (error == 1){
                    do{
                        printf("\n\nID already taken\n\n");
                        printf("Enter New Subject ID: ");
                        scanf("%d", &page3_2);
                        fflush(stdin);
                        for (index3 = 0; index3 < index2; index3++){
                            if (page3_2 != Units[index3].SubjectID){
                            error = 0;
                            }
                        }
                    } while (error == 1);
                    Units[index2].SubjectID = page3_2;
                }
                printf("\n\nPlease enter the Subject Title: ");
                fgets(Units[index2].SubjectTitle, 50, stdin);
                Units[index2].SubjectTitle[Strcspn(Units[index2].SubjectTitle, "\n")] = 0;
                fflush(stdin);
                Strcpy("",tempID);
            }
            CMSC11[index].HandsOnExams[0] = ToInteger(data1[0]);
            CMSC11[index].HandsOnExams[1] = ToInteger(data1[1]);
            CMSC11[index].HandsOnExams[2] = ToInteger(data1[2]);
            for (index2 = 0; Units[index2].SubjectID != 0; index2++){
                if (Strcmp(data2[0], Units[index2].SubjectCode) == 0){
                    CMSC11[index].enrolled[0] = &Units[index2];
                }
                if (Strcmp(data2[1], Units[index2].SubjectCode) == 0 && CMSC11[index].enrolled[0] != &Units[index2]){
                    CMSC11[index].enrolled[1] = &Units[index2];
                }else{
                    CMSC11[index].enrolled[1] = &Empty;
                }
                if (Strcmp(data2[2], Units[index2].SubjectCode) == 0 && CMSC11[index].enrolled[0] != &Units[index2] && CMSC11[index].enrolled[1] != &Units[index2]){
                    CMSC11[index].enrolled[2] = &Units[index2];
                }else{
                    CMSC11[index].enrolled[2] = &Empty;
                }
            }
            if (CMSC11[index].enrolled[0] != &Units[0] && CMSC11[index].enrolled[1] != &Units[0] && CMSC11[index].enrolled[2] != &Units[0]){
                printf("\n\nFirst Enrolled Subject %s was overwritten to %s for it must be a default subject\n\n", CMSC11[index].enrolled[0]->SubjectCode,Units[0].SubjectCode);
                CMSC11[index].enrolled[0] = &Units[0];
            }
            CMSC11[index].Total = CMSC11[index].HandsOnExams[0] + CMSC11[index].HandsOnExams[1] + CMSC11[index].HandsOnExams[2];
            if (CMSC11[index].Total >= 135){
                Strcpy("HD", CMSC11[index].Grade);
            }else if (CMSC11[index].Total >= 120 && CMSC11[index].Total < 135){
                Strcpy("D", CMSC11[index].Grade);
            }else if (CMSC11[index].Total >= 100 && CMSC11[index].Total < 120){
                Strcpy("P", CMSC11[index].Grade);
            }else if (CMSC11[index].Total >= 75 && CMSC11[index].Total < 100){
                Strcpy("C", CMSC11[index].Grade);
            }else{
                Strcpy("F", CMSC11[index].Grade);
            }
            for(index4 = 0; index4 < index; index4++){
                if(Strcmp(CMSC11[index].LastName, CMSC11[index4].LastName) == -1){
                    temp = CMSC11[index4];
                    CMSC11[index4] = CMSC11[index];
                    CMSC11[index] = temp;
                }
            }
        }
        line++;
    }
    fclose(dataset);
    printf("\n\nFilepath: %s successfully read!\n\n", a);
};

void CreateNewStudent(struct student *CMSC11, struct subject *Units, struct subject *Empty){
    int page3_2_1 = 1, page3_2_1_1, index, index2, match;
    struct student temp;
    if(CMSC11[999].StudentID == 0){
        while(page3_2_1 > 0 && CMSC11[999].StudentID == 0){
            for (index = 0; index < 1000; index++){
                if (CMSC11[index].StudentID == 0){
                    break;
                }
            }
            printf("\n\nCREATING STUDENT RECORD\n\n");
            printf("Basic Information:\n");
            match = 1;
            while(match > 0){
                printf("\n\tEnter 3-Digit Student ID: ");
                scanf("%d", &CMSC11[index].StudentID);
                fflush(stdin);
                for (index2 = 0; index2 < index; index2++){
                    if (CMSC11[index].StudentID == CMSC11[index2].StudentID){
                        printf("\n\n\tOops! ID already taken. Try another one!\n\n");
                        match = 1;
                        break;
                    }else{
                        match = 0;
                    }
                }
                if (index == 0){
                    match = 0;
                }
            }
            printf("\n\tEnter First Name: ");
            fgets(CMSC11[index].FirstName, 50, stdin);
            CMSC11[index].FirstName[Strcspn(CMSC11[index].FirstName, "\n")] = 0;
            printf("\n\tEnter Last Name: ");
            fgets(CMSC11[index].LastName, 50, stdin);
            fflush(stdin);
            CMSC11[index].LastName[Strcspn(CMSC11[index].LastName, "\n")] = 0;
            printf("\n\tEnter CMSC11 Section: ");
            fgets(CMSC11[index].CMSC11Section, 50, stdin);
            fflush(stdin);
            CMSC11[index].CMSC11Section[Strcspn(CMSC11[index].CMSC11Section, "\n")] = 0;
            for (index2 = 0; CMSC11[index].CMSC11Section[index2] != '\0'; index2++){
                CMSC11[index].CMSC11Section[index2] = ToUpper(CMSC11[index].CMSC11Section[index2]);
            }
            printf("\n\tEnter Hands-On Exam 1 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[0]);
            fflush(stdin);
            printf("\n\tEnter Hands-On Exam 2 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[1]);
            fflush(stdin);
            printf("\n\tEnter Hands-On Exam 3 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[2]);
            fflush(stdin);
            CMSC11[index].Total = CMSC11[index].HandsOnExams[0] + CMSC11[index].HandsOnExams[1] + CMSC11[index].HandsOnExams[2];
            if (CMSC11[index].Total >= 135){
                Strcpy("HD", CMSC11[index].Grade);
            }else if (CMSC11[index].Total >= 120 && CMSC11[index].Total < 135){
                Strcpy("D", CMSC11[index].Grade);
            }else if (CMSC11[index].Total >= 100 && CMSC11[index].Total < 120){
                Strcpy("P", CMSC11[index].Grade);
            }else if (CMSC11[index].Total >= 75 && CMSC11[index].Total < 100){
                Strcpy("C", CMSC11[index].Grade);
            }else{
                Strcpy("F", CMSC11[index].Grade);
            }
            CMSC11[index].enrolled[0] = &Units[0];
            CMSC11[index].enrolled[1] = Empty;
            CMSC11[index].enrolled[2] = Empty;
            printf("\n\nWould you like to proceed to enrollment?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_1_1);
            switch (page3_2_1_1){
            case 1:
                StudentEnrollment(CMSC11, index);
                break;
            
            default:
                printf("\n\nENROLLMENT REQUEST ABORTED\n\n");
                break;
            }
            printf("Student ID: %d's Basic Information added onto database\n\n", CMSC11[index].StudentID);
            printf("\n\nWould you like to continue to create another student record?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_1);
            fflush(stdin);
            switch (page3_2_1){
            case 1:
                break;
            
            default:
                page3_2_1 = 0;
                break;
            }
            for(index2 = 0; index2 < index; index2++){
                if(Strcmp(CMSC11[index].LastName, CMSC11[index2].LastName) == -1){
                    temp = CMSC11[index2];
                    CMSC11[index2] = CMSC11[index];
                    CMSC11[index] = temp;
                }
            }
        }
        if (page3_2_1 == 0){
            printf("\n\nDone Creating Student Record!\n\n");
        }
    }else{
        printf("\n\nOops! You cannot create another student record. Student Record is at full capacity!\n\n");
    }
};

void StudentEnrollment(struct student *CMSC11, int index){
    int page0 = 1, index2, subjects, tries = 0;
    for(subjects = 0; CMSC11[index].enrolled[subjects] ->SubjectID != 0 && subjects < 3; subjects++);
    if (CMSC11[index].enrolled[2] == &Empty || CMSC11[index].enrolled[1] == &Empty){
        while(page0 > 0){
            printf("\n\nENROLLMENT REQUEST PROCESSING\n\n");
            do{
                DisplaySubjectRecord(Units);
                printf("\nSelect Subject ID: ");
                scanf("%d", &page0);
                fflush(stdin);
                if (page0 == CMSC11[index].enrolled[0] ->SubjectID || page0 == CMSC11[index].enrolled[1] ->SubjectID || page0 == CMSC11[index].enrolled[2] ->SubjectID){
                    printf("\n\nOops! You are already enrolled in this subject. Choose a different one!\n\n");
                }
            } while (page0 == CMSC11[index].enrolled[0] ->SubjectID || page0 == CMSC11[index].enrolled[1] ->SubjectID || page0 == CMSC11[index].enrolled[2] ->SubjectID);
            for(index2 = 0; Units[index2].SubjectID != page0 && index2 < 100; index2++);
            if(Units[index2].SubjectID != 0){
                CMSC11[index].enrolled[subjects] = &Units[index2];
            }else{
                do{
                    printf("\n\nOops! Such ID isn't in the database yet. Try Again!\n\n");
                    do{
                        DisplaySubjectRecord(Units);
                        printf("Select Subject ID: ");
                        scanf("%d", &page0);
                        fflush(stdin);
                        if (page0 == CMSC11[index].enrolled[0] ->SubjectID || page0 == CMSC11[index].enrolled[1] ->SubjectID || page0 == CMSC11[index].enrolled[2] ->SubjectID){
                            printf("\n\nOops! You are already enrolled in this subject. Choose a different one!\n\n");
                        }
                    } while (page0 == CMSC11[index].enrolled[0] ->SubjectID || page0 == CMSC11[index].enrolled[1] ->SubjectID || page0 == CMSC11[index].enrolled[2] ->SubjectID);
                    for(index2 = 0; Units[index2].SubjectID != page0 && index2 < 100; index2++);
                    if(Units[index2].SubjectID != 0){
                        CMSC11[index].enrolled[subjects] = &Units[index2];
                    }else{
                        tries++;
                    }
                    if (tries == 3){
                        page0 = 0;
                        break;
                    }
                } while (CMSC11[index].enrolled[subjects] == &Empty);
            }
            if(CMSC11[index].enrolled[2] == &Empty && tries < 3){
                printf("\n\nWould you like to enroll to other subjects?\n\t1. Yes\t2. No\n\n");
                printf("Select: ");
                scanf("%d", &page0);
                switch (page0){
                case 1:
                    subjects++;
                    break;
                
                default:
                    page0 = 0;
                    break;
                }
            }else{
                page0 = 0;
            }
        }
        if (page0 == 0){
            if (tries == 3){
                printf("\n\nEnrollment Request Aborted\n\n");
            }else{
                printf("\n\nEnrollment Request Done!\n\n");   
            }
        }
    }else{
        printf("Oops! You have already enrolled in 3 subjects. 3 is our max, sorry!\n\n");
    }
};

void SearchStudentRecord(struct student *CMSC11){
    int page3_2 = 1;
    if(CMSC11[0].StudentID != 0){
        while(page3_2 > 0){
            printf("\n\nSEARCHING FOR STUDENT INFROMATION IN STUDENT RECORD\n\n");
            printf("Active Commands:\n\t1. Search by Student ID\t\t2. Search by Student's Last Name\t\t3. Exit\n\n");
            printf("Select: ");
            scanf("%d", &page3_2);
            fflush(stdin);
            switch (page3_2){
            case 1:
                SearchStudentID(CMSC11);
                break;
            
            case 2:
                SearchStudentLastName(CMSC11);
                break;

            default:
                break;
            }
            printf("\n\nWould you like to do another search?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2);
            fflush(stdin);
            switch (page3_2){
            case 1:
                break;
            
            default:
                page3_2 = 0;
                break;
            }
        }
    }else{
        printf("\n\nStudent Record is empty. Try adding a student record first!\n\n");
    }
    printf("\n\nYou left Search Student Record Page.\n\n");
};

void SearchStudentID(struct student *CMSC11){
    int page3_2_1 = 1, index;
    printf("\n\nSEARCHING STUDENT BY STUDENT ID\n\n");
    printf("Enter Student ID: ");
    scanf("%d", &page3_2_1);
    fflush(stdin);
    for (index = 0; CMSC11[index].StudentID != page3_2_1 && index < 1000; index++);
    if(index < 1000){
        printf("\n\nSearch Found!\n\n");
        DisplayStudentSearchedRecord(CMSC11, index);
        printf("Active Commands:\n");
        printf("\t1. Edit Student's Basic Information\n\t2. Enroll to Subject\n\t3. Drop Subject\n\t4. Delete Student's Information\n\t5. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page3_2_1);
        fflush(stdin);
        switch (page3_2_1){
        case 1:
            EditStudentRecord(CMSC11, index);
            break;
            
        case 2:
            StudentEnrollment(CMSC11, index);
            break;

        case 3:
            DropSubject(CMSC11, index);
            break;
        
        case 4:
            DeleteStudentRecord(CMSC11, index);
            break;

        default:
            break;
        }
    }else{
        printf("\n\nNo search results.\n\n");
    }
};

void SearchStudentLastName(struct student *CMSC11){
    int page3_2_2 = 1, index, results, index2;
    char LastNameTemp[50];
    printf("\n\nSEARCHING STUDENT BY STUDENT LAST NAME\n\n");
    printf("Enter Student's Last Name: ");
    fgets(LastNameTemp, 50, stdin);
    fflush(stdin);
    LastNameTemp[Strcspn(LastNameTemp,"\n")] = 0;
    results = 0;
    for(index = 0; index < 1000; index++){
        if(Strcmp(CMSC11[index].LastName, LastNameTemp) == 0){
            results++;
        }
    }
    printf("\n\nSearch Results:");
    if (results > 0){
        for(index = 0; index < 1000; index++){
            if(Strcmp(CMSC11[index].LastName, LastNameTemp) == 0){
                DisplayStudentSearchedRecord(CMSC11, index);
            }
        }
        printf("Select ID: ");
        scanf("%d", &index);
        fflush(stdin);
        for(index2 = 0; CMSC11[index2].StudentID != index; index2++);
        if(index2 < 1000){
            DisplayStudentSearchedRecord(CMSC11, index2);
            printf("Active Commands:\n");
            printf("\t1. Edit Student's Basic Information\n\t2. Enroll to Subject\n\t3. Drop Subject\n\t4. Delete Student's Information\n\t5. Exit\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_2);
            fflush(stdin);
            switch (page3_2_2){
            case 1:
                EditStudentRecord(CMSC11, index2);
                break;
                
            case 2:
                StudentEnrollment(CMSC11, index2);
                break;

            case 3:
                DropSubject(CMSC11, index2);
                break;

            case 4:
                DeleteStudentRecord(CMSC11, index2);
                break;

            default:
                break;
            }
        }
    }else{
        printf("Empty. It seems that, that student doesn't exist!\n\n");
    }
};

void EditStudentRecord(struct student *CMSC11, int index){
    int page3_2_1_1 = 1, index2;
    struct student temp;
    printf("\n\nEDITING BASIC INFORMATION OF STUDENT ID: %d\n\n", CMSC11[index].StudentID);
    while(page3_2_1_1 > 0){
        printf("What Information to Edit?\n");
        printf("\t1. Student's First Name\n\t2. Student's Last Name\n\t3. Student's CMSC11 Section\n\t4. Student's Hands-On Exam 1\n\t5. Student's Hands-On Exam 2\n\t6. Student's Hands-On Exam 3\n\t7. Edit All\n");
        printf("\nSelect: ");
        scanf("%d", &page3_2_1_1);
        fflush(stdin);
        switch (page3_2_1_1){
        case 1:
            printf("\n\nPrevious Student's First Name: %s\n", CMSC11[index].FirstName);
            printf("New Student's First Name: ");
            fgets(CMSC11[index].FirstName, 50, stdin);
            fflush(stdin);
            CMSC11[index].FirstName[Strcspn(CMSC11[index].FirstName, "\n")] = 0;
            break;

        case 2:
            printf("\n\nPrevious Student's Last Name: %s\n", CMSC11[index].LastName);
            printf("New Student's Last Name: ");
            fgets(CMSC11[index].LastName, 50, stdin);
            fflush(stdin);
            CMSC11[index].LastName[Strcspn(CMSC11[index].LastName, "\n")] = 0;
            break;

        case 3:
            printf("\n\nPrevious Student's CMSC11 Section: %s\n", CMSC11[index].CMSC11Section);
            printf("New Student's CMSC11 Section: ");
            fgets(CMSC11[index].CMSC11Section, 50, stdin);
            fflush(stdin);
            CMSC11[index].CMSC11Section[Strcspn(CMSC11[index].CMSC11Section, "\n")] = 0;
            break;

        case 4:
            printf("\n\nPrevious Student's Hands-On Exam 1 Score: %d\n", &CMSC11[index].HandsOnExams[0]);
            printf("New Student's Hands-On Exam 1 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[0]);
            fflush(stdin);
            break;

        case 5:
            printf("\n\nPrevious Student's Hands-On Exam 2 Score: %d\n", &CMSC11[index].HandsOnExams[1]);
            printf("New Student's Hands-On Exam 2 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[1]);
            fflush(stdin);
            break;

        case 6:
            printf("\n\nPrevious Student's Hands-On Exam 3 Score: %d\n", &CMSC11[index].HandsOnExams[2]);
            printf("New Student's Hands-On Exam 3 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[2]);
            fflush(stdin);
            break;

        case 7:
            printf("\n\nPrevious Student's First Name: %s\n", CMSC11[index].FirstName);
            printf("New Student's First Name: ");
            fgets(CMSC11[index].FirstName, 50, stdin);
            fflush(stdin);
            CMSC11[index].FirstName[Strcspn(CMSC11[index].FirstName, "\n")] = 0;
            printf("\nPrevious Student's Last Name: %s\n", CMSC11[index].LastName);
            printf("New Student's Last Name: ");
            fgets(CMSC11[index].LastName, 50, stdin);
            fflush(stdin);
            CMSC11[index].LastName[Strcspn(CMSC11[index].LastName, "\n")] = 0;
            printf("\nPrevious Student's CMSC11 Section: %s\n", CMSC11[index].CMSC11Section);
            printf("New Student's CMSC11 Section: ");
            fgets(CMSC11[index].CMSC11Section, 50, stdin);
            fflush(stdin);
            CMSC11[index].CMSC11Section[Strcspn(CMSC11[index].CMSC11Section, "\n")] = 0;
            printf("\nPrevious Student's Hands-On Exam 1 Score: %d\n", CMSC11[index].HandsOnExams[0]);
            printf("New Student's Hands-On Exam 1 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[0]);
            fflush(stdin);
            printf("\nPrevious Student's Hands-On Exam 2 Score: %d\n", CMSC11[index].HandsOnExams[1]);
            printf("New Student's Hands-On Exam 2 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[1]);
            fflush(stdin);
            printf("\nPrevious Student's Hands-On Exam 3 Score: %d\n", CMSC11[index].HandsOnExams[2]);
            printf("New Student's Hands-On Exam 3 Score: ");
            scanf("%d", &CMSC11[index].HandsOnExams[2]);
            fflush(stdin);
            break;

        default:
            break;
        }
        if (page3_2_1_1 != 7){
            printf("\n\nWould you like to edit more?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_1_1);
            switch (page3_2_1_1){
            case 1:
                break;
        
            default:
                printf("\n\nYou left Edit Student Basic Information Page.\n\n");
                page3_2_1_1 = 0;
                break;
            }
        }else{
            printf("\n\nYou left Edit Student Basic Information Page.\n\n");
        }
    }
    CMSC11[index].Total = CMSC11[index].HandsOnExams[0] + CMSC11[index].HandsOnExams[1] + CMSC11[index].HandsOnExams[2];
    if (CMSC11[index].Total >= 135){
        Strcpy("HD", CMSC11[index].Grade);
    }else if (CMSC11[index].Total >= 120 && CMSC11[index].Total < 135){
        Strcpy("D", CMSC11[index].Grade);
    }else if (CMSC11[index].Total >= 100 && CMSC11[index].Total < 120){
        Strcpy("P", CMSC11[index].Grade);
    }else if (CMSC11[index].Total >= 75 && CMSC11[index].Total < 100){
        Strcpy("C", CMSC11[index].Grade);
    }else{
        Strcpy("F", CMSC11[index].Grade);
    }
    for(index = 0; CMSC11[index].StudentID != 0; index++){
        for(index2 = 0; CMSC11[index2].StudentID != 0; index2++){
            if (Strcmp(CMSC11[index].LastName, CMSC11[index2].LastName) == -1){
                temp = CMSC11[index2];
                CMSC11[index2] = CMSC11[index];
                CMSC11[index] = temp;
            }
        }
    }
};

void DropSubject(struct student *CMSC11, int index){
    int page3_2_1_3 = 1, page3_2_1_3_1;
    while (page3_2_1_3 > 0){
        printf("\n\nDROPPING ENROLLED SUBJECT OF STUDENT ID %d\n\n", CMSC11[index].StudentID);
        printf("Subjects Enrolled in:\n");
        printf("\t1. %s\n", CMSC11[index].enrolled[0] ->SubjectCode);
        if (CMSC11[index].enrolled[1] != &Empty){
            printf("\t2. %s\n", CMSC11[index].enrolled[1] ->SubjectCode);
        }
        if (CMSC11[index].enrolled[2] != &Empty){
            printf("\t3. %s\n", CMSC11[index].enrolled[2] ->SubjectCode);
        }
        printf("\nSelect: ");
        scanf("%d", &page3_2_1_3);
        fflush(stdin);
        switch (page3_2_1_3){
        case 1:
            printf("\nOops! You cannot drop-out from this subject. Sorry, but it is your default one!\n\n");
            break;
        case 2:
            printf("Dropping Subject %s\n", CMSC11[index].enrolled[1] ->SubjectCode);
            printf("Are you sure that you would drop this subject?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_1_3_1);
            fflush(stdin);
            switch (page3_2_1_3_1){
            case 1:
                CMSC11[index].enrolled[1] = &Empty;
                printf("\nYou successfully dropped out from this subject!\n\n");
                break;
            
            default:
                printf("\nDrop-Out Request cancelled!\n\n");
                break;
            }
            break;

        case 3:
            printf("Dropping Subject %s\n", CMSC11[index].enrolled[2] ->SubjectCode);
            printf("Are you sure that you would drop this subject?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_1_3_1);
            fflush(stdin);
            switch (page3_2_1_3_1){
            case 1:
                CMSC11[index].enrolled[2] = &Empty;
                printf("\nYou successfully dropped out from this subject!\n\n");
                break;
            
            default:
                printf("\nDrop-Out Request cancelled!\n\n");
                break;
            }
            break;

        default:
            break;
        }
        if (CMSC11[index].enrolled[1] != &Empty || CMSC11[index].enrolled[2] != &Empty){
            printf("Would you like to drop another subject?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page3_2_1_3);
            fflush(stdin);
            switch (page3_2_1_3){
            case 1:
                break;
            
            default:
                page3_2_1_3 = 0;
                break;
            }
        }else{
            page3_2_1_3 = 0;
        }
    }
    printf("\n\nYou left Drop Subject Page.\n\n");
};

void DisplayStudentSearchedRecord(struct student *CMSC11, int index){
    printf("\n\nDISPLAYING STUDENT RECORD OF STUDENT ID %d\n\n", CMSC11[index].StudentID);
    printf("Basic Information:\n");
    printf("\tStudent ID: %d\n", CMSC11[index].StudentID);
    printf("\tStudent's First Name: %s\n", CMSC11[index].FirstName);
    printf("\tStudent's Last Name: %s\n", CMSC11[index].LastName);
    printf("\tStudent's CMSC11 Section: %s\n", CMSC11[index].CMSC11Section);
    printf("\tStudent's Hands-On Exam 1 Score: %d\n", CMSC11[index].HandsOnExams[0]);
    printf("\tStudent's Hands-On Exam 2 Score: %d\n", CMSC11[index].HandsOnExams[1]);
    printf("\tStudent's Hands-On Exam 3 Score: %d\n", CMSC11[index].HandsOnExams[2]);
    if (CMSC11[index].enrolled[0] != NULL){
        if (CMSC11[index].enrolled[1] != NULL){
            if (CMSC11[index].enrolled[2] != NULL){
                printf("\tStudent's Enrolled Subjects: %s, %s, %s\n\n", CMSC11[index].enrolled[0] ->SubjectCode, CMSC11[index].enrolled[1] ->SubjectCode, CMSC11[index].enrolled[2] ->SubjectCode);
            }else{
                printf("\tStudent's Enrolled Subjects: %s, %s\n\n", CMSC11[index].enrolled[0] ->SubjectCode, CMSC11[index].enrolled[1] ->SubjectCode);
            }
        }else{
            printf("\tStudent's Enrolled Subjects: %s\n\n", CMSC11[index].enrolled[0] ->SubjectCode);
        }
    }
};

void DeleteStudentRecord(struct student *CMSC11, int index){
    int page3_2_0, index2;
    struct student temp;
        printf("\n\nDELETING STUDENT RECORD OF STUDENT ID %d\n\n", CMSC11[index].StudentID);
        printf("Are you sure that you want to delete this student's record?\n\t1. Yes\t2. No\n\n");
        printf("Select: ");
        scanf("%d", &page3_2_0);
        switch (page3_2_0){
        case 1:
            CMSC11[index].StudentID = 0;
            Strcpy("",CMSC11[index].FirstName);
            Strcpy("",CMSC11[index].LastName);
            Strcpy("",CMSC11[index].CMSC11Section);
            CMSC11[index].HandsOnExams[0] = 0;
            CMSC11[index].HandsOnExams[1] = 0;
            CMSC11[index].HandsOnExams[2] = 0;
            CMSC11[index].enrolled[0] = NULL;
            CMSC11[index].enrolled[1] = NULL;
            CMSC11[index].enrolled[2] = NULL;
            CMSC11[index].Total = 0;
            Strcpy("", CMSC11[index].Grade);
            printf("\n\nStudent Record successfully deleted.\n\n");
            if (CMSC11[index+1].StudentID != 0){
                for (index2 = index+1; CMSC11[index2].StudentID != 0; index2++){
                    temp = CMSC11[index2-1];
                    CMSC11[index2-1] = CMSC11[index2];
                    CMSC11[index2] = temp;
                }
            }
            break;
        
        default:
            printf("\n\nDelete Request cancelled.\n\n");
            break;
        }
};

void DisplayStudentRecord(struct student *CMSC11, struct subject *Units){
    int index, index2;
    if(CMSC11[0].StudentID != 0){
        printf("\n\nDISPLAYING ENTIRE STUDENT RECORD\n\n");
        printf("COUNT\tID\tFIRST NAME\t\tLAST NAME\tCMSC11 SECTION\tSUBJECTS ENROLLED\t\tHEX 1 SCORE\tHEX 2 SCORE\tHEX 3 SCORE\tTOTAL\tGRADE\n");
        for (index = 0; CMSC11[index].StudentID != 0; index++){
            printf("%d\t", index+1);
            printf("%d\t", CMSC11[index].StudentID);
            for(index2 = 0; CMSC11[index].FirstName[index2] != '\0'; index2++);
            if (index2+1 < 9){
                printf("%s\t\t\t", CMSC11[index].FirstName);
            }else if (index2+1 < 17){
                printf("%s\t\t", CMSC11[index].FirstName);
            }else{
                printf("%.19s...\t", CMSC11[index].FirstName);
            }
            for(index2 = 0; CMSC11[index].LastName[index2] != '\0'; index2++);
            if (index2+1 < 9){
                printf("%s\t\t", CMSC11[index].LastName);
            }else{
                printf("%.11s...\t", CMSC11[index].LastName);
            }
            printf("%s\t\t", CMSC11[index].CMSC11Section);
            if (CMSC11[index].enrolled[0] != NULL){
                if (CMSC11[index].enrolled[1] != NULL){
                    if (CMSC11[index].enrolled[2] != NULL){
                        printf("%s, %s, %s\t\t", CMSC11[index].enrolled[0] ->SubjectCode, CMSC11[index].enrolled[1] ->SubjectCode, CMSC11[index].enrolled[2] ->SubjectCode);
                    }else{
                        printf("%s, %s\t\t\t", CMSC11[index].enrolled[0] ->SubjectCode, CMSC11[index].enrolled[1] ->SubjectCode);
                    }
                }else{
                    printf("%s\t\t\t\t", CMSC11[index].enrolled[0] ->SubjectCode);
                }
            }
            printf("%d\t\t%d\t\t%d\t\t%d\t", CMSC11[index].HandsOnExams[0], CMSC11[index].HandsOnExams[1], CMSC11[index].HandsOnExams[2], CMSC11[index].Total);
            printf("%s\n", CMSC11[index].Grade);
        }
        StatisticsRecord(CMSC11, &Data);
        printf("\n\t\t\t\t\t\t\t\t\tLOWEST\t\t\t\t%d\t\t%d\t\t%d\t\t%d\n", Data.Lowest[0], Data.Lowest[1], Data.Lowest[2], Data.Lowest[3]);
        printf("\n\t\t\t\t\t\t\t\t\tHIGHEST\t\t\t\t%d\t\t%d\t\t%d\t\t%d\n", Data.Highest[0], Data.Highest[1], Data.Highest[2], Data.Highest[3]);
        printf("\n\t\t\t\t\t\t\t\t\tAVERAGE\t\t\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3lf\n", Data.Average[0], Data.Average[1], Data.Average[2], Data.Average[3]);
        printf("\n\t\t\t\t\t\t\t\t\tSTD.DEVATION\t\t\t%.3lf\t\t%.3lf\t\t%.3lf\t\t%.3f\n\n", Data.StdDeviation[0], Data.StdDeviation[1], Data.StdDeviation[2], Data.StdDeviation[3]);
    }else{
        printf("\n\nOops! The Student Record is empty. I cannot display anything!\n\n");
    }
};

void ClearStudentRecord(struct student *CMSC11){
    int page2_4, index;
    printf("\n\nCLEARING ENTIRE STUDENT RECORD\n\n");
    printf("Are you sure you want to delete all student records?\n\t1. Yes\t2. No\n\n");
    printf("Select: ");
    scanf("%d", &page2_4);
    fflush(stdin);
    switch (page2_4){
    case 1:
        for(index = 0; CMSC11[index].StudentID != 0; index++){
            CMSC11[index].StudentID = 0;
            Strcpy("",CMSC11[index].FirstName);
            Strcpy("",CMSC11[index].LastName);
            Strcpy("",CMSC11[index].CMSC11Section);
            CMSC11[index].HandsOnExams[0] = 0;
            CMSC11[index].HandsOnExams[1] = 0;
            CMSC11[index].HandsOnExams[2] = 0;
            CMSC11[index].enrolled[0] = NULL;
            CMSC11[index].enrolled[1] = NULL;
            CMSC11[index].enrolled[2] = NULL;
            CMSC11[index].Total = 0;
            Strcpy("", CMSC11[index].Grade);
        }
        break;
    
    default:
        break;
    }    
};

void ExportStudentRecord(struct student *CMSC11, struct statistics *Data){
    FILE *export;
    export = fopen("Exported_StudentRecord.csv", "w");
    DisplayStudentRecord(CMSC11, Units);
    if(CMSC11[0].StudentID != 0){
        int page2_5, index;
        fprintf(export,"COUNT,ID,FIRST NAME,LAST NAME,CMSC11 SECTION,HEX 1 SCORE,HEX 2 SCORE,HEX 3 SCORE,SUBJECTS ENROLLED,TOTAL,GRADE\n");
        for (index = 0; CMSC11[index].StudentID != 0; index++){
            fprintf(export,"%d,%d,%s,%s,%s,%d,%d,%d,%s %s %s,%d,%s\n", index+1,CMSC11[index].StudentID, CMSC11[index].FirstName, CMSC11[index].LastName, CMSC11[index].CMSC11Section, CMSC11[index].HandsOnExams[0], CMSC11[index].HandsOnExams[1], CMSC11[index].HandsOnExams[2], CMSC11[index].enrolled[0]->SubjectCode, CMSC11[index].enrolled[1]->SubjectCode, CMSC11[index].enrolled[2]->SubjectCode, CMSC11[index].Total, CMSC11[index].Grade);
        }
        fprintf(export,"\n");
        fprintf(export,",,,,,,Lowest,%d,%d,%d,%d,,\n", Data->Lowest[0], Data->Lowest[1], Data->Lowest[2], Data->Lowest[3]);
        fprintf(export,",,,,,,Highest,%d,%d,%d,%d,,\n", Data->Highest[0], Data->Highest[1], Data->Highest[2], Data->Highest[3]);
        fprintf(export,",,,,,,Average,%.3f,%.3f,%.3f,%.3f,,\n", Data->Average[0], Data->Average[1], Data->Average[2], Data->Average[3]);
        fprintf(export,",,,,,,Std. Deviation,%.3f,%.3f,%.3f,%.3f,,\n", Data->StdDeviation[0], Data->StdDeviation[1], Data->StdDeviation[2], Data->StdDeviation[3]); 
        fclose(export);
        printf("\nStudent Record succesfully extracted!\n\n");
    }else{
        printf("\n\nOops! Record seems to be empty. Can't extract an empty record\n\n");
    }
};

void StatisticsRecord(struct student *CMSC11, struct statistics *Data){
    int index;
    Data->Lowest[0] = CMSC11[0].HandsOnExams[0];
    Data->Lowest[1] = CMSC11[0].HandsOnExams[1];
    Data->Lowest[2] = CMSC11[0].HandsOnExams[2];
    Data->Lowest[3] = CMSC11[0].Total;
    Data->Highest[0] = CMSC11[0].HandsOnExams[0];
    Data->Highest[1] = CMSC11[0].HandsOnExams[1];
    Data->Highest[2] = CMSC11[0].HandsOnExams[2];
    Data->Highest[3] = CMSC11[0].Total;
    for (index = 0; CMSC11[index].StudentID != 0; index++){
        Data->Average[0] = Data->Average[0] + CMSC11[index].HandsOnExams[0];
        Data->Average[1] = Data->Average[1] + CMSC11[index].HandsOnExams[1];
        Data->Average[2] = Data->Average[2] + CMSC11[index].HandsOnExams[2];
        Data->Average[3] = Data->Average[3] + CMSC11[index].Total;
        if (Data->Lowest[0] > CMSC11[index].HandsOnExams[0]){
            Data->Lowest[0] = CMSC11[index].HandsOnExams[0];
        }
        if (Data->Lowest[1] > CMSC11[index].HandsOnExams[1]){
            Data->Lowest[1] = CMSC11[index].HandsOnExams[1];
        }
        if (Data->Lowest[2] > CMSC11[index].HandsOnExams[2]){
            Data->Lowest[2] = CMSC11[index].HandsOnExams[2];
        }
        if (Data->Lowest[3] > CMSC11[index].Total){
            Data->Lowest[3] = CMSC11[index].Total;
        }
        if (Data->Highest[0] < CMSC11[index].HandsOnExams[0]){
            Data->Highest[0] = CMSC11[index].HandsOnExams[0];
        }
        if (Data->Highest[1] < CMSC11[index].HandsOnExams[1]){
            Data->Highest[1] = CMSC11[index].HandsOnExams[1];
        }
        if (Data->Highest[2] < CMSC11[index].HandsOnExams[2]){
            Data->Highest[2] = CMSC11[index].HandsOnExams[2];
        }
        if (Data->Highest[3] < CMSC11[index].Total){
            Data->Highest[3] = CMSC11[index].Total;
        }
    }
    Data->Average[0] = Data->Average[0]/(index);
    Data->Average[1] = Data->Average[1]/(index);
    Data->Average[2] = Data->Average[2]/(index);
    Data->Average[3] = Data->Average[3]/(index);
    for (index = 0; CMSC11[index].StudentID != 0; index++){
        Data->StdDeviation[0] = Data->StdDeviation[0] + (CMSC11[index].HandsOnExams[0] - Data->Average[0])*(CMSC11[index].HandsOnExams[0] - Data->Average[0]);
        Data->StdDeviation[1] = Data->StdDeviation[1] + (CMSC11[index].HandsOnExams[1] - Data->Average[1])*(CMSC11[index].HandsOnExams[1] - Data->Average[1]);
        Data->StdDeviation[2] = Data->StdDeviation[2] + (CMSC11[index].HandsOnExams[2] - Data->Average[2])*(CMSC11[index].HandsOnExams[2] - Data->Average[2]);
        Data->StdDeviation[3] = Data->StdDeviation[3] + (CMSC11[index].Total - Data->Average[3])*(CMSC11[index].Total - Data->Average[3]);
    }
    Data->StdDeviation[0] = Data->StdDeviation[0]/(index);
    Data->StdDeviation[1] = Data->StdDeviation[1]/(index);
    Data->StdDeviation[2] = Data->StdDeviation[2]/(index);
    Data->StdDeviation[3] = Data->StdDeviation[3]/(index);
    Data->StdDeviation[0] = Sqrt(Data->StdDeviation[0]);
    Data->StdDeviation[1] = Sqrt(Data->StdDeviation[1]);
    Data->StdDeviation[2] = Sqrt(Data->StdDeviation[2]);
    Data->StdDeviation[3] = Sqrt(Data->StdDeviation[3]);
};

void CreateSubjectRecord(struct subject *Units){
    int page2_2_1 = 1;
    char directory[100];
    printf("\n\nCREATING A NEW SUBJECT RECORD\n\n");
    printf("Active Commands:\n");
    printf("\t1. Read from File\t2. Create Subject Record\t3. Exit\n\n");
    printf("Select: ");
    scanf("%d", &page2_2_1);
    fflush(stdin);
    switch (page2_2_1){
    case 1:
        printf("\n\nREADING FROM FILE\n\n");
        printf("[Note: Use /] Please enter the directory of the file: ");
        fgets(directory, 100, stdin);
        directory[Strcspn(directory, "\n")] = 0;
        ReadFromFileSubject(Units, directory);
        break;
        
    case 2:
        CreateNewSubject(Units);
        break;

    default:
        printf("\n\nYou left Create Subject Record Page.\n\n");
        break;
    }
};

void ReadFromFileSubject(struct subject *Units, char a[]){
    FILE *dataset = fopen(a, "r");
    char data[10], tempCode[20];
    int index, index2, error = 0, page2_3;
    while (!feof(dataset)){
        for (index = 0; Units[index].SubjectID != 0; index++);
        fscanf(dataset, "\n%[^,], %[^,], %[^\n]", &data, &Units[index].SubjectCode, &Units[index].SubjectTitle);
        Units[index].SubjectID = ToInteger(data);
        DisplaySubjectSearchedRecord(Units, index);
        for (index2 = 0; index2 < index; index2++){
            printf("Current: %d =  Record: %d\n", Units[index].SubjectID, Units[index2].SubjectID);
            if (Units[index].SubjectID == Units[index2].SubjectID && Strcmp(Units[index].SubjectCode, Units[index2].SubjectCode) == 0){
                printf("Flag 1\n");
                error = 0;
                Units[index].SubjectID = 0;
                break;
            }
            if (Units[index].SubjectID == Units[index2].SubjectID && Strcmp(Units[index].SubjectCode, Units[index2].SubjectCode) != 0){
                printf("\n\nSubject ID %d already taken.\n\n", Units[index].SubjectID);
                printf("Flag 2\n");
                printf("Strcmp: %d\n", Strcmp(Units[index].SubjectCode, Units[index2].SubjectCode));
                error = 1;
                break;
            }
            if ((Units[index].SubjectID != Units[index2].SubjectID && Strcmp(Units[index].SubjectCode, Units[index2].SubjectCode) == 0)){
                printf("\n\nSubject Code %s already taken.\n\n", Units[index].SubjectCode);
                printf("Flag 3\n");
                error = 2;
                break;
            }
        }
        if (error == 1){
            printf("Would you like to change the ID?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page2_3);
            fflush(stdin);
            switch (page2_3){
            case 1:
                do{
                    printf("\n\nEnter New Subject ID: ");
                    scanf("%d", &page2_3);
                    fflush(stdin);
                    for (index2 = 0; index2 < index; index2++){
                        if (page2_3 != Units[index2].SubjectID){
                            error = 0;
                        }else{
                            printf("\n\nID already taken.\n\n");
                            error = 1;
                            break;
                        }
                    }
                } while (error == 1);
                Units[index].SubjectID = page2_3;
                break;
            
            default:
                Units[index].SubjectID = 0;
                printf("\n\nSubject Record discarded.\n\n");
                error = 0;
                break;
            }
        }
        if(error == 2){
            printf("Would you like to change the Code?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page2_3);
            fflush(stdin);
            switch (page2_3){
            case 1:
                do{
                    printf("\n\nEnter New Subject Code: ");
                    fgets(tempCode, 20, stdin);
                    tempCode[Strcspn(tempCode, "\n")] = 0;
                    fflush(stdin);
                    for (index2 = 0; index2 < index; index2++){
                        if (Strcmp(tempCode, Units[index2].SubjectCode) != 0){
                            error = 0;
                        }else{
                            printf("\n\nCode already taken.\n\n");
                            error = 1;
                        }
                    }
                } while (error == 1);
                Strcpy(tempCode, Units[index].SubjectCode);
                break;
            
            default:
                Units[index].SubjectID = 0;
                printf("\n\nSubject Record discarded.\n\n");
                error = 0;
                break;
            }            
        }
        index++;
    }
    fclose(dataset);
};

void CreateNewSubject(struct subject *Units){
    int page2_2_2_1 = 1, index, index2, match, match2;
    if(Units[99].SubjectID == 0){
        while(page2_2_2_1 > 0 && Units[99].SubjectID == 0){
            for (index = 0; index < 100; index++){
                if (Units[index].SubjectID == 0){
                    break;
                }
            }
            printf("\n\nCREATING SUBJECT RECORD\n\n");
            printf("Basic Information:\n");
            match = 1;
            while(match > 0){
                printf("\n\tEnter 2-Digit Subject ID: ");
                scanf("%d", &Units[index].SubjectID);
                fflush(stdin);
                for (index2 = 0; index2 < index; index2++){
                    if (Units[index].SubjectID == Units[index2].SubjectID){
                        printf("\n\n\tOops! ID already taken. Try another one!\n\n");
                        match = 1;
                        break;
                    }else{
                        match = 0;
                    }
                }
            }
            match2 = 1;
            while(match2 > 0){
                printf("\n\tEnter Subject Code: ");
                fgets(Units[index].SubjectCode, 20, stdin);
                fflush(stdin);
                Units[index].SubjectCode[Strcspn(Units[index].SubjectCode, "\n")] = 0;
                for (index2 = 0; Units[index].SubjectCode[index2] != '\0'; index2++){
                    Units[index].SubjectCode[index2] = ToUpper(Units[index].SubjectCode[index2]);
                }
                for (index2 = 0; index2 < index; index2++){
                    if (Strcmp(Units[index].SubjectCode,Units[index2].SubjectCode) == 0){
                        printf("\n\n\tOops! Code already taken. Try another one!\n\n");
                        match2 = 1;
                        break;
                    }else{
                        match2 = 0;
                    }
                }
            }
            printf("\n\tEnter Subject Title: ");
            fgets(Units[index].SubjectTitle, 50, stdin);
            fflush(stdin);
            Units[index].SubjectTitle[Strcspn(Units[index].SubjectTitle, "\n")] = 0;
            printf("\n\nSubject ID: %d's Basic Information added onto database\n\n", Units[index].SubjectID);
            printf("\n\nWould you like to continue to create another subject record?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page2_2_2_1);
            fflush(stdin);
            switch (page2_2_2_1){
            case 1:
                break;
            
            default:
                page2_2_2_1 = 0;
                break;
            }
        }
        if (page2_2_2_1 == 0){
            printf("\n\nDone Creating Subject Record!\n\n");
        }
    }else{
        printf("\n\nOops! You cannot create another subject record. Subject Record is at full capacity!\n\n");
    }
};

void SearchSubjectRecord(struct subject *Units){
    int page2_2_3 = 1;
    while(page2_2_3> 0){
        printf("\n\nSEARCHING FOR SUBJECT INFROMATION IN SUBJECT RECORD\n\n");
        printf("Active Commands:\n\t1. Search by Subject ID\t\t2. Search by Subject Code\t\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page2_2_3);
        fflush(stdin);
        switch (page2_2_3){
        case 1:
            SearchSubjectID(Units);
            break;
        
        case 2:
            SearchSubjectCode(Units);
            break;

        default:
            break;
        }
        printf("\n\nWould you like to do another search?\n\t1. Yes\t2. No\n\n");
        printf("Select: ");
        scanf("%d", &page2_2_3);
        fflush(stdin);
        switch (page2_2_3){
        case 1:
            break;
        
        default:
            page2_2_3 = 0;
            break;
        }
    }
    printf("\n\nYou left Search Subject Record Page.\n\n");
};

void SearchSubjectID(struct subject *Units){
    int page2_2_3_1 = 1, index;
    printf("\n\nSEARCHING SUBJECT BY SUBJECT ID\n\n");
    printf("Enter Subject ID: ");
    scanf("%d", &page2_2_3_1);
    fflush(stdin);
    for (index = 0; Units[index].SubjectID != page2_2_3_1 && index < 100; index++);
    if(index < 100){
        printf("\n\nSearch Found!\n\n");
        DisplaySubjectSearchedRecord(Units, index);
        printf("Active Commands:\n");
        printf("\t1. Edit Subject's Basic Information\n\t2. Delete Student's Information\n\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page2_2_3_1);
        fflush(stdin);
        switch (page2_2_3_1){
        case 1:
            EditSubjectRecord(Units, index);
            break;
            
        case 2:
            DeleteSubjectRecord(Units, index);
            break;

        default:
            break;
        }
    }else{
        printf("\n\nNo search results.\n\n");
    }
};

void SearchSubjectCode(struct subject *Units){
    int page2_2_3_2 = 1, index, results;
    char CodeTemp[20];
    printf("\n\nSEARCHING STUDENT BY SUBJECT CODE\n\n");
    printf("Enter Subject Code: ");
    fgets(CodeTemp, 20, stdin);
    fflush(stdin);
    CodeTemp[Strcspn(CodeTemp,"\n")] = 0;
    results = 0;
    for(index = 0; index < 100; index++){
        if (Strcmp(CodeTemp, Units[index].SubjectCode) == 0){
            results++;
            break;
        }   
    }
    if(index < 100 && results == 1){
        printf("\n\nSearch Found!\n\n");
        DisplaySubjectSearchedRecord(Units, index);
        printf("Active Commands:\n");
        printf("\t1. Edit Subject's Basic Information\n\t2. Delete Subject's Information\n\t3. Exit\n\n");
        printf("Select: ");
        scanf("%d", &page2_2_3_2);
        fflush(stdin);
        switch (page2_2_3_2){
        case 1:
            EditSubjectRecord(Units, index);
            break;
            
        case 2:
            DeleteSubjectRecord(Units, index);
            break;

        default:
            break;
        }
    }else{
        printf("\n\nSearch found nothing.\n\n");
    }
};

void EditSubjectRecord(struct subject *Units, int index){
    int page2_2_3_2_1 = 1, match, index2;
    printf("\n\nEDITING BASIC INFORMATION OF SUBJECT ID: %d\n\n", Units[index].SubjectID);
    while(page2_2_3_2_1 > 0){
        printf("What Information to Edit?\n");
        printf("\t1. Subject Code\n\t2. Subject Title\n\t3. Edit All\n\n");
        printf("Select: ");
        scanf("%d", &page2_2_3_2_1);
        fflush(stdin);
        switch (page2_2_3_2_1){
        case 1:
            match = 1;
            while(match > 0){
                printf("Previous Subject Code: %s\n", Units[index].SubjectCode);
                printf("New Subject Code: ");
                fgets(Units[index].SubjectCode, 20, stdin);
                fflush(stdin);
                Units[index].SubjectCode[Strcspn(Units[index].SubjectCode, "\n")] = 0;
                for (index2 = 0; Units[index].SubjectCode[index2] != '\0'; index2++){
                    Units[index].SubjectCode[index2] = ToUpper(Units[index].SubjectCode[index2]);
                }
                for (index2 = 0; index2 < index; index2++){
                    if (Strcmp(Units[index].SubjectCode,Units[index2].SubjectCode) == 0){
                        printf("\n\n\tOops! Code already taken. Try another one!\n\n");
                        break;
                    }else{
                        match = 0;
                    }
                }
                if (index == 0){
                    match = 0;
                }
            }
            break;

        case 2:
            printf("Previous Subject Title: %s\n", Units[index].SubjectCode);
            printf("New Subject Title: ");
            fgets(Units[index].SubjectTitle, 50, stdin);
            fflush(stdin);
            Units[index].SubjectTitle[Strcspn(Units[index].SubjectTitle, "\n")] = 0;
            break;

        case 3:
            printf("\n\nPrevious Subject Code: %s\n", Units[index].SubjectCode);
            printf("New Subject Code: ");
            fgets(Units[index].SubjectCode, 20, stdin);
            fflush(stdin);
            Units[index].SubjectCode[Strcspn(Units[index].SubjectCode, "\n")] = 0;
            printf("Previous Subject Title: %s\n", Units[index].SubjectCode);
            printf("New Subject Title: ");
            fgets(Units[index].SubjectTitle, 50, stdin);
            fflush(stdin);
            Units[index].SubjectTitle[Strcspn(Units[index].SubjectTitle, "\n")] = 0;
            break;

        default:
            break;
        }
        if (page2_2_3_2_1 != 3){
            printf("\n\nWould you like to edit more?\n\t1. Yes\t2. No\n\n");
            printf("Select: ");
            scanf("%d", &page2_2_3_2_1);
            switch (page2_2_3_2_1){
            case 1:
                break;
        
            default:
                printf("\n\nYou left Edit Subject Basic Information Page.\n\n");
                page2_2_3_2_1 = 0;
                break;
            }
        }else{
            printf("\n\nYou left Edit Subject Basic Information Page.\n\n");
        }
    }
};

void DeleteSubjectRecord(struct subject *Units, int index){
    int page2_2_3_2_2, index2;
    if (Units[index].SubjectID != 11){
        printf("\n\nDELETING SUBJECT RECORD OF SUBJECT ID %d\n\n", Units[index].SubjectID);
        printf("Are you sure that you want to delete this subject's record?\n\t1. Yes\t2. No\n\n");
        printf("Select: ");
        scanf("%d", &page2_2_3_2_2);
        switch (page2_2_3_2_2){
        case 1:
            Units[index].SubjectID = 0;
            Strcpy("",Units[index].SubjectCode);
            Strcpy("",Units[index].SubjectTitle);
            printf("\n\nSubject Record successfully deleted.\n\n");
            if (Units[index+1].SubjectID != 0){
                for (index2 = index; Units[index2].SubjectID != 0; index2++){
                    Units[index2] = Units[index2+1];
                }
            }
            break;
        
        default:
            printf("\n\nDelete Request cancelled.\n\n");
            break;
        }
    }else{
        printf("\n\nOops! You cannot delete CMSC11, it is a default subject\n\n");
    }
};

void DisplaySubjectSearchedRecord(struct subject *Units, int index){
    printf("\n\nDISPLAYING SUBJECT RECORD OF SUBJECT ID %d\n\n", Units[index].SubjectID);
    printf("Basic Information:\n");
    printf("\tSubject ID: %d\n", Units[index].SubjectID);
    printf("\tSubject Code: %s\n", Units[index].SubjectCode);
    printf("\tSubject Title: %s\n", Units[index].SubjectTitle);
};

void DisplaySubjectRecord(struct subject *Units){
    int index;
    printf("\n\nDISPLAYING SUBJECT RECORD OF SUBJECT ID %d\n\n", Units[index].SubjectID);
    printf("COUNT\tID\tSUBJECT CODE\tSUBJECT TITLE\n");
    for (index = 0; Units[index].SubjectID != 0; index++){
        printf("%d\t%d\t%s\t\t%s\n", index+1, Units[index].SubjectID, Units[index].SubjectCode, Units[index].SubjectTitle);
    }
};

void ClearSubjectRecord(struct subject *Units){
    int index, page2_2_4;
    printf("\n\nAre you sure you want to clear the entire subject record?\n\t1. Yes\t2. No\n\n");
    printf("Select: ");
    scanf("%d", &page2_2_4);
    fflush(stdin);
    switch (page2_2_4){
    case 1:
        for (index = 1; Units[index].SubjectID != 0; index++){
            Units[index].SubjectID = 0;
            Strcpy("",Units[index].SubjectCode);
            Strcpy("",Units[index].SubjectTitle);
        }
        printf("\n\nSubject Record successfully cleared.\n\n");
        break;
    
    default:
        printf("\n\nDelete Request cancelled.\n\n");
        break;
    }
};

void ExportSubjectRecord(struct subject *Units){
    FILE *export;
    export = fopen("Exported_SubjectRecord.csv", "w");
    int page2_5, index;
    fprintf(export,"SUBJECT ID, SUBJECT CODE, SUBJECT TITLE\n");
    for (index = 0; Units[index].SubjectID != 0; index++){
        fprintf(export,"%d,%s,%s\n", Units[index].SubjectID, Units[index].SubjectCode, Units[index].SubjectTitle);
    }
    fclose(export);
};

int Strcspn(char a[], char b[]){
    int i;
    for (i = 0; a[i] != b[0]; i++){
    }
    return(i);
};

int ToInteger(char st[]){
    int i = 0, integer = 0, sign = 1;
    if (st[0] == '-'){
        i = 1;
        sign = -1;
    }
    for (i = i; st[i] != 00; i++){
        integer = integer * 10 + st[i] - 48;
    }
    return(integer*sign);
};

int Strcmp(char s1[], char s2[]){
    int i, compare;
    for (i = 0; s1[i] != '\0'; i++){
        if (ToLower(s1[i]) == ToLower(s2[i])){
            compare = 0;
        }else if (ToLower(s1[i]) < ToLower(s2[i])){
            compare = -1;
            break;
        }else{
            compare = 1;
            break;
        }
    }
    return(compare);
};

char ToLower(char ch){
    if (ch > 64 && ch < 91){
        ch = ch + 32;
    }
    return(ch);
};

char ToUpper(char ch){
    if (ch > 96 && ch < 123){
        ch = ch - 32;
    }
    return(ch);
};

void Strcpy(char src[], char dest[]){
    int i;
    for (i = 0; src[i] != '\0'; i++){
        dest[i] = src[i];
    }
};

double Sqrt(double number){
    double sqrtNum, temp;
    sqrtNum= number/2;
    temp = 0;
    while(sqrtNum!= temp){
        temp = sqrtNum;
        sqrtNum = (number/temp+temp)/2;
    }
    return(sqrtNum);
};

void Strcat(char s1[], char s2[]){
	int i, j;
	for (i = 0; s1[i] != 0; i++);
  	for (j = 0; s2[j] != 0; j++){
        s1[i] = s2[j];
        i++;
    }
    s1[i] = '\0';
};

int Substring(char s1[], char s2[]){
    int i, j = 0, sim = 0, disim = 0;
    for (i = 0; s2[i] != '\n'; i++){
        for(j = j; s1[j] != '\n'; j++){
            if (s1[j] == s2[i]){
                sim += 1;
                j = j + 1;
                break;
            }else{
                disim += 1;
            }
        }
    }
    if (sim > disim){
        sim = 1;
    }else{
        sim = 0;
    }
    return(sim);
};