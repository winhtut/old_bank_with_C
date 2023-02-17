//
// Created by ncc on 26/01/2023.
//

#ifndef XBANKV1_XBANK_H
#define XBANKV1_XBANK_H




#include "nccColor.h"
#include "stdio.h"
#include "stdlib.h"
#include "time.h"
//#include "conio.h"
#define USIZE 100

struct transaction{
    char note[200];
};
struct database{
    unsigned int id;
    char name[50];
    char email[50];
    char suspend[1];
    char password[50];
    unsigned int phNumber;
    char address[200];
    unsigned int amount;
    struct transaction transRC[100];

};

struct currentTime{

    char curTime[25];
};
struct currentTime getCTime[1];
char rootPass[5]= {'t','o','o','r','\0'};


struct database db[USIZE];
struct database loginEmail[1];

int gIndex=0; // this variable will use for database;
int eFound = -1; // this variable will use for email checking;
int emailValid=0;
int phFound = -1;

int twoCharFlag=-1;


int toDelete = -1;

// for admin variable
int adminEFound=-1;



int spaceArray[100];
int gSpace = 0;
void loading();
void allDataPrinting();
int charCounting(char toCount[50]);
void recordingDataToFile();
void login();
void rEgister();
void menu();
void home();
void emailExitChecking(char lEmail[50]);
void emailValidation(char email[50]);
//void userNameChecking(char toUser[50]);
void userProfileAndMenu(int userDBIndex);
void toTransfer(int userDBIndex , int uFound);
void phNumberChecking(unsigned int to_Phnumber);
void spaceCounting();
void adminSector();
void admin_delete();
void transacitonRecord(int userDBIndex,int uFound,char who);
void twoCharArrayChecking(char one[50],char two[50]);
void deletingUser(int index);
void adminPh_update();
void copyingTwoArray(char receiver[50],char transmitter[50]);
void adminEmail_update();
void admin_update();
void adminAmount_update();
void adminAddress_Update();
void adminUpdate_suspend();
void getTime();
//
//int main(){
//
//    spaceCounting();
//    loading();
//
//    allDataPrinting();
//
//
//    home();
//
//    return 0;
//}

//This function will get all data from file
// and will insert to our database
void loading(){
    FILE *fptr = fopen("8-db.txt","r");
    if(fptr!= NULL){
        for(int i=0; i<USIZE ; i++){
            fscanf(fptr,"%u%s%s%s%s%u%s%u",&db[i].id,&db[i].name,&db[i].email,&db[i].suspend[0],&db[i].password,&db[i].phNumber,&db[i].address,&db[i].amount);
            for(int gcc=0; gcc<=spaceArray[i]-8; gcc++){

                fscanf(fptr,"%s",&db[i].transRC[gcc].note);
            }


            if(db[i].id==0){
                break;
            }
            gIndex++;
        }
    } else{
        nccRed();
        printf("Loading failed at Loading Function():\n");
        nccReset();
    }
    fclose(fptr);
}
void allDataPrinting(){

    for(int i=0; i<gIndex ; i++){
        nccYellow();
        printf("%u-%s-%s-%c-%s-%u-%s-%u",db[i].id,db[i].name,db[i].email,db[i].suspend[0],db[i].password,db[i].phNumber,db[i].address,db[i].amount);
        for(int gcc=0; gcc<=spaceArray[i]-8 ; gcc++){

            printf("-%s",db[i].transRC[gcc].note);
        }
        printf("\n");
        nccReset();
    }
}

