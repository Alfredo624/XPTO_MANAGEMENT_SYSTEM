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

#define MAX_EMPLOYEES 100
#define MAX_COMPONENTS 100
#define MAX_WORKS 100
#define MAX_WORK_OFFICE 100
#define MAX_OPERATIONS 100

// Global variables come here
char row[101];
int i, j;
char choice = '\0';
FILE* file, * new_file;
char curr_dir[MAX_BUF]; //Save the current location.
char buff[FILENAME_MAX]; // Create buffer to hold path.

// 				#Structures start here

//Employee and User structure
struct employee{
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
} component_tmp;

//Work Office structure
struct work_office{
	int id;
	char name[20];
	char place[30];
	int section;
	char note[50];
	int id_employee;
} work_office_tmp;

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
} operations_tmp;

// Company structure
struct company{
	int id;
	char name[20];
	char type[20];
	char contact[30];
} company_tmp;

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

//WorkOffice CRUD
void InsertWorkOffice(void);
void UpdateWorkOffice(void);
void DeleteWorkOffice(void);
void ListWorkOffice(void);
void SearchWorkOffice(void);

//Component CRUD
void InsertComponents(void);
void UpdateComponents(void);
void DeleteComponents(void);
void ListComponents(void);
void SearchComponents(void);
void SubstituteByWorkOffice(void);

//Operation CRUD
void InsertOperations(void);
void UpdateOperations(void);
void DeleteOperations(void);
void ListOperations(void);
void SearchOperations(void);

//Company CRUD
void InsertCompany(void);
void UpdateCompany(void);
void DeleteCompany(void);
void ListCompany(void);
void SearchCompany(void);

// Function definitions
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
int searchWildCard(char text[], char key[], int n, int m);
int searchWildCard_v2(char * frist, char * second);


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
    printf("\n\n\t\t[1] => Componentes:\n\t\t[2] => Posto de trabalho:\n\t\t[3] => Funcionarios:\n\t\t[4] => Operacoes:\n\t\t[5] => Empresas:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
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
	footer();
    printf("\n\t\t::: MENU COMPONENTES :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Substituir entre postos de trabalho:\n\t\t[5] => Listar:\n\t\t[6] => Pesquisar:\n\t\t[7] => Voltar <=::\n\t\t[8] => Sair.\n\n\t\tOperacao: ");

	scanf("%c", &choice); fflush(stdin);
	
    switch(choice)
    {
        case '1': InsertComponents();
        break;
        case '2': UpdateComponents();
        break;
        case '3': DeleteComponents();
        break;
        case '4': SubstituteByWorkOffice();
        break;
        case '5': ListComponents();
        break;
        case '6': SearchComponents();
        break;
        case '7': mainMenu();
        break;
        case '8': Exit();
        break;
        default: Components();
        break;
    }
}

void WorkOffice(){
	header();
	footer();
    printf("\n\t\t::: MENU POSTOS DE TRABALHOS :::");
    printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	
	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': InsertWorkOffice();
        break;
        case '2': UpdateWorkOffice();
        break;
        case '3': DeleteWorkOffice();
        break;
        case '4': ListWorkOffice();
        break;
        case '5': SearchWorkOffice();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
        break;
        default: WorkOffice();
        break;
    }
}

void Worker(){
	header();
	footer();
    printf("\n\t\t::: MENU FUNCIONARIOS :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	
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
        case '7': Exit();
        break;
        default: Worker();
        break;
    }
}

void Operations(){
	header();
	footer();
    printf("\n\t\t:: MENU OPERACOES :::");
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair.\n\n\t\tOperacoes: ");
	scanf("%c", &choice); fflush(stdin);

	
    switch(choice)
    {
        case '1': InsertOperations();
        break;
        case '2': UpdateOperations();
        break;
        case '3': DeleteOperations();
        break;
        case '4': ListOperations();
        break;
        case '5': SearchOperations();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
        break;
        default: Operations();
        break;
    }
}

