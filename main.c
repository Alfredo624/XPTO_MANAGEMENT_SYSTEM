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

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
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

void login(){
	header();
	footer();

	FILE* file;
	char curr_dir[MAX_BUF]; //Save the current location.
	
	char buff[FILENAME_MAX]; // Create buffer to hold path.
	GetCurrentDir(buff, FILENAME_MAX);
	
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/employee_user.dat"; // Define directory.

	strcat(curr_dir, path); // Make the mix.
	printf("%s\n", curr_dir); // Print current location.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.
	
	
	char user_data[50], password_data[50];
	int flag = -1; // If flag = -1 => Account not found; If flag = 0 => Wrong password; Otherwise correct password.

	while(flag!=1){		
		printf("Username: ");
		scanf("%s", username);
		fflush(stdin);
		printf("Password: ");
		scanf("%s", password);
		fflush(stdin);

		while(fgets(row, sizeof(row), file)){ // Search for credentials.
		
			fflush(stdin);
			i = j = 0;
			while(row[i] != ' ') // 32 is the ASCII code for "space". Did you get?
			{
				user_data[j] = row[i];
				i++;
				j++;
			}
			
			j = 0; i++;
			while(row[i+1] != '\0'){
				password_data[j] = row[i];
				i++;
				j++;
			}

			int tmp1 = strcmp(user_data, username); // Check match between users.
			int tmp2 = strcmp(password_data, password); // Check math between passwords.

			if(tmp1 == 0 && tmp2 == 0) // When it's true, means that the credentials are correct.
				flag = 1;
			
			memset(user_data, '\0', sizeof(user_data));
			memset(password_data, '\0', sizeof(password_data));
		}

		if(flag == -1)
			printf("\nUser not found or wrong password.\n");
		 else
			successful();

		printf("\nPress ENTER.\n");	
		getchar();
		
		memset(username, '\0', sizeof(username));
		memset(password, '\0', sizeof(password));
	}

	fclose(file); // Close the file.
}

void menu(){

}

// Program start running here
int main() {
	login();
	getchar();
	return 0;
}

void errorMessage(void){
	printf("Failed!\n");
}

void clearScreen(){

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
	printf("\nSuccessful!\n");
}