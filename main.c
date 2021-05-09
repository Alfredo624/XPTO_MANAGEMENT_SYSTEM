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
char row[101];
int i, j;
char choice = '\0';
FILE* file;
char curr_dir[MAX_BUF]; //Save the current location.
char buff[FILENAME_MAX]; // Create buffer to hold path.

// 				#Structures start here

//Employee and User structure
struct _employee{
	int id;
	char name[50];
	char username[50];
	char password[50];
	char function[50];
	char note[10000];
} employee, user_tmp;

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

// Worker CRUD
void InsertWorker(void);
void UpdateWorker(void);
void DeleteWorker(void);
void ListWorker(void);
void SearchWorker(void);
int ExistsWorker(char p[]);


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
void Exit(void);
void pressAnyKey(void);


// Program start running here.
int main() {
	login();
	return 0;
}

void login(){

	GetCurrentDir(buff, FILENAME_MAX);
	
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.
	//printf("%s\n", curr_dir); // Print current location.
	
	int flag = -1; // If flag = -1 => Account not found; If flag = 0 => Wrong password; Otherwise correct password.

	while(flag!=1){		
		fflush(stdin);
		clearScreen();
		header();
		footer();
		printf("\n\t\tUsuario: ");
		scanf("%s", employee.username);
		fflush(stdin);
		printf("\t\tSenha: ");
		readPassword(); // Read password using mask, COOL.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		if(strcmp(employee.username, "admin") == 0)
			flag = 1;

		while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
			int tmp1 = strcmp(user_tmp.username, employee.username); // Check match between users.
			int tmp2 = strcmp(user_tmp.password, employee.password); // Check math between passwords.

			if(tmp1 == 0 && tmp2 == 0) // When it's true, means that the credentials are correct.
			{
				flag = 1;
				break;
			}
		}

		fclose(file); // Close the file.

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
		}

		//printf("\nPress any KEY to continue.\n");
		if(flag<-3)
			printf("\n\nExcedeu o limite de tentativas.\n");
		
		if(choice == '2' || flag<-3){ 
			Exit();
		}
	}
	
	successful();

}

void mainMenu(){
	header();
	footer();
    printf("\n\t\t::: MENU PRINCIPAL :::");
    printf("\n\n\t\t[1] => Componentes:\n\t\t[2] => Posto de trabalho:\n\t\t[3] => Funcionarios:\n\t\t[4] => Operacoes:\n\t\t[5] => Empresas:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sai.\n\n\t\tOperacoes: ");
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
        case '6': login();
        break;
        case '7': Exit();
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
			employee.password[index] = key;
			index++;
		}
	}
	employee.password[index] = '\0'; // Determine the end of password.
	fflush(stdin);
}

void header(){
	system("cls");
	printf("\n");
	printf("\t\t\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb XPTO MANAGMENT SYSTEM \xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\xdb\n");
}


void footer(){
	time_t t;
	time(&t);
	printf("\n\t\tData e tempo: %s\n",ctime(&t));
}

void Exit(){
	printf("\n\t\t Ate mais! Obrigado.\n");
	exit(0);
}

void successful(){
	printf("\n\n\t\tUsuario logado com sucesso!\n\n");
	char u[20]; // It's an auxiliary variable used to print username.
	strcpy(u, employee.username);
	u[0] = toupper(u[0]);
	printf("\t\t%s, seja bem-vindo ao XPTO MANAGEMENT SYSTEM! \n\t\tSinta-te a vontade usando o sistema ...\n\n", u);
	
	pressAnyKey();
	mainMenu();
}

void Components(){
	header();
    printf("\n\t\t::: MENU COMPONENTES :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Sair.\n\n\t\tOperacao: ");
	
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
        case '6': Exit();
        break;
        default: Components();
        break;
    }
}

void WorkOffice(){
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
        case '6': Exit();
        break;
        default: WorkOffice();
        break;
    }
}

