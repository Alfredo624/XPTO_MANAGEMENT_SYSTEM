#include<stdio.h>

#define size 200 
main()
{
    int	j = 0; 
    char row[size]="enio 2020";
    char password_data[size];
    char user_data[size];
			while(row[j] != ' '){
				user_data[j] = row[j];
                // printf("%c", row[j-1]);
                printf("%c", user_data[j++]);

			}
            puts("");
            while(row[++j] != '\0'){
				password_data[j] = row[j];
                // printf("%c", row[j-1]);
                printf("%c", password_data[j]);

			}


}