void Company(){
	header();
	footer();
    printf("\n\t\t::: MENU EMPRESAS :::");    
	printf("\n\n\t\t[1] => Inserir:\n\t\t[2] => Alterar:\n\t\t[3] => Apagar:\n\t\t[4] => Listar:\n\t\t[5] => Pesquisar:\n\t\t[6] => Voltar <=::\n\t\t[7] => Sair:\n\n\t\tOperacoes: ");

	scanf("%c", &choice); fflush(stdin);

    switch(choice)
    {
        case '1': InsertCompany();
        break;
        case '2': UpdateCompany();
        break;
        case '3': DeleteCompany();
        break;
        case '4': ListCompany();
        break;
        case '5': SearchCompany();
        break;
        case '6': mainMenu();
        break;
        case '7': Exit();
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
		
		printf("\n\n\t\tUsuario inexistente!\n");
		printf("\n\t\tTentar novamente ? Yes/No: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'Y')
			UpdateWorker();
		else Worker();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "/data/employee.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct employee all_employees[MAX_EMPLOYEES];
		fread(&all_employees, sizeof(struct employee), MAX_EMPLOYEES, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_EMPLOYEES; i++){
			if(strcmp(all_employees[i].username, user_tmp.username) == 0){
							
				printf("\n\n\t\tNome: ");
				gets(all_employees[i].name); fflush(stdin);

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

				strcpy(all_employees[i].function, functions[option]);
				printf("\n\t\tSenha: ");
				scanf("%s", all_employees[i].password); fflush(stdin);

				printf("\n\t\tNota: ");
				gets( all_employees[i].note); fflush(stdin);

				break;
			}

			if(all_employees[i].username[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "/data/employee.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_employees, sizeof(employee), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Worker();
}

void DeleteWorker(){
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE FUNCIONARIO :::\n");
	printf("\n\t\tNome de usuario: ");
	scanf("%s", user_tmp.username); fflush(stdin);

	if(ExistsWorker(user_tmp.username) == 0){
		
		printf("\n\n\t\tUsuario inexistente!\n");
		printf("\n\t\tTentar novamente ? Yes/No: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'Y')
			DeleteWorker();
		else Worker();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Worker();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "/data/employee.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct employee all_employees[MAX_EMPLOYEES];
		fread(&all_employees, sizeof(struct employee), MAX_EMPLOYEES, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_EMPLOYEES; i++){
			if(strcmp(all_employees[i].username, user_tmp.username) == 0){	
				strcpy(all_employees[i].name, "");
				strcpy(all_employees[i].username, "");
				strcpy(all_employees[i].password, "");
				strcpy(all_employees[i].function, "");
				strcpy(all_employees[i].note, "");
			}

			if(all_employees[i].username[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "/data/employee.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_employees, sizeof(employee), cont + 1, file);
		printf("\n\t\tFuncionario apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Worker();
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

	struct employee user_tmp;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
	
		if(strcmp(p, user_tmp.username) == 0)
			flag = 1;
	}

	fclose(file); // Close the file.´

	return flag;
}


int ExistsComponent(int id){
	int flag = 0;

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/components.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct employee component_tmp;
	while(fread(&component_tmp, sizeof(component_tmp), 1, file) == 1){ // Search for credentials.
	
		if(id == component_tmp.id)
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
		if(user_tmp.username[0] == '\0')
			continue;
		
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
	header();
	footer();
	
	printf("\n\t\t:: PESQUISA DE FUNCIONARIO :::\n");
	printf("\n\t\tPesquisar: ");
	char key[100];
	scanf("%s", key); fflush(stdin);
	
	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/employee.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	struct employee user_tmp;
	while(fread(&user_tmp, sizeof(user_tmp), 1, file) == 1){ // Search for credentials.
		// Verify here

		int tmp1 = strcmp(key, user_tmp.username);
		int tmp2 = compare(key, user_tmp.username); // Uses WILDCARDS

		//printf("%d %d\n", tmp1, tmp2);

		if(tmp1 == 0 || tmp2 == 1){
			//Print here
			printf("\n\t\tNome: %s\n\t\tNome de Usuario: %s\n\t\tSenha: ****\n\t\tFuncao: %s\n\t\tNota: %s\n", 
				user_tmp.name, user_tmp.username, user_tmp.function, user_tmp.note);
		}
	}
	fclose(file); // Close the file.

	printf("\n");
	pressAnyKey();
	Worker();
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

// == Components functions == //
void InsertComponents(void){

	header();
	footer();

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/components.bin"; // Define directory.
	
	printf("\n\t\t:: INSERCAO DE COMPONENTE :::");
	printf("\n\n\t\tID: ");
	scanf("%d", &company_tmp.id); fflush(stdin);

	printf("\t\tNome: ");
	gets(component_tmp.name); fflush(stdin);

	printf("\t\tNumero de serie: ");
	scanf("%s", component_tmp.serie_number); fflush(stdin);

	printf("\t\tData de aquisicao: ");
	scanf("%s", component_tmp.date_taken); fflush(stdin);

	printf("\t\tDias de garantia: ");
	scanf("%d", &component_tmp.guarantee); fflush(stdin);

	printf("\t\tID do fornecedor: ");
	scanf("%d", &component_tmp.id_supplier); fflush(stdin);

	printf("\t\tID do Fabricante: ");
	scanf("%d", &component_tmp.id_maker); fflush(stdin);
	
	printf("\t\tTipo de componente: ");
	scanf("%d", &component_tmp.type); fflush(stdin);
	
	printf("\t\tCondicao: ");
	scanf("%d", &component_tmp.status); fflush(stdin);

	printf("\t\tID do Posto de Trabalho: ");
	scanf("%d", &component_tmp.id_work_office); fflush(stdin);

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	strcpy(path, "/data/components.bin"); // Define directory.
	strcat(curr_dir, path); // Make the mix.
	
	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "a");
	else
		file = fopen(curr_dir, "a"); // Open the file.

	if(file == NULL){
		printf("Problemas na abertura do ficheiro.\n\n");
		Components();
	}

	if(fwrite(&component_tmp, sizeof(component_tmp), 1, file))
		printf("\n\t\tFuncionario inserido com sucesso!\n\n");
	else {
		printf("Erro de insercao\n");
		Components();
	}

	fclose(file);

	pressAnyKey();
	Components();
}

void UpdateComponents(void){
	header();
	footer();
	
	printf("\n\t\t:: ATUALIZACAO DE COMPONENTE :::\n");
	printf("\n\t\tId do Componente: ");
	scanf("%s", component_tmp.id); fflush(stdin);

	if(ExistsComponent(component_tmp.id) == 0){
		
		printf("\n\n\t\tComponente inexistente!\n");
		printf("\n\t\tTentar novamente ? Yes/No: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'Y')
			UpdateWorker();
		else Worker();
	}
	else{	
		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "/data/components.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct components all_components[MAX_COMPONENTS];
		fread(&all_components, sizeof(struct components), MAX_EMPLOYEES, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_EMPLOYEES; i++){
			if(all_components[i].id == component_tmp.id){
							
				printf("\t\tNome: ");
				gets(component_tmp.name); fflush(stdin);

				printf("\t\tNumero de serie: ");
				scanf("%s", component_tmp.serie_number); fflush(stdin);

				printf("\t\tData de aquisicao: ");
				scanf("%s", component_tmp.date_taken); fflush(stdin);

				printf("\t\tDias de garantia: ");
				scanf("%d", &component_tmp.guarantee); fflush(stdin);

				printf("\t\tID do fornecedor: ");
				scanf("%d", &component_tmp.id_supplier); fflush(stdin);

				printf("\t\tID do Fabricante: ");
				scanf("%d", &component_tmp.id_maker); fflush(stdin);

				printf("\t\tTipo de componente: ");
				scanf("%d", &component_tmp.type); fflush(stdin);

				printf("\t\tCondicao: ");
				scanf("%d", &component_tmp.status); fflush(stdin);

				printf("\t\tID do Posto de Trabalho: ");
				scanf("%d", &component_tmp.id_work_office); fflush(stdin);

				break;
			}

			if(all_components[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		
		strcpy(curr_dir, buff); 
		strcpy(path, "/data/components.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_components, sizeof(component_tmp), cont + 1, file);
		printf("\n\t\tDados actualizados com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Worker();
}

void DeleteComponents(void){
	
	header();
	footer();
	
	printf("\n\t\t:: DELECAO DE COMPONENTES :::\n");
	printf("\n\t\tId do Componente: ");
	scanf("%d", &component_tmp.id); fflush(stdin);

	if(ExistsComponent(component_tmp.id) == 0){
		
		printf("\n\n\t\tComponente inexistente!\n");
		printf("\n\t\tTentar novamente ? Yes/No: ");
		scanf("%c", &choice);
		fflush(stdin);

		choice = toupper(choice);

		if(choice == 'Y')
			DeleteComponents();
		else Components();
	}
	else{	

		printf("\n\t\tTem a certeza que realmente deseja deletar? Sim/Nao: ");
		char option;
		scanf("%c", &option);

		option = toupper(option);

		if(option == 'N')
			Components();

		strcpy(curr_dir, buff); 
		char path[MAX_BUF] = "/data/components.bin"; // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "r"); // Open the file.

		struct components all_components[MAX_EMPLOYEES];
		fread(&all_components, sizeof(struct components), MAX_COMPONENTS, file);
		
		int cont = 0;
		for ( i = 0; i<MAX_COMPONENTS; i++){
			if(all_components[i].id = components_tmp.id){	
				strcpy(all_components[i].name, "");
			}

			if(all_employees[i].name[0] != '\0')
				cont++;
		}

		fclose(file); // Close the file.

		strcpy(curr_dir, buff); 
		strcpy(path, "/data/employee.bin"); // Define directory.

		strcat(curr_dir, path); // Make the mix.

		if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
			fopen(curr_dir, "w");
		else
			file = fopen(curr_dir, "w"); // Open the file.

		fwrite(&all_employees, sizeof(employee), cont + 1, file);
		printf("\n\t\tFuncionario apagado com sucesso!\n\n");
		
		fclose(file);
	}

	pressAnyKey();
	Worker();
}

void ListComponents(void){
	
	header();
	footer();
	
	printf("\n\t\t:: LISTAGEM DE COMPONENTES :::\n");

	GetCurrentDir(buff, FILENAME_MAX);
	strcpy(curr_dir, buff); 
	char path[MAX_BUF] = "/data/components.bin"; // Define directory.

	strcat(curr_dir, path); // Make the mix.

	if(fopen(curr_dir, "r") == NULL) // Verify if the file exists.
		fopen(curr_dir, "w");
	else
		file = fopen(curr_dir, "r"); // Open the file.

	int count = 1;
	while(fread(&component_tmp, sizeof(component_tmp), 1, file) == 1){ // Search for credentials.
		if(component_tmp.name[0] == '\0')
			continue;
		
		printf("\n\t\tId: %d\n\t\tDesignacao: %s\n\t\tNumero de Serie: %s\n\t\tData de aquisicao: %s\n\t\tDias de Garantia: %d\n\t\tId do Fornecedor: %d\n\t\tId do Fabricador: %d\n\t\tTipo: %d\n\t\tCondicao: %d\n\t\tId do Posto de Trabalho: %d\n", 
			component_tmp.id, component_tmp.name, component_tmp.serie_number, component_tmp.date_taken, component_tmp.guarantee, component_tmp.id_supplier, component_tmp.id_maker, component_tmp.type, component_tmp.status, component_tmp.id_work_office);
		count++;
	}

	fclose(file); // Close the file.

	printf("\n\n\t\tTOTAL =  %d\n\n", count - 1);
	pressAnyKey();
	Components();
}

void SearchComponents(void){

}

void SubstituteByWorkOffice(){

}

// == WorkOffice functions == //
void InsertWorkOffice(void){

}

void UpdateWorkOffice(void){

}

void DeleteWorkOffice(void){

}

void ListWorkOffice(void){

}

void SearchWorkOffice(void){

}

// Operations functions
void InsertOperations(void){

}

void UpdateOperations(void){

}

void DeleteOperations(void){

}

void ListOperations(void){

}

void SearchOperations(void){

}

// == Company functions == //
void InsertCompany(void){

}

void UpdateCompany(void){

}

void DeleteCompany(void){

}

void ListCompany(void){

}

void SearchCompany(void){

}

int searchWildCard(char text[], char key[], int n, int m){
	// Code goes here
	// Empty text can only math with empty key
	if(m == 0)
		return (n == 0);

	//Lookup table for storing results of sub-problems
	int dp[n+1][m+1];
	
	//Initialize lookup table to to false
	memset(dp, 0, sizeof(dp));

	//Empty text can math with empty key
	dp[0][0] = 1;

	//Only '*' can math with empty key
	for (j = 1; j<=m; j++)
		if(key[j-1] == '*')
			dp[0][j] = dp[0][j-1];

	//Fill the table in bottom-up manner
	for (i = 1; i<=n; i++)
		for (j = 1; j<=m; j++)
			// There are two cases if we find a '*'
			// a) We ignore '*' character and move
			// 	to next character in the text,
			// i.e., '*' indicates an empty sequence.
			// b) '*' character matches with ith character in key

 			if(key[j-1] == '*')
				dp[i][j] = dp[i][j-1] || dp[i-1][j];
			else 
				if(key[j-1] == '?' || text[i-1] == key[j-1])
					dp[i][j] = dp[i-1][j-1];

			// If characters don't match
			else 
				dp[i][j] = 0;

	return dp[n][m];
}


int searchWildCard_v2(char *first, char * second)
{
    // If we reach at the end of both strings, we are done
    if (*first == '\0' && *second == '\0')
        return 1;
  
    // Make sure that the characters after '*' are present
    // in second string. This function assumes that the first
    // string will not contain two consecutive '*'
    if (*first == '*' && *(first+1) != '\0' && *second == '\0')
        return 0;
  
    // If the first string contains '?', or current characters
    // of both strings match
    if (*first == '?' || *first == *second)
        return searchWildCard_v2(first+1, second+1);
  
    // If there is *, then there are two possibilities
    // a) We consider current character of second string
    // b) We ignore current character of second string.
    if (*first == '*')
        return searchWildCard_v2(first+1, second) || searchWildCard_v2(first, second+1);
        
    return 0;
}
  
// A function to run test cases
int compare(char *first, char *second)
{  searchWildCard_v2(first, second)? 1: 0; }
