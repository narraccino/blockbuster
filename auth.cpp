#include"auth.h"
#include<stdio.h>
#include<cstring>
#include<iostream>
#include<ctype.h>
#include"operatore.h"
#include<conio.h>
#include"CData.h"
using namespace std;

void _upper_string(char * str); // serve per rendere lett. maiuscole 
void replace_str(char * str, char space, char underscore ); /* è una funzione che ha lo scopo di 
									leggere un carattere desiderato e di sostituirlo con un secondo carattere desiderato*/

// VENDITORE

operatore *op; // dichiaro un puntatore alla classe operatore. 
int menu_vend(venditore *vend)
{
	
	op=vend; 
	
	int i,flag =0;
	char nom[20];
	char cog[20];
	char nascita[9];
	char password[20];
	char username[20];
	float credito;
	do{

flag =0;

cout << "\n\nSCEGLI L'OPERAZIONE DESIDERATA\n\n\n";

cout << "(1) - Inserisci nuovi film\n\n";

cout << "(2) - Consulta lista film e relativi noleggiatori\n\n";

cout << "(3) - Consulta lista clienti\n\n";

cout << "(4) - Crea nuovo cliente\n\n";

cout << "(5) - Rimuovere cliente\n\n";

cout << "(6) - Rimuovere film\n\n";

cout << "(7) - Modifica impostazioni\n\n";

cout << "(8) - ESCI DAL MENU\n\n";

cout << "Scegli numero: ";
cin >>i;
fflush(stdin);



switch(i)
{
case 1:

	int i;
	char movie[50];
	cout << "Inserisci nuovo film: ";
	cin.getline(movie, 50);   // la funzione cin.getline accetta anche lo spazio
	fflush(stdin);
	_upper_string(movie);   //rende maiuscole le lettere passate in input
	 replace_str(movie, ' ', '_');  //sostituisce lo spazio con un trattino _

	((venditore*)op)->aggiungi_film(movie); /* cast del puntatore op perchè la funzione aggiungi_film è un 
												medoto della classe venditore*/
	flag =1;
	system("cls");
	break;

case 2:
		system("cls");
		op->mostra();   /*dato che in op vi è l'indirizzo dell'oggetto vend. 
							Tramite op richiamo la funzione mostra di venditore*/
		flag =1;
		break;

case 3:
		system("cls");

	((venditore*)op)->mostra_clienti();  // cast del puntatore op anche qui
	flag=1;
	break;

case 4:
	
	cout << "CREAZIONE NUOVO CLIENTE\n\n";
	cout << "Inserisci nome: ";
	cin.getline(nom, 30);
	fflush(stdin);
	replace_str(nom, ' ', '_');
	_upper_string(nom);

	cout << "Inserisci cognome: ";
	cin.getline(cog, 30);
	fflush(stdin);
	replace_str(cog, ' ', '_');
	_upper_string(cog);

	do{
	cout << "Inserisci la data di nascita(gg/mm/aa): ";
	cin.getline(nascita, 13);
	fflush(stdin); 
	}while(Data::verifica_data(nascita)==0);  //l'ho potuto fare senza istanziare un oggetto di classe DATA xkè verifica_data è una funzione static
												/*all'interno di verifica data, viene verificata la data realmente esistita.*/
	int res;
	do{
		cout << "Inserisci username: ";
		cin.getline(username, 20);
		fflush(stdin);
		res=((venditore*)op)->ver_username(username);
		if(res==0)
			cout << "ATTENZIONE! Nome utente già esistente!\n";
	}while(res==0);
	
	cout << "Inserire password: ";
	cin.getline(password, 20);
	fflush(stdin);

	do{
		cout << "Inserisci il credito (accettate banconote da 5 a 100 euro): ";
	cin >> credito;
	fflush(stdin);
	}while(((int)credito) !=5 && ((int)credito) !=10 && ((int)credito) !=20 && ((int)credito) !=50 && ((int)credito) !=100);
	((venditore*)op)->crea_utente(cog,nom,nascita,username,password, credito);
	flag=1;

	system("cls");
	break;

case 5:
	char username[20];
	cout << "Inserire nome, cognome, nascita del cliente da eliminare\n";
	cout << "NOME: ";
	cin.getline(nom,  20);
	fflush(stdin);
	_upper_string(nom);
	cout << "COGNOME: ";
	cin.getline(cog, 20);
	fflush(stdin);
	_upper_string(cog);
	cout << "DATA DI NASCITA gg/mm/aa: ";
	cin.getline(nascita, 9);
	fflush(stdin);
	cout << "NOME UTENTE: ";
	cin.getline(username, 20);
	fflush(stdin);

	((venditore*)op)->rimuovi_cliente(username);
	flag=1;

	break;


case 6:
	char titolo[30];
	cout << "Inserire titolo film da eliminare: ";
	cin.getline(titolo, 30);
	fflush(stdin);
	_upper_string(titolo);
	replace_str(titolo, ' ', '_');

	((venditore*)op)->rimuovi_film(titolo);
	flag=1;
		system("cls");

	break;

case 7:
	
	
	cout << "MODIFICA IMPOSTAZIONI VENDITORE\n\n";
	cout << "Inserisci nome: ";
	cin.getline(nom, 20);
	fflush(stdin);
	_upper_string(nom);
	cout << "Inserisci cognome: ";
	cin.getline(cog,20);
	fflush(stdin);
	_upper_string(cog);
	cout << "Inserisci la data di nascita(gg/mm/aa): ";
	cin.getline(nascita, 9);
	fflush(stdin);
	cout << "Inserire username: ";
	cin.getline(username, 20);
	fflush(stdin);
	cout << "Inserire password: ";
	cin.getline(password, 20);
	fflush(stdin);

	((venditore*)op)->modifica_imp(nom, cog, nascita,username, password);
	system("cls");
		system("cls");

	return 8;
	

case 8:
	
	system("cls");
	break;
	
default:
		
	cout << "SCELTA ERRATA\n\n\n\n\n\n\n";
	i=0; 
	
}

} while(i==0 && flag==0);

return i;


}