void recordingDataToFile(){

    FILE *fptr= fopen("8-db.txt","w");
    if(fptr == NULL){
        nccRed();
        printf("file opening error at recordingToFile Function():\n");
        nccReset();
    } else{
        for(int ncc=0; ncc<gIndex; ncc++){
            if(toDelete != -1){
                if(ncc == toDelete){

                    continue;

                }
            }
            fprintf(fptr,"%u%c%s%c%s%c%c%c%s%c%u%c%s%c%u",db[ncc].id,' ',db[ncc].name,' ',db[ncc].email,' ',db[ncc].suspend[0],' ',db[ncc].password,' ',db[ncc].phNumber,' ',db[ncc].address,' ',db[ncc].amount);
            for(int gcc=0; gcc<spaceArray[ncc]-7 ; gcc++){

                fprintf(fptr," %s",db[ncc].transRC[gcc].note);
            }
            fprintf(fptr,"%c",'\n');

        }
        nccBlue();
        printf("Recording Complete to '8-db.txt' File!\n");
        nccReset();
    }

}

int charCounting(char toCount[50]){
    int charCount=0;
    for(int ncc=0; ncc<50; ncc++){

        if(toCount[ncc] == '\0'){
            break;
        } else{
            charCount++;
        }
    }
    return charCount;
}

void home(){

    nccCyan();
    printf("Welcome to our xBank!\n");
    menu();

}

void menu(){
    int menuOption=0;
    nccCyan();
    printf("[1] For Login!\n");
    printf("[2] For Register!\n");
    printf("[3] Exit!\n");
    printf("Enter your option:");
    scanf("%d",&menuOption);
    nccReset();

    if(menuOption == 1){
        login();
    } else if(menuOption==2){
        rEgister();
    } else if(menuOption == 3){
        recordingDataToFile();
        exit(1);
    } else{
        nccRed();
        printf("Invalid option:\n");
        nccReset();
        menu();
    }

}

void login(){
    char l_email[50];
    nccYellow();
    printf("This is login session:\n");
    nccReset();

    printf("Enter your email address:");
    scanf(" %[^\n]",&l_email[0]);
    eFound = -1;
    emailExitChecking(l_email);

//    if(eFound >=0 && eFound <=3){
//        adminSector();
//    }
//
//    if(eFound != -1 && eFound >3){
//        printf("your email found!\n");
//        printf("Welcome: Mr/s:%s\n",db[eFound].name);
//        userProfileAndMenu(eFound);
//        menu();
//    } else{
//        printf("your email not found pls Register:\n");
//        rEgister();
//        login();
//    }
    if(db[eFound].suspend[0] == 'F'){
        int susUser=0; // option for suspended user
        nccReset();
        nccBlue();
        printf("Your Account was Suspended By XBank Admin!\n");
        nccReset();
        nccYellow();
        printf("Press 1 to get Menu:\nPress 2 to Exit:");
        scanf("%d",&susUser);

        if(susUser == 1){
            menu();
        } else if(susUser == 2){
            recordingDataToFile();
            exit(00);
        } else{
            printf("Invalid Option!\n");
            menu();
            menu();
        }

    } else{

        if(eFound >=0 && eFound <=3){
            adminSector();
        }

        if(eFound != -1 && eFound >3){
            printf("your email found!\n");
            printf("Welcome: Mr/s:%s\n",db[eFound].name);
            userProfileAndMenu(eFound);
            menu();
        } else{
            int rOption=0;
            printf("your email not found pls Register:\n");
            printf("Press 1 to get Menu:\n");
            printf("Press 2 to get Login:\n");
            printf("Press 3 to get Register:");
            scanf("%d",&rOption);
            if(rOption == 1){
                menu();
            } else if(rOption == 2){
                login();
            } else if(rOption == 3){
                rEgister();
            } else{
                system("clear");

            }
        }

    }

}

