#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <windows.h>

// Constants declarations
#ifndef MAX_BUF
#define MAX_BUF 200
#endif

#ifdef WINDOWS // It's for Windows SO
#include <direct.h>
#define GetCurrentDir _getcwd
#else // It's for Linux SO
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

// Global variables come here
char username[50], password[50];
char row[101];
int i, j;

// 				#Structures start here

//Employee and User structure
struct employee{
	int id;
	char name[20];
	char user_name[20];
	char password[20];
	char function[20];
	char note[50];
};

//Components structure
struct components{
	int id;
	char name[20];
	char serie_number[20];
	char date_taken[20];
	int guarantee;
	int id_supplier;
	int id_maker;
	int type;
	int status;
	int id_work_office;
	char observation[1000];
};

//Work Office structure
struct work_office{
	int id;
	char name[20];
	char place[30];
	int section;
	char note[50];
	int id_employee;
};

//Operation structure
struct operations{
	int id;
	int id_internal_doc;
	int id_external_doc;
	int id_work_office;
	int id_component;
	int id_office;
	int type;
	char date_out[20];
	char date_int[20];
	char date_prevision_in[20];
	int id_worker;
	char date[20];
	float money;
	char observation[1000];
};

// Company structure
struct company{
	int id;
	char name[20];
	char type[20];
	char contact[30];
};

// 					#Structures end here

// Functions definitions
void login(void);
void menu(void);
void errorMessage(void);
void clearScreen(void);
void footer(void);
void header(void);
void successful(void);
void readPassword(void);

void login(){

	FILE* file;
	char curr_dir[MAX_BUF]; //Save the current location.
	
	char buff[FILENAME_MAX]; // Create buffer to hold path.
	GetCurrentDir(buff, FILENAME_MAX);
	
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/employee_user.dat"; // Define directory.

	strcat(curr_dir, path); // Make the mix.
	//printf("%s\n", curr_dir); // Print current location.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.
	
	
	char user_data[50], password_data[50];
	int flag = -1; // If flag = -1 => Account not found; If flag = 0 => Wrong password; Otherwise correct password.

	while(flag!=1){		
		clearScreen();
		header();
		footer();

		printf("\nUsername: ");
		scanf("%s", username);
		fflush(stdin);
		printf("Password: ");
		readPassword(); // Read password using mask, COOL.

		while(fscanf(file, "%s %s", &user_data, &password_data)!=EOF){ // Search for credentials.
		
			int tmp1 = strcmp(user_data, username); // Check match between users.
			int tmp2 = strcmp(password_data, password); // Check math between passwords.

			if(tmp1 == 0 && tmp2 == 0) // When it's true, means that the credentials are correct.
				flag = 1;
		}

		char choice = ' ';
		if(flag != 1){
			printf("\n\nSorry! Login unsuccessful.\n");
			do{	
				printf("\nPress:\n[1] - Try again;\n[2] - Exit.\n");
				printf("\nChoice: ");
				scanf("%c", &choice);
				fflush(stdin);
			} while(choice!= '1' && choice != '2');
			
			flag--; // Decrease each time is entered wrong password. Once tried 3 times, the system is exited!
		}

		//printf("\nPress any KEY to continue.\n");
		if(flag<-3)
			printf("\n\nYou have exceeded the number of attempts.\n");
		
		if(choice == '2' || flag<-3){ 
			printf("\nSee you later! Thank you.\n");
			exit(0);
		}
	}
	
	successful();

	fclose(file); // Close the file.
}

void menu(){

}

// Program start running here.
int main() {
	login();
	return 0;
}

void errorMessage(void){
	printf("Failed!\n");
}

void clearScreen(){
	system("cls");
}

// Read password using mask, COOL.
void readPassword(){
	char key = '\0';
	int index = 0;
	
	while(key != 13){
		key = getch();

		if(key != 13 && key != 8){
			putchar('*');
			password[index] = key;
			index++;
		}
	}
	password[index] = '\0'; // Determine the end of password.
	fflush(stdin);
}

void header(){
	printf("\n");
	printf("\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb XPTO MANAGMENT SYSYTEM \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
}


void footer(){
	time_t t;
	time(&t);
	printf("\n\t\tDate and time: %s\n",ctime(&t));
}

void successful(){
	printf("\n\nLogin successful!\n\n");
	printf("%s, WELCOME to XPTO MANAGEMENT SYSTEM! Feel free using the system ...\n", username);
}