/* *********** Pledge of Honor *************************************************************************** *
 * I hereby certify that I have completed this programming assignment on my own *
 * without any help from anyone else. The effort in the assignment thus belongs *
 * completely to me. I did not search for a solution, or I did not consult to any program *
 * written by other students or did not copy any program from other sources. I read and *
 * followed the guidelines provided in the programming assignment. *
 *
 * READ AND SIGN BY WRITING YOUR NAME SURNAME AND STUDENT ID
 * SIGNATURE: <Ýsmail Ozan Kayacan, 69103>
 *
 * ************************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


typedef struct{
	char sender[100];
	char receiverAddress[100];
	int subject;
	char date[100];
	char messageContent[100];
}Mail;

typedef struct ListNodeMail{
	Mail mail;
	struct ListNodeMail *nextPtr;
} ListNodeMail;

typedef struct ListNodeMail *ListNodeMailPtr;

typedef struct{
	char eMail[100];
	ListNodeMailPtr *inbox;
}User;

typedef struct ListNodeUser{
	User user;
	struct ListNodeUser *nextPtr;
} ListNodeUser;

typedef struct ListNodeUser *ListNodeUserPtr;

typedef struct{
	char domainName[100];
	ListNodeUserPtr *usersList;
}MailServer;

//-----------------------------------FUNCTIONS-----------------------------------//
//A=65, Z=90, a=97, z=122
char* decrypt(char *s, int n){ //pass by value
	int len=strlen(s);
	char *result;
	result=malloc(sizeof(char)*100);

	for(int i=0; i<len; i++){
		if(isupper(s[i])){
			result[i]=65+(s[i]-65+n)%26;
		} else if (islower(s[i])){
			result[i]=97+(s[i]-97+n)%26;
		}
	}
	result[len]='\0';
	return result;
}

int correctSubject(char *s){ //pass by value

	int len = strlen(s);
	int true=1;
	if(!isdigit(s[0]) || !isdigit(s[len-1])){
		true=0;
	} else {
		for(int i=0; i<len; i++){
			if(!isdigit(s[i]) && s[i]!='+' && s[i]!='-' && s[i]!='*' && s[i]!='/' && s[i]!=' '){
				true=0;
			}
			if(isdigit(s[i]) && i!=len-1 && ( !isdigit(s[i+1]) && s[i+1]!=' ') ){
				true=0;
			}
			if(s[i]==' ' &&( ( isdigit(s[i-1]) && isdigit(s[i+1]) ) || ( !isdigit(s[i-1]) && !isdigit(s[i+1]) ) ) ){
				true=0;
			}
			if((s[i]=='+' || s[i]=='-' || s[i]=='*' || s[i]=='/') && (isdigit(s[i-1]) || isdigit (s[i+1]))){
				true=0;
			}
		}
	}
	return true;
}

int calculateSubject(char *s){ //pass by value
	char *string=malloc(100*sizeof(char));
	strcpy(string,s);

	char *tokenPtr=malloc(100*sizeof(char));

	tokenPtr=strtok(string, " ");

	int result=atoi(tokenPtr);
	int operation; //1 for add, 2 for substract, 3 for multiply, 4 for divide

	while (tokenPtr != NULL) {

		if (strcmp(tokenPtr,"+")==0){
			operation=1;
		}else if (strcmp(tokenPtr,"-")==0){
			operation=2;
		}else if (strcmp(tokenPtr,"*")==0){
			operation=3;
		}else if (strcmp(tokenPtr,"/")==0){
			operation=4;
		} else {
			if(operation==1){
				result+=atoi(tokenPtr);
			} else if (operation==2){
				result-=atoi(tokenPtr);
			}else if (operation==3){
				result*=atoi(tokenPtr);
			}else if (operation==4){
				result/=atoi(tokenPtr);
			}
		}
		tokenPtr = strtok(NULL, " ");
	}
	return result;
}


void insertUser(ListNodeUserPtr *headPtr, User u) { //pass by reference

	ListNodeUserPtr currentPtr = *headPtr, newNodePtr;


	newNodePtr = malloc(sizeof(ListNodeUser));
	newNodePtr->user = u;
	newNodePtr->nextPtr = NULL;


	if (*headPtr == NULL) {
		*headPtr = newNodePtr;
		return;
	}


	while (currentPtr->nextPtr != NULL) {
		currentPtr = currentPtr->nextPtr;
	}


	currentPtr->nextPtr = newNodePtr;
}

void insertMail(ListNodeMailPtr *headPtr, Mail m) { //pass by reference

	ListNodeMailPtr currentPtr = *headPtr, newNodePtr;


	newNodePtr = malloc(sizeof(ListNodeMail));
	newNodePtr->mail = m;
	newNodePtr->nextPtr = NULL;


	if (*headPtr == NULL) {
		*headPtr = newNodePtr;
		return;
	}


	while (currentPtr->nextPtr != NULL) {
		currentPtr = currentPtr->nextPtr;
	}

	// add the new node to the end
	currentPtr->nextPtr = newNodePtr;
}


void printUserList(ListNodeUserPtr headPtr) { //pass by value
	ListNodeUserPtr currentPtr = headPtr;

	if (currentPtr == NULL) printf("Empty list\n");
	else printf("USERS:\n");


	while (currentPtr != NULL) {
		printf("%s\n",&(currentPtr->user).eMail);
		currentPtr = currentPtr->nextPtr;

	}
	printf("\n");
}

void printMailList(ListNodeMailPtr headPtr) { //pass by value
	ListNodeMailPtr currentPtr = headPtr;

	if (currentPtr == NULL) printf("Empty list\n");
	else printf("MAILS:\n");

	while (currentPtr != NULL) {
		printf("Sender:%s\nReceiver:%s\nSubject:%d\nDate:%s\nMessage:%s\n", currentPtr->mail.sender,currentPtr->mail.receiverAddress,currentPtr->mail.subject,currentPtr->mail.date,currentPtr->mail.messageContent);
		currentPtr = currentPtr->nextPtr;
	}
	printf("\n");
}

User findUser(char *eMail, ListNodeUserPtr headPtr){ //pass by value
	ListNodeUserPtr currentPtr=headPtr;

	while(currentPtr!=NULL){
		if(strcmp(eMail,currentPtr->user.eMail)==0){
			return currentPtr->user;
		}
		currentPtr = currentPtr->nextPtr;
	}
	User nullUser={"NULL",NULL};
	return nullUser;
}

void printWithKeyword(char *key, ListNodeMailPtr headPtr){//pass by value

	ListNodeMailPtr currentPtr=headPtr;

	while(currentPtr!=NULL){
		/*if(strstr(currentPtr->mail.subject, key)!=NULL){
			printf("\nSender:%s\nReceiver:%s\nSubject:%s\nDate:%s\nMessage:%s\n\n",
					currentPtr->mail.sender,currentPtr->mail.receiverAddress,currentPtr->mail.subject,currentPtr->mail.date,currentPtr->mail.messageContent);

		}else*/ if(strstr(currentPtr->mail.sender, key)!=NULL){
			printf("\nSender:%s\nReceiver:%s\nSubject:%d\nDate:%s\nMessage:%s\n\n",
					currentPtr->mail.sender,currentPtr->mail.receiverAddress,currentPtr->mail.subject,currentPtr->mail.date,currentPtr->mail.messageContent);

		}else if(strstr(currentPtr->mail.receiverAddress, key)!=NULL){
			printf("\nSender:%s\nReceiver:%s\nSubject:%d\nDate:%s\nMessage:%s\n\n",
					currentPtr->mail.sender,currentPtr->mail.receiverAddress,currentPtr->mail.subject,currentPtr->mail.date,currentPtr->mail.messageContent);

		}
		currentPtr=currentPtr->nextPtr;
	}

}