void rEgister(){

    char rEmail[50];

    printf("This is register!\n");
    printf("Enter your email to Register:");
    scanf(" %[^\n]",&rEmail[0]);

    emailValid = 0;
    emailValidation(rEmail);

    if( emailValid != -1){
        nccCyan();
        printf("Your email format was valid:\nChecking for Register:....\n");
        nccReset();

        eFound=-1;
        emailExitChecking(rEmail);
        int newUserIndex = gIndex;
        if(eFound == -1){
            int toInsertDb_email = charCounting(rEmail);
            for(int z=0; z<toInsertDb_email ; z++){

                db[newUserIndex].email[z] = rEmail[z];

            }
            db[newUserIndex].id = newUserIndex+1;

            nccGreen();
            printf("Enter your username:");
            scanf(" %[^\n]",&db[newUserIndex].name[0]);
            printf("Enter your password:");
            scanf(" %[^\n]",&db[newUserIndex].password[0]);
            printf("Enter your phone number:");
            scanf("%u",&db[newUserIndex].phNumber);
            printf("Enter your address completely:");
            scanf(" %[^\n]",&db[newUserIndex].address[0]);
            printf("Enter your initial amount:");
            scanf("%u",&db[newUserIndex].amount);
            printf("Pls enter some note for your xBank account:");
            scanf(" %[^\n]",&db[newUserIndex].transRC[0].note[0]);

            db[newUserIndex].suspend[0]='T';

            nccPurple();
            printf("Registartion was complete!\n");
            spaceArray[gIndex]=8;
            gIndex++;

            allDataPrinting();
            nccReset();
            login();

        } else{
            nccRed();
            printf("Your email was already register:\n");
            nccReset();
            rEgister();
        }
    } else{
        nccReset();
        nccRed();
        printf("Email format is not valid :\n");
        rEgister();
    }

}

void emailExitChecking(char lEmail[50]){
    int loginEmailCount=charCounting(lEmail);
    printf("\nCounting for input para: %d\n",loginEmailCount);

    for(int ncc=0; ncc<gIndex; ncc++){
        int dbEmailCount =0;

        dbEmailCount = charCounting(db[ncc].email);

        int sameCount=0;
        if( loginEmailCount == dbEmailCount){
            for(int i=0; i<loginEmailCount ; i++){

                if(db[ncc].email[i] == lEmail[i]){
                    sameCount++;
                } else{
                    break;
                }

            }
            if(dbEmailCount == sameCount){
                eFound=ncc;
                adminEFound=ncc;
                return;
            }
        }
    }

}

void emailValidation(char email[50]){

    char emailForm[10]={'@','g','m','a','i','l','.','c','o','m'};
    int cCount = 0;
    for(int a=0; a<50; a++){
        if(email[a] == '@'){
            break;
        } else{
            cCount++;
        }
    }

    printf("\nchecking for email validation %d\n",cCount);
    //int forIndex = charCounting(email);
    int formIndex=0;
    for(int b=cCount; b<cCount+10; b++){

        if( email[b] != emailForm[formIndex]){
            emailValid = -1;
            break;
        }
        formIndex++;
    }
}

void userProfileAndMenu(int userDBIndex){
    int option=0;
    unsigned int toUserPh=0;

    nccReset();
    nccWhite();
    printf("Your Information:\n");
    printf("Name: %s\n",db[userDBIndex].name);
    printf("PhNumber: %u\n",db[userDBIndex].phNumber);
    printf("Amount: %u\n",db[userDBIndex].amount);

    nccReset();
    nccBlue();
    printf("Press 1: to Update Information:\n");
    printf("Press 2: to Transfer:\n");
    printf("Press 3: to Withdraw:");

    scanf("%d",&option);

    if(option == 1){
        printf("This is for update information:\n");
    } else if(option == 2){
        printf("This is for Transaction:\n");
        printf("Pls enter PhNumber to send money for:");
        scanf("%u",&toUserPh);
        phFound=-1;
        phNumberChecking(toUserPh);

        if(phFound != -1){
            //printf("User for %d is %s email: %s \n",toUserPh,db[phFound].name,db[phFound].email);
            toTransfer(userDBIndex,phFound);

        } else{
            printf("User PhNumber not Found!\n");
            userProfileAndMenu(userDBIndex);
        }

    }
}

