#define _GNU_SOURCE
#include <stdio.h>
#include <ctype.h>
#include <locale.h>
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
char choice = '\0';

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

// Menu items
void Components(void);
void WorkOffice(void);
void Worker(void);
void Operations(void);
void Company(void);

// Sub-menus items
void Insert(void);
void Update(void);
void Delete(void);
void List(void);
void Search(void);

// Functions definitions
void login(void);
void menu(void);
void errorMessage(void);
void clearScreen(void);
void footer(void);
void header(void);
void successful(void);
void readPassword(void);
void fordelay(void);


// Program start running here.
int main() {
	login();
	return 0;
}

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
		printf("\n\t\tUsuario: ");
		scanf("%s", username);
		fflush(stdin);
		printf("\t\tSenha: ");
		readPassword(); // Read password using mask, COOL.

		while(fscanf(file, "%s %s", &user_data, &password_data)!=EOF){ // Search for credentials.
		
			int tmp1 = strcmp(user_data, username); // Check match between users.
			int tmp2 = strcmp(password_data, password); // Check math between passwords.

			if(tmp1 == 0 && tmp2 == 0) // When it's true, means that the credentials are correct.
				flag = 1;
		}

		char choice = '\0';
		if(flag != 1){
			printf("\n\n\t\tDesculpa! Credenciais incorrectas.\n");
			do{	
				printf("\n\t\tPressione:\n\t\t[1] - Tentar novamente;\n\t\t[2] - Sair.\n");
				printf("\n\t\tOpcao: ");
				scanf("%c", &choice);
				fflush(stdin);
			} while(choice!= '1' && choice != '2');
			
			flag--; // Decrease each time is entered wrong password. Once tried 3 times, the system is exited!
				
			// Reset variables
			memset(username, '\0', sizeof(username));
			memset(password, '\0', sizeof(password));
		}

		//printf("\nPress any KEY to continue.\n");
		if(flag<-3)
			printf("\n\nExcedeu o limite de tentativas.\n");
		
		if(choice == '2' || flag<-3){ 
			printf("\nAte mais! Obrigado.\n");
			exit(0);
		}
	}
	
	successful();

	fclose(file); // Close the file.
}

void mainMenu(){
    system("cls");
	header();
    printf("\n\t\t::: MENU PRINCIPAL :::");
    printf("\n\n\t\t[1] => Componentes:\n\t\t[2] => Posto de trabalho:\n\t\t[3] => Funcionarios:\n\t\t[4] => Operacoes:\n\t\t[5] => Empresas:\n\t\t[6] => Sai.\n\n\t\tOperacoes: ");
    scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': Components();
        break;
        case '2': WorkOffice();
        break;
        case '3': Worker();
        break;
        case '4': Operations();
        break;
        case '5': Company();
        break;
        case '6': exit(0);
        break;
        default: mainMenu();
        break;
    }
}


void errorMessage(void){
	printf("\t\tFalha!\n");
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
	printf("\n\t\tData e tempo: %s\n",ctime(&t));
}

void successful(){
	printf("\n\n\t\tUsuario logado com sucesso!\n\n");
	username[0] = toupper(username[0]);
	printf("\t\t%s, seja bem-vindo ao XPTO MANAGEMENT SYSTEM! \n\t\tSinta-te a vontade usando o sistema ...\n\n", username);
	printf("\t\tPressione qualquer tecla para continuar ... ");
	getch();
	mainMenu();
}

void Components(){
	system("cls");
	header();
    printf("\n\t\t::: MENU COMPONENTES :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Sair.\n\n\t\tOperacoes: ");
	
    switch(choice)
    {
        case '1': Insert();
        break;
        case '2': Update();
        break;
        case '3': Delete();
        break;
        case '4': List();
        break;
        case '5': Search();
        break;
        case '6': exit(0);
        break;
        default: Components();
        break;
    }
}

void WorkOffice(){
	system("cls");
	header();
    printf("\n\t\t::: MENU POSTOS DE TRABALHOS :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Sair.\n\n\t\tOperacoes: ");
	
    switch(choice)
    {
        case '1': Insert();
        break;
        case '2': Update();
        break;
        case '3': Delete();
        break;
        case '4': List();
        break;
        case '5': Search();
        break;
        case '6': exit(0);
        break;
        default: WorkOffice();
        break;
    }
}

void Worker(){
	system("cls");
	header();
    printf("\n\t\t::: MENU FUNCIONARIOS :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Sair.\n\n\t\tOperacoes: ");
	
    switch(choice)
    {
        case '1': Insert();
        break;
        case '2': Update();
        break;
        case '3': Delete();
        break;
        case '4': List();
        break;
        case '5': Search();
        break;
        case '6': exit(0);
        break;
        default: Worker();
        break;
    }
}

void Operations(){
	system("cls");
	header();
    printf("\n\t\t:: MENU OPERACOES :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Sair.\n\n\t\tOperacoes: ");

	
    switch(choice)
    {
        case '1': Insert();
        break;
        case '2': Update();
        break;
        case '3': Delete();
        break;
        case '4': List();
        break;
        case '5': Search();
        break;
        case '6': exit(0);
        break;
        default: Operations();
        break;
    }
}

void Company(){
	system("cls");
	header();
    printf("\n\t\t::: MENU EMPRESAS :::");    
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Sair:\n\n\t\tOperacoes: ");

	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': Insert();
        break;
        case '2': Update();
        break;
        case '3': Delete();
        break;
        case '4': List();
        break;
        case '5': Search();
        break;
        case '6': exit(0);
        break;
        default: Company();
        break;
    }
}