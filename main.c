#include <stdio.h>

int i;

// 				#Structures start here

//User structure
struct user{
	char user_name[20];
	char password[20];
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

//Employee structure
struct employee{
	int id;
	char name[20];
	char function[20];
	char note[50];
};

//Operation structure
struct operations{
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


// 					#Structures end here

void login(){
	system("cls");
	printf("\n\n\t\t\t\t\t\t WELCOME TO XPTO MANAGMENT SYSYTEM \t\t\t\t\t\t\n");
	printf("\t\t\t\t\t\t\t\t 		Security 				  \t\t\t\t\t\t\n\n");
}

void menu(){

}

int main() {
	login();
	getchar();
	return 0;
}