void toTransfer(int userDBIndex , int uFound){
    unsigned  int toAmount = 0;
    int option=0;

    nccReset();
    nccGreen();
    printf("You are:%s amount:%u\n",db[userDBIndex].name,db[userDBIndex].amount);
    nccReset();
    nccRed();
    printf("U can transfer to ph:%u : name:%s : email:%s\n",db[uFound].phNumber,db[uFound].name,db[uFound].email);
    printf("Please enter amount to send if u sure:");
    scanf("%u",&toAmount);

    if(toAmount < db[userDBIndex].amount-1000){
        db[userDBIndex].amount =db[userDBIndex].amount-toAmount; // လွှဲမည့်သူ   transferer
        db[uFound].amount +=toAmount; // လက်ခံမည့်သူ
        transacitonRecord( userDBIndex, uFound, 't');
        transacitonRecord( userDBIndex, uFound, 'r');

        allDataPrinting();

        printf("Transaction was successful!\n");
        printf("Your amount for now :%u\n",db[userDBIndex].amount);
        nccReset();
        nccCyan();
        printf("Press 1 to User Profile:\n");
        printf("Press 2 to Exit:\n");
        printf("Press 3 to Home:\n");

        scanf(" %d",&option);

        if(option == 1){

            userProfileAndMenu(userDBIndex);
        } else if(option == 2){
            recordingDataToFile();
        } else if(option == 3){
            menu();

        } else{
            printf("Invalid Option:\n");
            userProfileAndMenu(userDBIndex);
        }

    } else{
        nccReset();
        nccRed();
        printf("[X]Your amount not sufficient!\n");
        nccReset();
        toTransfer(userDBIndex,uFound);
    }

}
void phNumberChecking(unsigned int to_Phnumber){

    for(int i=0; i<gIndex ; i++){

        if(db[i].phNumber == to_Phnumber){

            phFound = i;
        }

    }

}
void spaceCounting(){
    FILE *fptr = fopen("8-db.txt","r");
    char c = fgetc(fptr);
    int index=0;
    while (!feof(fptr)){
        if(c!='\n'){
            if(c == ' '){
                spaceArray[index] +=1;
            }
            c = fgetc(fptr);

        }else{
            index++;
            c = fgetc(fptr);
        }

    }
    gSpace = index;
    for(int i=0; i<index ; i++){
        printf("%d : ",spaceArray[i]);
    }
    printf("\n");
    fclose(fptr);

}

void adminSector(){
    nccReset();
    nccRed();
    int admin_Option=0;
    printf("Welcome Admin:\n");
    printf("All of Actions are shall be liable to you:\n");

    printf("Press 1 to Delete User Account:\n");
    printf("Press 2 to Update Information of user:\n");
    printf("Press 3 to Suspend User Account:\n");
    printf("Press 4 to Exit!\n");
    printf("Press 5 to Get Home Sector:\n");
    printf("Press your option carefully:");
    scanf("%d",&admin_Option);

    if(admin_Option == 1){
        admin_delete();
    } else if(admin_Option == 2){
        admin_update();

    } else if(admin_Option == 3){
        printf("This is Suspend Session for admin:\n");
        adminUpdate_suspend();
    } else if(admin_Option == 4){
        printf("Good Luck!:");
        recordingDataToFile();
        exit(1);
    } else if(admin_Option == 5){

        home();
    }

    else{
        printf("Invalid Option Pls Try Again!\n");
        adminSector();
    }


}
void admin_delete(){
    char toDeleteEmail[50];
    printf("This is Delete  for admin:\n");
    char rootPW[30];
    printf("Enter your Root Password:");
    scanf(" %[^\n]",&rootPW[0]);

    twoCharFlag = -1;
    twoCharArrayChecking(rootPW , rootPass);

    if (twoCharFlag != -1){

        printf("Enter user email address to delete:");
        scanf(" %[^\n]",&toDeleteEmail[0]);
        eFound = -1;
        emailExitChecking(toDeleteEmail);

        if( eFound != -1){


            deletingUser(eFound);

        }
        else{

            printf("Email not Found!");
            admin_delete();
        }

    } else{
        nccReset();
        nccYellow();
        printf("\nAdmin Password denied Pls reEnter Carefully!\n");
        nccReset();
        admin_delete();
    }

}

