#include<stdio.h>
#include<stdlib.h>

//passando o codigo da insercao e o caminho do ficheiro
int insert(int cod, char* path)
{   
	//declaracao das variaveis
	FILE *file;
    char user_name[30], user_password[12];
    //insercao por codigo
    switch (cod)
    {
        case 1:
        //abertura do ficheiro
    	file = fopen(path,"a+");
        puts("Digite o nome do usuario:");
        gets(user_name);
        puts("Digite a senha:");
        gets(user_password);
        //insercao no ficheiro
        fprintf(file, "\n%s %s",user_name,user_password);
		fclose(file);
            return 1;
    
        default:
            return 0;
    }
}
int main(){
   
    char word[101]="data\\employee_user.dat";
	if(insert(1,word))
		puts("usuario inserido com sucesso!");
	else
		puts("algo deu errado :(");
    return 0;
    
}