/*NOLEGGIATORE*/ 

int menu_noleg(noleggiatore *noleg)
{

  op=noleg;/* assegno alla variabile puntatore a operatore l'indirizzo 
			 della variabile puntatore alla classe venditore*/
char utente[30];
char nome[30];
char cognome[30];

strcpy(nome, ((noleggiatore*)op)->get_nome());
strcpy(cognome, ((noleggiatore*)op)->get_cognome());
replace_str(nome, '_', ' ');
replace_str(cognome, '_', ' ');

sprintf(utente, "%s_%s", ((noleggiatore*)op)->get_nome(), ((noleggiatore*)op)->get_cognome());

cout << "\nBenvenuto a BLOCKBUSTER " << nome << " " << cognome << " " << "scegli il tuo film preferito!\n\n" << endl;


cout << "Il tuo saldo contabile e' di EURO: " << ((noleggiatore*)op)->get_credito() << " \n\n\n\n";

if(((noleggiatore*)op)->get_credito()<0)
	cout << "!!!ATTENZIONE!!! devi restituire a BLOCKBUSTER "<< ((noleggiatore*)op)->get_credito()*(-1) << " euro" << endl;


((noleggiatore*)op)->da_restituire(utente);


int i,flag =0;

do{

flag =0;

cout << "SCEGLI L'OPERAZIONE DESIDERATA\n\n\n";

cout << "(1) - Noleggia film\n\n";

cout << "(2) - Consulta lista dei film\n\n";

cout << "(3) - Restituzione articoli\n\n";

cout << "(4) - Ricarica credito\n\n";

cout << "(5) - LOGOUT\n\n";

cout << "Scegli numero: ";
cin >> i;
fflush(stdin);


switch(i)
{
case 1:
		int i;
	char movie[30];
	cout << "Ricerca film: ";
	cin.getline(movie, 30);
	fflush(stdin);
	_upper_string(movie);

	replace_str(movie, ' ', '_');

	if(((noleggiatore*)op)->noleggia_film(movie)==1)
		cout << "Non e' possibile noleggiare il film perche' superata la soglia di film noleggiati";
	flag =1;
	break;
	
case 2:
	op->mostra();
	flag=1;
	break;

case 3:
	if(((noleggiatore*)op)->restituisci_film())
		cout << "Il film è stato restituito. Grazi e arrivederci \n\n\n\n";

	flag=1;
	break;

case 4:

	int soldi;
	cout << "\n\nPrego inserire banconote (da 5 a 100 euro)";

			do{
			cin >> soldi;
			fflush(stdin);
			}while(((int)soldi) !=5 && ((int)soldi) !=10 && ((int)soldi) !=20 && ((int)soldi) !=50 && ((int)soldi) !=100);

	((noleggiatore*)op)->ricarica_credito(soldi);
	flag=1;
	break;

case 5:
	
	flag=1;
	system("cls"); /*cancello schermo*/
	break;
	
	
default:
		
	cout << "SCELTA ERRATA\n\n\n\n\n\n\n";
	i=0; 
}
}while(flag==0)	;

	return i;
}
int auth(venditore * vend, char * username, char * password)
{
	op= vend;   
	FILE *fp;
	char pwd[50];
	char nome[20];
	char cognome[20];
	char usern[20];
	char data[13];
	char *buffer;
	long fSize;


	fp=fopen("venditore.pwd", "rb");

	fseek(fp, 0, SEEK_END);
	fSize=ftell(fp);
	rewind(fp);
	buffer= new char [fSize];
	for(int h=0; h<fSize;h++)// inizializzo buffer con tutti zeri
	{
		buffer[h]=0;
	}
	fread(buffer, sizeof(char), fSize, fp);
	sscanf(buffer, "%s\t%s\t%s\t%s\t%s",cognome, nome, data, usern, pwd);
	
	if(strcmp(usern, username)==0 &&(strcmp(pwd, password)==0))
	{
		((venditore*)op)->set_nome(nome);
		((venditore*)op)->set_cognome(cognome);
		((venditore*)op)->set_password(pwd);
		((venditore*)op)->set_nascita(data);
		((venditore*)op)->set_username(usern);
		fclose(fp);
		return 1;
	}
	
	fclose(fp);
	return 0;
}
int auth(noleggiatore *noleg, char *username, char * password)
{
	op=noleg;
	int res,flag;
	char nom[20];
	char cog[20];
	char data[13];
	char usern[20];

	FILE *fp;
	fp=fopen("clienti.txt", "r");
	if(!fp)
		return 0;
	do
	{
		char  pwd[30];
		float temp2;
		
		res= fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%f",cog ,nom , data, usern, pwd, &temp2);
		if(strcmp(usern, username)==0 && strcmp( pwd, password)==0)
		{
			((noleggiatore*)op)->set_nome(nom);
			((noleggiatore*)op)->set_cognome(cog);
			((noleggiatore*)op)->set_nascita(data);
			((noleggiatore*)op)->set_credito(temp2);
			((noleggiatore*)op)->set_password(pwd);
			((noleggiatore*)op)->set_username(usern);
			flag=1;
			break;
		}

	}while(res!= EOF );
	fclose(fp);


	if(flag==1)
		return 1;
	else
		return 0;

}
void _upper_string(char * _str)
{
	for(int i=0; i<strlen(_str); i++)
	
		_str[i]= toupper(_str[i]); //funzione che mi consente di rendere maiuscolo un carattere dell'alfabeto
	
}
void replace_str(char * str, char space, char underscore )
{
	for(int i=0; i<strlen(str); i++)
		if(str[i]==space)
		{
			str[i]=underscore;
		}
}