void transacitonRecord(int userDBIndex,int uFound,char who){
    int transfer = charCounting(db[userDBIndex].name);
    int accept = charCounting(db[uFound].name);

    if(who == 't') {

        char toInsert1[4] ={'F','r','o','m'};
        char toInsert2[2] ={'t','o'};
        //db[userDBIndex].transRC[spaceArray[userDBIndex]].note

        int indexPoint=0;
        for(int x=indexPoint; x<4; x++){
            db[userDBIndex].transRC[spaceArray[userDBIndex]-7].note[x]=toInsert1[x];
            indexPoint++;
        }
        int nameIndex=0;
        int endPoint = indexPoint+transfer;
        for(int x=indexPoint; x<endPoint; x++){
            db[userDBIndex].transRC[spaceArray[userDBIndex]-7].note[indexPoint]=db[userDBIndex].name[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex=0;
        endPoint = indexPoint+2;
        for(int x=indexPoint; x<endPoint; x++){
            db[userDBIndex].transRC[spaceArray[userDBIndex]-7].note[indexPoint]=toInsert2[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex=0;
        endPoint = indexPoint+accept;
        for(int x=indexPoint; x<endPoint; x++){
            db[userDBIndex].transRC[spaceArray[userDBIndex]-7].note[indexPoint]=db[uFound].name[nameIndex];
            nameIndex++;
            indexPoint++;
        }
        nameIndex=0;
        getTime();
        for(int win=endPoint; win<25+endPoint ; win++ ){

            db[userDBIndex].transRC[spaceArray[userDBIndex]-7].note[win]=getCTime[0].curTime[nameIndex];
            nameIndex++;
        }
        spaceArray[userDBIndex] = spaceArray[userDBIndex]+1;
    } else{

        char receiveFrom[13] = {'-','R','e','c','e','i','v','e','F','r','o','m','-'};
        int indexPoint=0;
        int endpoint=0;
        int reIndex=0;
        for(int i=0;i<accept;i++){
            db[uFound].transRC[spaceArray[uFound]-7].note[i]=db[uFound].name[i];
            indexPoint++;
        }
        endpoint=accept+13;
        for(int i=indexPoint;i<endpoint;i++){
            db[uFound].transRC[spaceArray[uFound]-7].note[i]=receiveFrom[reIndex];
            reIndex++;

        }
        reIndex=0;
        int toendpoint=endpoint+transfer;
        for(int i=endpoint;i<toendpoint;i++){
            db[uFound].transRC[spaceArray[uFound]-7].note[i]=db[userDBIndex].name[reIndex];
            reIndex++;
        }

        reIndex=0;
        getTime();
        for(int win=toendpoint; win<25+toendpoint ; win++ ){

            db[uFound].transRC[spaceArray[uFound]-7].note[win]=getCTime[0].curTime[reIndex];
            reIndex++;
        }

        spaceArray[uFound] = spaceArray[uFound]+1;

    }

}

void twoCharArrayChecking(char one[50],char two[50]){

    int sameCount=0;
    int oneChar = charCounting(one);
    int twoChar = charCounting(two);

    if(oneChar == twoChar){

        for(int a=0; a<oneChar ; a++){
            if(one[a] == two[a]){
                sameCount++;
            }
        }

    }
    if( oneChar == sameCount){
        twoCharFlag=1;
    }
}

void deletingUser(int index){

//    printf("You have to delete %s ph %u\n",db[index].name , db[index].phNumber);
//
//    for(int gcc = index ; gcc<gIndex ; gcc++){
//
//        db[gcc].name = db[gcc+1].name;
//
//    }
    char delEmail[8]={'n','o','t','v','a','l','i','d'};
    toDelete = index;
    copyingTwoArray(db[index].email,delEmail);

    recordingDataToFile();
    loading();
    //allDataPrinting();
    adminSector();

}

void admin_update(){

    unsigned int phNumber=0;
    printf("This is Update Session for admin:\n");
    printf("Enter Phone Number of User to Update:");
    scanf(" %u",&phNumber);
    phFound = -1;
    phNumberChecking(phNumber);
    if(phFound != -1){
        int updateOption=0;
        printf("This is User Information:\n");
        printf("id   name      email         amount\n");
        nccRed();
        printf("%u %s %s %u\n",db[phFound].id ,db[phFound].name,db[phFound].email,db[phFound].amount );
        printf("Which one Do U like to Update Sir:\n");
        printf("Press 1 to update phNumber:\nPress 2 to update email:\nPress 3 to update amount:\nPress 4 to update Address:");
        scanf("%d",&updateOption);

        if(updateOption == 1){
            adminPh_update();
        } else if(updateOption == 2){
            adminEmail_update();
        } else if(updateOption == 3){
            adminAmount_update();
        } else if(updateOption == 4){
            adminAddress_Update();
        } else{
            printf("Invalid Option!\n");
            admin_update();
        }

    } else{

        nccReset();
        nccWhite();
        printf("Phone Number was not Found! or The User is not exist!\n");
        nccReset();
        admin_update();

    }

}

void adminPh_update(){
    int adminPhOption=0;
    nccReset();
    nccBlue();
    unsigned int newPhNumber = 0;
    printf("Enter New PhNumber Sir:\n");
    scanf("%u",&newPhNumber);
    //this place can need for sms validation for real world.
    db[phFound].phNumber = newPhNumber;
    nccReset();
    nccGreen();
    printf("Phone Number Was update:\n");
    nccReset();
    printf("Press 1 to get AdminSector:\nPress 2 to get admin_update:\nPress 3 to Exit:");
    scanf("%d",&adminPhOption);

    if(adminPhOption == 1){
        adminSector();
    } else if(adminPhOption==2){
        admin_update();
    } else if(adminPhOption == 3){
        recordingDataToFile();
        exit(00);

    } else{
        printf("Invalid Option :\n");
        admin_update();
    }

}

void adminEmail_update(){

    int adminEOption=0;

    nccReset();
    nccPurple();
    char toUpdateEmail[50];
    printf("This Admin Email Update Option!\n");
    printf("Enter new Email Sir:\n");
    scanf(" %[^\n]",&toUpdateEmail[0]);
    emailValid=0;
    emailValidation(toUpdateEmail);

    if(emailValid != -1){

        adminEFound=-1;
        emailExitChecking(toUpdateEmail);

        if(adminEFound != -1){

            printf("Email Was already exit at User:\n");
            adminEmail_update();

        } else{

            // to update email to database:

            copyingTwoArray(db[phFound].email , toUpdateEmail);
            nccReset();
            nccGreen();
            printf("New Email  Was update:\n");
            nccReset();
            printf("Press 1 to get AdminSector:\nPress 2 to get admin Email update:\nPress 3 to Exit:");
            scanf("%d",&adminEOption);

            if(adminEOption == 1){
                adminSector();
            } else if(adminEOption==2){
                admin_update();
            } else if(adminEOption == 3){
                recordingDataToFile();
                exit(00);

            } else{
                printf("Invalid Option :\n");
                admin_update();
            }
        }

    } else{
        nccReset();
        nccRed();
        printf("Email Format was not valid Sir:\n");
        adminPh_update();
    }

}

void copyingTwoArray(char receiver[200],char transmitter[200]){

    for(register int aaa=0; aaa<200; aaa++){

        receiver[aaa]='\0';
    }
    //getting amount of char for transmitter -new email
    int charCount = charCounting(transmitter);

    for(register int gcc=0; gcc<charCount ; gcc++){
        receiver[gcc] = transmitter[gcc];
    }
}

void adminAmount_update(){
    unsigned int amount=0;
    printf("Enter amount to Add:");
    scanf("%u",&amount);

    db[phFound].amount = amount;

    nccReset();
    nccGreen();
    printf("New Amount was updated:\n");
    nccReset();
    int adminEOption=0;
    printf("Press 1 to get AdminSector:\nPress 2 to get admin  update:\nPress 3 to Exit:");
    scanf("%d",&adminEOption);

    if(adminEOption == 1){
        adminSector();
    } else if(adminEOption==2){
        admin_update();
    } else if(adminEOption == 3){
        recordingDataToFile();
        exit(00);

    } else{
        printf("Invalid Option :\n");
        admin_update();
    }

}
void adminAddress_Update(){

    char newAddress[200];
    nccReset();
    nccPurple();
    printf("This is Admin Address Update Session:\n");
    printf("Enter new address without using space character:");
    scanf(" %[^\n]",&newAddress[0]);

    copyingTwoArray(db[phFound].address,newAddress);
    nccReset();
    nccRed();
    printf("[+]New Address was Updated:\n %s\n",db[phFound].address);
    nccReset();
    int adminEOption=0;
    printf("Press 1 to get AdminSector:\nPress 2 to get admin  update:\nPress 3 to Exit:");
    scanf("%d",&adminEOption);

    if(adminEOption == 1){
        adminSector();
    } else if(adminEOption==2){
        admin_update();
    } else if(adminEOption == 3){
        recordingDataToFile();
        exit(00);

    } else{
        printf("Invalid Option :\n");
        admin_update();
    }

}

void adminUpdate_suspend(){
    char susEmail[50];
    int susSure=0;
    nccReset();
    nccGreen();
    printf("This is Admin User Suspend Session!\n");
    nccReset();
    nccRed();
    printf("HIGH RISK!\n");
    nccReset();

    printf("Enter email address of user to Suspend:");
    scanf(" %[^\n]",&susEmail[0]);
    eFound=-1;
    emailExitChecking(susEmail);

    if(eFound != -1){
        nccReset();
        nccCyan();
        printf("Email Was found:\nUser name : %s\n",db[eFound].name);

        printf("Press 1 to Proceed:\nPress 2 for Suspend Option:");
        scanf("%d",&susSure);

        if(susSure == 1){
            db[eFound].suspend[0]='F';
            nccReset();
            nccCyan();
            printf("Suspension was completed for User: %s email: %s\n",db[eFound].name,db[eFound].email);
            nccReset();
            nccYellow();
            int adminEOption=0;
            printf("Press 1 to get AdminSector:\nPress 2 to get admin  update:\nPress 3 to Exit:");
            nccReset();
            scanf("%d",&adminEOption);

            if(adminEOption == 1){
                adminSector();
            } else if(adminEOption==2){
                admin_update();
            } else if(adminEOption == 3){
                recordingDataToFile();
                exit(00);

            } else{
                printf("Invalid Option :\n");
                admin_update();
            }

        } else if(susSure == 2){

            adminUpdate_suspend();
        } else{
            printf("Invalid Option!\n");
            adminUpdate_suspend();
        }

    } else{
        printf("Email Not Found!\n");
        adminUpdate_suspend();

    }
}

void getTime(){

    time_t tm;
    time(&tm);

    printf("Current Date/Time = %s", ctime(&tm));
    FILE *fptr= fopen("mytime.txt","w");
    fprintf(fptr,"%s", ctime(&tm));
    int index=0;
    getCTime[0].curTime[index]='-';
    index++;
    fclose(fptr);
    FILE *rFptr = fopen("mytime.txt","r");
    char c = fgetc(rFptr);
    while (!feof(rFptr)){
        if(c ==' '){
            getCTime[0].curTime[index]='-';
            c = fgetc(rFptr);
            index++;

        } else{
            getCTime[0].curTime[index] = c;
            c = fgetc(fptr);
            index++;

        }

    }

}








#endif //XBANKV1_XBANK_H
