extern int debugMode;
/*****************************************************************
//      Function name: addRecord
//  //
//  //  DESCRIPTION:   Function is called by user interface to add a record
//  //   to the database where it copies the information to a new record file 
//  //   and proceeds to search through record to find its correct posistion or a duplicate accountno
//  //                 
//  //
//  //  Parameters:    start: pointer to the first record in the list 
//  //                 uaccountno: accountno entered by the user
//  //                 uname: name entered by the user
//  //                 uaddreess: address entered by the user
//  //  Return values:  0:file was added 
//  //                  -1: duplicate file found
//  //
****************************************************************/
int addRecord(struct record **start, int uaccountno, char uname[], char uaddress[])
{   
    int result = 0; 
    int duplicate = 0;   
    struct record *newRecord = NULL;
    struct record *current = *start;
    struct record *previous = NULL;
    if(debugMode == 1)
    {   
        printf("\nDebugMode ON: addRecord()");
        printf("\nParameters: id = %d, name = %s, address = %s\n", uaccountno, uname, uaddress);
     
    }
    current = *start;
    while(current != NULL && current->accountno < uaccountno)
    {   
        if(debugMode == 1)
        {   
            printf("Checking account number %d against %d\n", current->accountno, uaccountno);
        }
        previous = current;
        current = current->next;
    
    }
    if(current != NULL && current->accountno == uaccountno)
    {
        if(debugMode == 1)
        {
            printf("Duplicate accound number found: %d\n", uaccountno);
        }
            duplicate = 1;
            result = -1;
    }

    if(!duplicate)
    {
        newRecord = (struct record*)malloc(sizeof(struct record));
        if(newRecord == NULL)
        {
            result = -1;
        }
        else
        {
            newRecord->accountno = uaccountno;
            strncpy(newRecord->name, uname, sizeof(newRecord->name) - 1);
            newRecord->name[sizeof(newRecord->name) - 1] = '\0';
            strncpy(newRecord->address, uaddress, sizeof(newRecord->address) - 1);
            newRecord->address[sizeof(newRecord->address) - 1] = '\0';
            newRecord->next = current;

            if(previous == NULL)
            {
                *start = newRecord;
            }
            else
            {
                previous->next = newRecord;
            }
        }
    }
    return result;
}
/*****************************************************************
            Function name: printAllRecords
//  //  //
//  //  //  DESCRIPTION:   When called it prints all records
//  //  //                 currently in the database including
//  //  //                 their name, accoutno and address
//  //  //  Parameters:    start(record*): pointer to the first
//  //  //                 record in the data base
//  //  //
//  ****************************************************************/
void printAllRecords(struct record *start)
{
    struct record *current = start;
    if(debugMode == 1)
    {
        printf("\nDebugMode ON: PrintAllRecords(struct record *head) has been called\n");
    }
    printf("Current Records: \n");
    if(current == NULL)
    {
        printf("There are no current records");
    }

    while(current != NULL)
    {
        printf("Account: %d, Name: %s, Address: %s\n",current->accountno, current->name, current->address);
        current = current->next;
    }
    printf("\n");

}

/*****************************************************************
//  //  //  Function name: findRecord
//  //
//  //  //  DESCRIPTION:   Function iterates through the array until it
//  //  //                 finds the account with the matching id # then 
//  //  //                 prints the account information or returns an 
//  //  //                 error if the account is not found 
//  //  // 
//  //  //  Parameters:    accountno (int): accountno being searched for 
//  //  //                 start (struct record*): pointer to the first node
//  //  //                            
//  //  //
//  //  //  Return values:  0 : record was found a printed
//  //  //                 -1 : record was not found
//  //  //
//  ****************************************************************/
int findRecord(struct record *start, int uaccountno)
{

    int result = -1;
    struct record* current = start;
    if(debugMode == 1)
    {
        printf("\nDebugMode ON: findRecord()");
        printf("\nParameters: id = %d\n", uaccountno);
    }
     while(current != NULL)
    {
        if(debugMode == 1)
        {
            printf("Visiting node with account number: %d at adress: %p\n", current->accountno, (void*)current);
        }
        if(current->accountno == uaccountno)
        {
            printf("Account: %d, Name: %s, Address: %s\n",current->accountno, current->name, current->address);
            result = 0;
        }

        current = current->next;
    }
    if(debugMode == 1)
    {
        printf("Result of find function: %d", result);
    }
    return result;
}
/*****************************************************************
            Function name: main
//  //
//  //  //  DESCRIPTION:   Don't forget to describe what your main
//  //  //                 function does.
//  //  //
//  //  //  Parameters:    argc (int) : The number of elements in argv
//  //  //                 argv (char*[]) : An array of arguments passed
//  //  //                                  to the program.
//  //  //
//  //  //  Return values:  0 : account deleted succesfully
//  //  //                  1: account not found 
//  //  //
 ****************************************************************/