void Worker(){
	header();
	footer();
    printf("\n\t\t::: MENU FUNCIONARIOS :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar:\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	
	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': InsertWorker();
        break;
        case '2': UpdateWorker();
        break;
        case '3': DeleteWorker();
        break;
        case '4': ListWorker();
        break;
        case '5': SearchWorker();
        break;
        case '6': mainMenu();
        break;
        case '7': exit(0);
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

void InsertWorker(){
	header();
	footer();
	
	printf("\n\t\t:: INSERCAO DE FUNCIONARIO :::");
	printf("\n\n\t\tNome: ");
	gets(user_tmp.name); fflush(stdin);
	printf("\t\tNome de usuario: ");
	scanf("%s", user_tmp.username); fflush(stdin);

	while(ExistsWorker(user_tmp.username) == 1){
		printf("\n\t\tUsuario ja existente!\n");
		printf("\t\tNome de usuario: ");
		scanf("%s", user_tmp.username); fflush(stdin);
	}
	
	printf("\n\t\tFuncoes: \n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/functions.dat"; // Define directory.

	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.
	
	char read[50];
	char functions[50][100]; i = 1;
	while(fscanf(file, "%s", read) != EOF){
		strcpy(functions[i], read);
		printf("\t\t => [%d] - %s\n", i, functions[i]);;
		i++;
	}

	fclose(file);

	int option = i;

	while(option<=0 || option>=i){
		printf("\n\t\tOpcao: ");
		scanf("%d", &option); fflush(stdin);

		if(option<0 || option>=i){
			printf("\t\tOpcao invalida!\n");
		}
	} 

	strcpy(user_tmp.function, functions[option]);
	strcpy(user_tmp.password, "12345");

	printf("\n\t\tNota: ");
	gets(user_tmp.note); fflush(stdin);

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	strcpy(path, "/data/employee.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		Worker();
	}

	if(fwrite(&user_tmp, sizeof(user_tmp), 1, file))
		printf("\n\t\tFuncionario inserido com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		Worker();
	}

	fclose(file);

	pressAnyKey();

	Worker();
}

void UpdateWorker(){
	header();
	footer();
	
	printf("\n\t\t:: ATUALIZACAO DE FUNCIONARIO :::\n");
	printf("\n\t\tNome de usuario: ");
	scanf("%s", user_tmp.username); fflush(stdin);

	if(ExistsWorker(user_tmp.username) == 0){
		puts("\n\n\t\tUsuario inexistente!\n");
		printf("\n\t\tTentar novamente ? Yes/No: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'Y')
			UpdateWorker();
		else Worker();
	}
	else
	{	
		printf("\n\n\t\tNome: ");
		gets(user_tmp.name); fflush(stdin);

		printf("\n\t\tFuncoes: \n");

		GetCurrentDir(buff, FILENAME_MAX);
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "/data/functions.dat"; // Define directory.

		strcat(curr_dir, path); // Make the mix.
		
		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.
		
		char read[50];
		char functions[50][100]; i = 1;
		while(fscanf(file, "%s", read) != EOF){
			strcpy(functions[i], read);
			printf("\t\t => [%d] - %s\n", i, functions[i]);;
			i++;
		}

		fclose(file);

		int option = i;

		while(option<=0 || option>=i){
			printf("\n\t\tOpcao: ");
			scanf("%d", &option); fflush(stdin);

			if(option<0 || option>=i){
				printf("\t\tOpcao invalida!\n");
			}
		} 

		strcpy(user_tmp.function, functions[option]);
		strcpy(user_tmp.password, "12345");

		printf("\n\t\tNota: ");
		gets(user_tmp.note); fflush(stdin);

		GetCurrentDir(buff, FILENAME_MAX);
		strcpy(curr_dir, buff); 
		strcpy(path, "/data/employee.bin"); // Define directory.
		strcat(curr_dir, path); // Make the mix.
		
		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "a");
		else
			file = fopen(curr_dir, "a"); // Open the file.

		if(file == NULL){
			printf("Problemas na abertura do ficheiro.\n\n");
			Worker();
		}

		if(fwrite(&user_tmp, sizeof(user_tmp), 1, file))
			printf("\n\t\tFuncionario inserido com sucesso!\n\n");
		else {
			printf("Erro de insercao\n");
			Worker();
		}

		fclose(file);
	}

	pressAnyKey();
	Worker();
}

void DeleteWorker(){

}

int ExistsWorker(char p[]){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	struct _employee user_tmp;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
	
		if(strcmp(p, user_tmp.username) == 0)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}

void ListWorker(){
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE FUNCIONARIOS :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
		printf("\n\t\tNome: %s\n\t\tNome de Usuario: %s\n\t\tSenha: ****\n\t\tFuncao: %s\n\t\tNota: %s\n", 
			user_tmp.name, user_tmp.username, user_tmp.function, user_tmp.note);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	Worker();
}

void SearchWorker(){

}

void pressAnyKey(){
	printf("\t\tPressione qualquer tecla para continuar ... ");
	getch();
}

// Sub-menus items
void Insert(){

}

void Update(){

}

void Delete(){

}

void List(){

}

void Search(){

}
