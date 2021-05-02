#include <stdio.h>

// Constants declarations

// Global variables come here
int i;

// 				#Structures start here

//Employee and User structure
struct employee{
	int id;
	char name[20];
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
void login();
void menu();
void errorMessage();
void clearScreen();
void exit();
void footer();
void header();

void login(){
	system("cls");
	header();
	//printf("\n\n\t\t WELCOME TO XPTO MANAGMENT SYSYTEM\n");
	//printf("\t\t\t\tSecurity");
	footer();
}

void menu(){

}

// Program start running here
int main() {
	login();
	getchar();
	return 0;
}

void errorMessage(){

}

void exit(){

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

void sucessfull(){

}