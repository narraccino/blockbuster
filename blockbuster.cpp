#include<iostream>
#include<conio.h>
#include<cstring>
#include"operatore.h"
#include"auth.h"

using namespace std;

int main()
{

int i,flag;
char str[10];		// queste stringhe saranno utili per il nome utente e password che inserirò nel menu						
char username[20];

venditore vend;			//istanzio gli oggetti vend e noleg
noleggiatore noleg;
do
{

cout << "\n\n\b\t\t\t\tBENVENUTI A BLOCKBUSTER\n\n\n\n\n";
system("color 1E");
flag =0;
i=0;
		do{
		cout << "Prego immettere NOME UTENTE: ";
		cin.getline(username, 20);
		fflush(stdin);

		cout << "Prego immettere PASSWORD UTENTE: ";
			do 
		   { 
			   char c=getch(); 
			 
				if(c==8)
				{
					if(i>0){
					str[--i]='\0';					//servono per non visualizzare su schermo le lettere della passwrd
					putchar(8);
                    putchar(' ');
                    putchar(8);
					}
				}
				else
				{
					   str[i]=c;
					   if(str[i]!=13) 
					   { 
						 
						   cout<<"*"; 
					   }
					   i++;
				}
		   } 
			while (str[i-1]!=13); // quando premo invio(carattere 13 ASCII) il ciclo finirà


			str[i-1]= '\0';  /*tolgo il codice ascii invio (13) e salvo carattere di fine stringa altrimenti avrebbe salvato il carattee 13*/

cout << "\n\n\n\n";

if(auth(&vend,username, str)==1)
{
	cout << "Sei entrato come venditore "<< vend.get_nome()<< " " << vend.get_cognome() << "\n*****ACCESSO PERMESSO*****\n\n\n\n\n";
	flag=1;
	while (menu_vend(&vend)!=8);   //accedo al menu venditore, quando la funzione menu_vend restituirà 8 si uscirà dal ciclo
}

else
{

	if (auth(&noleg, username, str)==1)
		{
		while(menu_noleg(&noleg)!=5);
		flag=1;
		}


	else
		cout << "Password errata: !!!!!!!!ACCESSO NEGATO!!!!!!!!!!\n\n\n\n\n";
		
	
	
}
		}while(flag==0);

}while(1); /*LO LEGGE COME VALORE VERO E VA ALL'INFINITO PERCHE' IL PROGRAMMA DEVE FUNZIONARE 24 H SU 24*/


system("pause");
return 0;
}
