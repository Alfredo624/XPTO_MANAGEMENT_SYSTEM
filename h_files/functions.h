#ifndef FUNCTIONS_H
#define FUNCTIONS_H

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

#define MAX_ITENS 100



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
	int id_company;
	int type;
	char date_out[20];
	char date_in[20];
	char date_prevision_in[20];
	int id_employee;
	char date[20];
	float money;
	char observation[1000];
} operation_tmp;

// Company structure
struct company{
	int id;
	char name[30];
	char type[20];
	char contact[60];
} company_tmp;

// 					#Structures end here



// 					#Prototypes start here

// Menu items
void Components(void);
void WorkOffice(void);
void Worker(void);
void Operations(void);
void Company(void);
void Statistics(void);

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
int ExistsWorkOffice(char p[]);

//Component CRUD
void InsertComponents(void);
void UpdateComponents(void);
void DeleteComponents(void);
void ListComponents(void);
void SearchComponents(void);
void SubstituteByWorkOffice(void);
int ExistsComponentById(int p);
int ExistsComponent(char p[]);

//Operation CRUD
void InsertOperations(void);
void UpdateOperations(void);
void DeleteOperations(void);
void ListOperations(void);
void SearchOperations(void);
int ExistsOperation(int p);

//Company CRUD
void InsertCompany(void);
void UpdateCompany(void);
void DeleteCompany(void);
void ListCompany(void);
void SearchCompany(void);
void DeleteCompanyFromOperations(int id_company);
int ExistsCompanyById(int id);
int ExistsCompany(char p[]);

// General function definitions
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

// 					#Prototypes end here	

#endif