int deleteRecord(struct record **start, int uaccountno)
{
    int result = -1;
    struct record* current = *start;
    struct record* previous = NULL;
    if(debugMode == 1)
    {
        printf("\nDebugMode ON: deleteRecord()");
        printf("\nParameters: id = %d\n",  uaccountno);
        printf("Starting at address: %p\n", (void*)*start);

    }


    while(current != NULL)
    {
        if(debugMode == 1)
        {
            printf("Visiting node with account number: %d at adress: %p\n", current->accountno, (void*)current);
        }
        if(current->accountno == uaccountno)
        {
            if(previous == NULL)
            {
                    *start = current->next;
                    if(debugMode == 1)
                    {
                        printf("deleted head node. New address:%p\n",(void*)*start);
                    }
            }
            else
            {
                previous->next = current->next;
                if(debugMode == 1)
                {
                        printf("deleted node with account number: %d,  Linking previous node at %p to next node at %p\n", current->accountno, (void*)previous, (void*)current->next);
                }
            }

            if(debugMode == 1)
            {
                printf("deleteing accountno: %d\n, with addres: %p\n", current->accountno,(void*)current);
            }
            free(current);

            result = 0;
            if(debugMode == 1)
            {
                printf("result of delete function: %d\n", result);
            }
            return result;
        }

        previous = current;
        current = current->next;

    }
    if(debugMode == 1)
    {
        printf("Record with account number %d not found.\n", uaccountno);
    }
    return result;
}
/*****************************************************************
//////// function name:   cleanup
/////////  DESCRIPTION:   A function that is called when the user quits
//////////                that releases all the allocated spaces in the 
//////////                heaps memory and assigns start to NULL
//////////  Parameters:
//////////  Struct **start: pointer to the first node in the record list
****************************************************************/
void cleanup(struct record **start)
{

    struct record *current = *start;
    struct record *next;

    if(debugMode == 1)
    {
         printf("DebugMode ON: Cleanup Called\n");
    }

    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *start = NULL;
    if(debugMode == 1)
    {
         printf("start now points to %p\n",(void*)*start);
    }

}
/*****************************************************************
//////// function name: readfile
////////  DESCRIPTION:   A function that reads the information from a  
////////                file and restores it in the database
////////
////////
////////  Parameters:
////////  Struct **start: pointer to the first node in the record list
////////  char filename[]: file being opened and read from
////////
////////  Return values: 0: the file was succesfuly opened and read
////////                 -1: the file could not be opened
////////
****************************************************************/
int readfile(struct record **start, char filename[])
{   
    FILE *file;
    int accountno;
    int result = 0;
    char name[25];
    char address[50];
    struct record *newRecord;
    struct record *last = NULL;

    file = fopen(filename, "r");
    if(file == NULL)
    {
        return -1;
    }

    while(fscanf(file,"%d\n", &accountno) == 1)
    {
        fgets(name, sizeof(name), file);
        name[strcspn(name, "\n")]='\0';

        fgets(address, sizeof(address), file);
        address[strcspn(address,"\n")] = '\0';

        newRecord = (struct record *)malloc(sizeof(struct record));
        if(newRecord == NULL)
        {
            fclose(file);
            cleanup(start);
            return -1;
        }
        if (debugMode == 1)
        {
            printf("Read record: Account No: %d, Name: %s, Address: %s\n", accountno, name, address);
        }

        newRecord->accountno = accountno;
        strncpy(newRecord->name, name, sizeof(newRecord->name)-1);
        newRecord->name[sizeof(newRecord->name)-1]='\0';
        strncpy(newRecord->address, address, sizeof(newRecord->address)-1);
        newRecord->address[sizeof(newRecord->address)-1] = '\0';
        newRecord->next = NULL;

        if(*start == NULL)
        {
            *start = newRecord;
        }
        else
        {
            last->next = newRecord;
        }
        last = newRecord;
    }
    fclose(file);
    if (debugMode == 1)
    {
        printf("DebugMode: Finished reading file '%s'.\n", filename);
    }
    return result;
}


/*****************************************************************
////////  Function name: writefile
////////
////////  DESCRIPTION:   A function that writes all the records                 
////////                 stored in the heap to a file that can 
////////                 be reopened later
////////
////////
////////  Parameters:
////////  Struct* start: pointer to the first record in the list             
//////// 
////////  char filename[]: file where the data is being wrote to
////////
////////  Return values: 0: the file was succesfully opened and wrote to
////////                 -1: Writing to the file was unsuccesful
////////
****************************************************************/
int writefile(struct record *start, char filename[])
{
    int result=0;
    FILE *file;
    struct record *current = start;
    if (debugMode == 1)
    {
        printf("DebugMode ON: Opening file '%s' for writing...\n", filename);
    }

    file = fopen(filename,"w");
    if(file == NULL)
    {
        return -1;
    }
    while(current != NULL)
    {
        fprintf(file, "%d\n%s\n%s\n", current->accountno, current->name, current->address);
        if (debugMode == 1)
        {
            printf("Writing record: Account No: %d, Name: %s, Address: %s\n", current->accountno, current->name, current->address);
        }
        current = current->next;
    }
    fclose(file);
    return result;
}


