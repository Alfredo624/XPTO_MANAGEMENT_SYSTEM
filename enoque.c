#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char opcao, escolha;

//QUANDO O ADMIN ENTRAR NA OPCAO FUNCIONARIO
void header(void){
	printf("\n");
	printf("\t\t\t\t\t XPTO MANAGMENT SYSYTEM \n");
	printf("\t\t############################## FUNCIONARIOS ###############################\n");
	return;
	}

	struct add{
		char nome[20], sobrenome[20], user_name[50];
		char sexo;
		int telefone[10];
		char email[50];
		char senha [50];
		char P_trabalho [50];
		char funcao [50];
		char desc [50];
	}; 
	struct add office;
	void menu(void);
	void adicionar(void);
	void listar(void);
	void editar(void);
	void apagar(void);
	void pesquisar(void);

int main() {
	header();
	menu();
	return 0;
}
void menu(){
	do{
		system("cls");
		header();
		puts("\t\t[1]- Adicionar");
		puts("\t\t[2]- Editar");
		puts("\t\t[3]- Listar");
		puts("\t\t[4]- Apagar");
		puts("\t\t[5]- Pesquisar");
		puts("\t\t[6]- Sair");
		printf("\t\tOperacoes: ");
		scanf(" %c", &opcao);
	}while(opcao == '6');
	system("cls");
	switch(opcao){
		case '1': adicionar();
		break;
		case '2': editar();
		break;
		case '3': listar();
		break;
		case '4': apagar();
		break;	
		case '5': pesquisar();
		break;
		default: menu();
		break;		
	}
}
//cadastro
void adicionar(){
	system("cls");
	header();
	puts("\n\t\t\t CADASTRO");
	printf("\t\tNOME: ");
	scanf("%s", office.nome);
	printf("\t\tSOBRENOME: ");
	scanf("%s", office.sobrenome);
	printf("\t\tUSERNAME: ");
	scanf("%s", office.user_name);
	printf("\t\tSEXO: ");
	scanf(" %c", &office.sexo);
	printf("\t\tTELEFONE: ");
	scanf("%d", &office.telefone);
	printf("\t\tEMAIL: ");
	scanf("%s", office.email);
	printf("\t\tSENHA: ");
	scanf("%s", office.senha);
	printf("\t\tPOSTO DE TRABALHO: ");
	scanf("%s", office.P_trabalho);
	printf("\t\tFUNCAO: ");
	scanf("%s", office.funcao);
	printf("\t\tDESCRICAO: ");
	scanf("%s", office.desc);
	puts("\n\t\t\t[1]- ADICIONAR [2]- SAIR");
	printf("\t\t");scanf(" %c", &escolha);
	if(escolha == '1'){
		system("cls");
		header();
		adicionar();
	}else{
		system("cls");
		header();
		menu();
	}
	return;
}
void editar(){
	system("cls");
	header();
	menu();
}
//Buscar as informacoes
void apagar(){
	system("cls");
	header();
	puts("\t\t APAGAR");
	printf("\t\tNOME: ");
	scanf("%s", office.nome);
	printf("\t\tID DO FUNCIONARIO: ");
	puts("\n\t\t\t[1]- APAGAR [2]- SAIR");
	scanf(" %c", &escolha);
	if(escolha == '1'){
		system("cls");
		header();
		apagar();
	}else{
		system("cls");
		header();
		menu();
	}
	return;
}

void listar(){
	system("cls");
	header();
	puts("\n\t\t\t LISTAR");
	printf("\t\t[1]- POR POSTO DE TRABALHO");
	printf("\t\t[2]- FUNCAO");
	printf("\t\t[3]- TODOS");
	//
	puts("\n\t\t\t[4]- LISTAR [5]- SAIR");
	scanf(" %c", &escolha);
	if(escolha == '4'){
		system("cls");
		header();
		listar();
	}else{
		system("cls");
		header();
		menu();
	}
	return;
}

void pesquisar(){
	system("cls");
	header();
	puts("\n\t\t\t PESQUISAR");
	printf("\t\tNOME: ");
	scanf("%s", office.nome);
	printf("\t\tID DO FUNCIONARIO");
	
	puts("\n\t\t\t[1]- PESQUISAR [2]- SAIR");
	scanf(" %c", &escolha);
	if(escolha == '1'){
		system("cls");
		header();
		pesquisar();
	}else{
		system("cls");
		header();
		menu();
	}
}
	 

	

  