void printLast5Mails(ListNodeMailPtr headPtr){//pass by value
	ListNodeMailPtr currentPtr=headPtr;
	int count=-5;
	while (currentPtr->nextPtr != NULL) {
		currentPtr = currentPtr->nextPtr;
		count++;
	}
	ListNodeMailPtr currentPtr2=headPtr;
	for(int i=0; i<count+1;i++){
		currentPtr2 = currentPtr2->nextPtr;
	}
	while (currentPtr2 != NULL) {
		printf("\nSender:%s\nReceiver:%s\nSubject:%d\nDate:%s\nMessage:%s\n\n",
				currentPtr2->mail.sender,currentPtr2->mail.receiverAddress,currentPtr2->mail.subject,currentPtr2->mail.date,currentPtr2->mail.messageContent);
		currentPtr2 = currentPtr2->nextPtr;
	}
}
//--------------------------------------MAIN----------------------------------//
int main() {

	setbuf(stdout, NULL);

	ListNodeUserPtr gmailHead = NULL;
	ListNodeUserPtr kuHead = NULL;
	ListNodeUserPtr yahooHead = NULL;
	ListNodeUserPtr hotmailHead = NULL;

	ListNodeMailPtr user1Head = NULL;
	ListNodeMailPtr user2Head = NULL;
	ListNodeMailPtr user3Head = NULL;
	ListNodeMailPtr user4Head = NULL;
	ListNodeMailPtr user5Head = NULL;
	ListNodeMailPtr user6Head = NULL;

	User user1={"user1@gmail.com", user1Head};
	User user2={"user2@ku.com", user2Head};
	User user3={"user3@yahoo.com", user3Head};
	User user4={"user4@hotmail.com", user4Head};
	User user5={"user5@ku.com", user5Head};
	User user6={"user6@gmail.com", user6Head};

	MailServer server1={"gmail",gmailHead};
	MailServer server2={"ku",kuHead};
	MailServer server3={"hotmail",yahooHead};
	MailServer server4={"yahoo",hotmailHead};

	insertUser(&gmailHead, user1);insertUser(&gmailHead, user6);
	insertUser(&kuHead, user2);insertUser(&kuHead, user5);
	insertUser(&yahooHead, user3);
	insertUser(&hotmailHead, user4);

	Mail mail1={"user2@ku.com", "user1@gmail.com", 1, "01.01.2021", "aB"};
	Mail mail2={"user5@ku.com", "user2@ku.com", 1, "02.01.2021", "cde"};
	Mail mail3={"user6@gmail.com", "user3@yahoo.com", 2, "03.01.2021", "f"};
	Mail mail4={"user2@ku.com", "user4@gmail.com", 3, "04.01.2021", "ghj"};
	Mail mail5={"user4@hotmail.com", "user5@yahoo.com", 5, "05.01.2021", "klm"};

	Mail mail6={"user3@yahoo.com", "user1@gmail.com", 8, "06.01.2021", "AB"};
	Mail mail7={"user4@hotmail.com", "user1@gmail.com", 13, "07.01.2021", "prs"};
	Mail mail8={"user5@gmail.com", "user1@gmail.com", 21, "08.01.2021", "uvy"};
	Mail mail9={"user3@yahoo.com", "user1@gmail.com", 34, "09.01.2021", "UK"};
	Mail mail10={"user3@yahoo.com", "user1@gmail.com", 55, "10.01.2021", "TR"};


	insertMail(&user1Head, mail1);
	insertMail(&user2Head, mail2);
	insertMail(&user3Head, mail3);
	insertMail(&user4Head, mail4);
	insertMail(&user5Head, mail5);

	insertMail(&user1Head, mail6);
	insertMail(&user1Head, mail7);
	insertMail(&user1Head, mail8);
	insertMail(&user1Head, mail9);
	insertMail(&user1Head, mail10);

	int choice;
	printf( "MENU:\n"
			"1-Send message.\n"
			"2-Display last 5 emails of an user.\n"
			"3-Display the emails in an inbox containing a given keyword in the header.\n"
			"4-Exit\n");
	scanf("%d", &choice);

	while(choice!=4){

		if(choice==1){
			Mail mail;
			printf("Sender: ");
			scanf("%s", mail.sender);
			printf("Receiver Address: ");
			scanf("%s", mail.receiverAddress);

			User foundUser;
			int userFound=1;
			if(strcmp( findUser(mail.receiverAddress, gmailHead).eMail, "NULL")!=0){
				foundUser=findUser(mail.receiverAddress, gmailHead);
			} else if (strcmp( findUser(mail.receiverAddress, kuHead).eMail, "NULL")!=0){
				foundUser=findUser(mail.receiverAddress, kuHead);
			} else if(strcmp( findUser(mail.receiverAddress, yahooHead).eMail, "NULL")!=0){
				foundUser=findUser(mail.receiverAddress, yahooHead);
			} else if(strcmp( findUser(mail.receiverAddress, hotmailHead).eMail, "NULL")!=0){
				foundUser=findUser(mail.receiverAddress, hotmailHead);
			} else {
				printf("User not found!\n\n");
				userFound=0;
			}

			if(userFound==1){
				char subj[100];
				printf("Subject: ");
				getchar();
				gets(subj);
				int correctness=correctSubject(subj);

				if(correctness==1){
					mail.subject=calculateSubject(subj);
					printf("Calculated Mail Subject: %d\n", mail.subject);
					printf("Date: ");
					gets(mail.date);
					printf("Encrypted Message Content: ");
					char encryptedMessage[100];
					gets(encryptedMessage);
					printf("Ceaser Chiper Shift (n): ");
					int n;
					scanf("%d", &n);
					strcpy(mail.messageContent,decrypt(encryptedMessage,n));


					//insertMail(&foundUser.inbox, mail);   It does not work, i could not understand why.
					if(strcmp(mail.receiverAddress,user1.eMail)==0){
						insertMail(&user1Head, mail);
					}else if(strcmp(mail.receiverAddress,user2.eMail)==0){
						insertMail(&user2Head, mail);
					}else if(strcmp(mail.receiverAddress,user3.eMail)==0){
						insertMail(&user3Head, mail);
					}else if(strcmp(mail.receiverAddress,user4.eMail)==0){
						insertMail(&user4Head, mail);
					}else if(strcmp(mail.receiverAddress,user5.eMail)==0){
						insertMail(&user5Head, mail);
					}else if(strcmp(mail.receiverAddress,user6.eMail)==0){
						insertMail(&user6Head, mail);
					}

					printf("\nMail is sent successfully:\nSender:%s\nReceiver:%s\nSubject:%d\nDate:%s\nMessage:%s\n",
												mail.sender,mail.receiverAddress,mail.subject,mail.date,mail.messageContent);
				} else {
					printf("Invalid expression!\n\n");
				}
			}


		} else if (choice==2){

			printf("Write the email of the user: ");
			char emailToPrint[100];
			scanf("%s", emailToPrint);
			if(strcmp(emailToPrint,user1.eMail)==0){
				printLast5Mails(user1Head);
			}else if(strcmp(emailToPrint,user2.eMail)==0){
				printLast5Mails(user2Head);
			}else if(strcmp(emailToPrint,user3.eMail)==0){
				printLast5Mails(user3Head);
			}else if(strcmp(emailToPrint,user4.eMail)==0){
				printLast5Mails(user4Head);
			}else if(strcmp(emailToPrint,user5.eMail)==0){
				printLast5Mails(user5Head);
			}else if(strcmp(emailToPrint,user6.eMail)==0){
				printLast5Mails(user6Head);
			} else {
				printf("User not found!");
			}

		} else if (choice==3){

			char keyword[100];
			printf("Enter keyword: ");
			getchar();
			gets(keyword);
			printf("Write the email of the user: ");
			char emailToPrint[100];
			scanf("%s", emailToPrint);
			printf("Mails:\n");
			if(strcmp(emailToPrint,user1.eMail)==0){
				printWithKeyword(keyword, user1Head);
			}else if(strcmp(emailToPrint,user2.eMail)==0){
				printWithKeyword(keyword, user2Head);
			}else if(strcmp(emailToPrint,user3.eMail)==0){
				printWithKeyword(keyword, user3Head);
			}else if(strcmp(emailToPrint,user4.eMail)==0){
				printWithKeyword(keyword, user4Head);
			}else if(strcmp(emailToPrint,user5.eMail)==0){
				printWithKeyword(keyword, user5Head);
			}else if(strcmp(emailToPrint,user6.eMail)==0){
				printWithKeyword(keyword, user6Head);
			} else {
				printf("User not found!");
			}

		} else {
			printf("Please enter 1, 2, 3 or 4.\n");
		}

		printf( "\n-------------------------------------------------------------------\n\n"
				"MENU:\n"
				"1-Send message\n"
				"2-Display last 5 mails of an user\n"
				"3-Display the emails in an inbox containing a given keyword in the header.\n"
				"4-Exit\n");
		scanf("%d", &choice);

	}

	printf("\nBye!");

	return 0;
}
