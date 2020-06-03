#include"operatore.h"
#include<stdio.h>
#include<iostream>
using namespace std;
#include"CData.h"
#include<vector>
#include<ctype.h>
#include<algorithm>
#include"auth.h"



int controlla_limite (char *);
void __upper_string(char * _str)
{
	for(int i=0; i<strlen(_str); i++)
		_str[i]= toupper(_str[i]);
	
}
bool direttiva_film(film i, film j)  //questa funziona è una regola di ordinamento che verrà seguita nel momento in cui
									// chiameremo l'algoritmo sort che ordinerà il nostro vettore secondo le nostre esigenze
{
	if(strcmp(i.nome,j.nome)==-1)
		return true;
	else if(strcmp(i.nome,j.nome)==1)
		return false;

}
bool direttiva_clienti(cliente i, cliente j)  //questa funziona è una regola di ordinamento che verrà seguita nel momento in cui
									// chiameremo l'algoritmo sort che ordinerà il nostro vettore secondo le nostre esigenze
{
	if(strcmp(i.cog,j.cog)==-1)
		return true;
	else if(strcmp(i.cog,j.cog)==1)
		return false;
	else if(strcmp(i.cog,j.cog)==0)
	{
		if(strcmp(i.nom,j.nom)==-1)
		return true;
	else if(strcmp(i.nom,j.nom)==1)
		return false;
	}

}
int operatore::ver_username(char * user)
{
	FILE *fp;
	char usern[10];
	fp=fopen("clienti.txt", "r");
	if(!fp)
		return 1;

	cliente cl;

	while (fscanf(fp, "%*s\t%*s\t%*s\t%s\t%*s\t%*f",usern)!= EOF)
	{
		if(strcmp(usern, user)==0)
		{
			fclose(fp);		
			return 0;//l'username è già esistente
		}
	}
	fclose(fp);
	return 1; //username disponibile
	
}




/*VENDITORE */
void venditore::mostra()   //mostra film di venditore

{

	int i=0;
	FILE *fp;
    film f; // istanzio un oggetto f di tipo film 
	vector<film> lst_film;

	
	fp=fopen("film.txt", "r");
	if(!fp) 
		
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM\n";
		return; //ritorna nel caso in cui non è presente nessuna lista film
	}
	while(fscanf(fp, "%s\t%d\t%s\t%s", &f.nome,&f.disp, &f.dt.sdata, &f.noleggiatore)!= EOF){
		f.dt.suddividi_data();   // per convertirmi la stringa data in valori interi
		lst_film.push_back(f);   // inserisco nel vettore lst_film attraverso la funzione della classe <vector>
	}
	fclose(fp);

	for(i=0; i<lst_film.size(); i++)
	{   // per tanti quanti sono i film, prima sostituisco ai titoli il trattino con lo spazio e poi stampo su schermo
		replace_str( lst_film[i].nome, '_', ' ');
		printf(" %s\t\%d\t%s\t%s\n",lst_film[i].nome, lst_film[i].disp, lst_film[i].dt.toString(),lst_film[i].noleggiatore);
	}
}
void venditore:: crea_utente(char* cog, char* nom, char *nascita, char* user, char* password, float credito)
{
	FILE *fp;
	fp= fopen("clienti.txt", "a");
	fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%3.2f\n", cog,nom,nascita,user, password,credito); //stampa tutte le informazioni sul file
	fclose(fp);

	ordina_clienti();

}
void venditore::rimuovi_cliente(char * username)
{

	FILE *fp;
	vector <cliente> lst_clienti;   //dichiaro un vettore lst_clienti di tipo cliente
	int flag=0;
	fp=fopen("clienti.txt", "r");
	if(!fp)
	{
		cout << " NON E' PRESENTE ALCUN CLIENTE ALL'INTERNO\n\n";
		return;
	}

	cliente cl;  //istanzio oggetto cl di tipo cliente

	while (fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%f", cl.cog, cl.nom, cl.nascita,cl.username, cl.password, &cl.credito)!= EOF)
	{
		//leggo fin quando non arrivo alla fine del file e verifico con la strcmp se sono uguali
		if(strcmp(username, cl.username)!=0 )
		{
			lst_clienti.push_back(cl);//lo inserisco nel vettore se NON è la persona che voglio eliminare		
		}
		else
			flag=1;//trovato cliente da eliminare e non lo inserisco nel vettore dei clienti
		
		
	}
if(flag==0)
{
	cout << "IL CLIENTE NON E' PRESENTE NELLA LISTA CLIENTI";
	return;
}
	fclose(fp);
	fp=fopen("clienti.txt", "w");


	for(int j=0; j<lst_clienti.size(); j++) 	//tenendo conto della grandezze del vettore...ristampo tutti gli utenti nel file
	{
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%3.2f", lst_clienti[j].cog, lst_clienti[j].nom,  lst_clienti[j].nascita, lst_clienti[j].username, lst_clienti[j].password, lst_clienti[j].credito);
		
	}
	fclose(fp);
	cout << "\n\n\n\nL'UTENTE DA LEI INSERITO E' STATO RIMOSSO CON SUCCESSO!! "<< endl;
	
}
void venditore::mostra_clienti()
{
	
	cliente cl;
	FILE *fp;
	fp=fopen("clienti.txt", "r");
	if(!fp)
	{
		cout <<" NON E' PRESENTE UNA LISTA CLIENTI ALL'INTERNO";
		return;
	}

	while (fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%f", cl.cog,cl.nom,  cl.nascita,cl.username, cl.password, &cl.credito)!= EOF)
	{

		replace_str(cl.nom, '_', ' '); //non appena legge il trattino, lo sostituisco con uno spazio
		replace_str(cl.cog, '_', ' ');


		printf("%s\t%s\t%s\t%s\t%s\t%3.2f\n", cl.cog,cl.nom ,cl.nascita, cl.username, cl.password, cl.credito); //stampa a schermo
			
	}
	fclose(fp);


}
void venditore::ordina_clienti()
{
	
	FILE *fp;
	cliente cl;    // istanzio un oggetto cl di tipo cliente
	vector<cliente> lst_clienti;
	
	fp=fopen("clienti.txt", "r");
	if(!fp) 
	{
		cout << "NON E' PRESENTE ALCUNA LISTA CLIENTI\n";
		return; //ritorna nel caso in cui non è presente nessuna lista clienti
	}
	while (fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%f", cl.cog,cl.nom, cl.nascita,cl.username, cl.password, &cl.credito)!= EOF)
	{
		lst_clienti.push_back(cl);
	}
	fclose(fp);

//ordinamento
	sort(lst_clienti.begin(), lst_clienti.end(), direttiva_clienti);  //ALGORITMO DI ORDINAMENTO SORT!!! direttiva è l'indirizzo della funzione
	// sto dicendo di ordinarmi dall'inizio fino alla fine secondo una logica
	// dettata da direttiva_clienti
			
	
	
	fp=fopen("clienti.txt", "w");
	
	for(int i=0; i<lst_clienti.size(); i++)
		fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%3.2f\n", lst_clienti[i].cog, lst_clienti[i].nom,  lst_clienti[i].nascita,lst_clienti[i].username, lst_clienti[i].password, lst_clienti[i].credito);
	
	fclose(fp);

}
void venditore::aggiungi_film(char * movie)
{	

	FILE *fp;
	fp=fopen("film.txt", "a");
	fprintf(fp, "%s\t1\t_\t_\n", movie);
	
	fclose(fp);
ordina_film();

}
void venditore::ordina_film()
{
	
	FILE *fp;
	film f,temp;
	vector<film> lst_film;
	
	fp=fopen("film.txt", "r");
	if(!fp) 
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM\n";
		return; //ritorna nel caso in cui non è presente nessuna lista film
	}
	while(fscanf(fp, "%s\t%d\t%s\t%s", &f.nome,&f.disp, &f.dt.sdata, &f.noleggiatore)!= EOF){
		f.dt.suddividi_data();
		lst_film.push_back(f);
	}
	fclose(fp);


	sort(lst_film.begin(), lst_film.end(), direttiva_film);  //ALGORITMO DI ORDINAMENTO SORT!!! direttiva è l'indirizzo della funzione
	

	//ordinamento
	
	fp=fopen("film.txt", "w");
	
	for(int i=0; i<lst_film.size(); i++)
	fprintf(fp, "%s\t%d\t%s\t%s\n", lst_film[i].nome, lst_film[i].disp,lst_film[i].dt.toString(), lst_film[i].noleggiatore );
	
	fclose(fp);

}
void venditore::rimuovi_film(char * nomefilm)
{

	FILE *fp;
	vector <film> lst_film;
	
	fp=fopen("film.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM \n\n";
		return;
	}

	film f;

	while(fscanf(fp, "%s\t%d\t%s\t%s", f.nome,&f.disp,f.dt.sdata,f.noleggiatore)!=EOF)
	{
		f.dt.suddividi_data();
		lst_film.push_back(f);
		
	}
	
	fclose(fp);

	vector<film>::iterator i;
	i = lst_film.begin();

	for(;i!=lst_film.end();i++)
	{
		if (strcmp(i->nome, nomefilm)==0)
				{
				lst_film.erase(i);
				break;
				}
	}

	fp= fopen("film.txt", "w");

	for(int j=0; j<lst_film.size(); j++)
	{
		fprintf(fp, "%s\t%d\t%s\t%s\n", lst_film[j].nome,lst_film[j].disp, lst_film[j].dt.toString(),lst_film[j].noleggiatore );
		
	}
	fclose(fp);
	
}
void venditore::modifica_imp(char * nome, char * cognome, char * data, char* user, char *password)
{
	FILE *fp;
	char buffer[50];
	this->set_nome(nome);
	this->set_cognome(cognome);
	this->set_nascita(data);
	this->set_password(password);
	this->set_username(user);

	sprintf(buffer, "%s\t%s\t%s\t%s\t%s\n", cognome, nome, data,user, password);

	fp=fopen("venditore.pwd", "wb");
	fwrite(buffer, sizeof(char), strlen(buffer), fp);
	fclose(fp);


}
	
//NOLEGGIATORE
void noleggiatore::mostra()

{


	int i=0;
	FILE *fp;
	vector <film> lst_film;
	
	fp=fopen("film.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM \n\n";
		return;
	}
	film f;

	while(fscanf(fp, "%s\t%d\t%*s\t%*s", &f.nome,&f.disp)!=EOF)
	{
		lst_film.push_back(f);
		
	}
	
	fclose(fp);

	for(i=0; i<lst_film.size(); i++)
	{
		replace_str( lst_film[i].nome, '_', ' ');
		printf(" %s\t\%d\n",lst_film[i].nome, lst_film[i].disp);
	}

}
int noleggiatore::noleggia_film(char *titolo)
{	
	
	FILE *fp;
	int flag=0;
	char risposta[3];
	char utente[20];
	vector <film> lst_film;
	film f;

	sprintf(utente, "%s_%s", nome , cognome);
	if(credito<0)
	{
		cout << "SIAMO SPIACENTI MA IL TUO CREDITO NON E' SUFFICIENTE PER NOLEGGIARE UN FILM" << endl;
	 return 4;
	}

	if(controlla_limite(utente)==3)
		return 1;

	fp=fopen("film.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM \n\n";
		return 5;
	}

	while(fscanf(fp, "%s\t%d\t%s\t%s", &f.nome,&f.disp, f.dt.sdata , f.noleggiatore)!=EOF)
	{
			f.dt.suddividi_data();
		
			if(strcmp(f.nome, titolo)==0 )
			{
				flag=1;
				if(f.disp!=0)
				{
					cout <<"\n			INFORMAZIONI TARIFFE";
					cout <<"\n\n		8 sec : 2,5 euro";
					cout <<"\n		14 sec : 2,7 euro";
					cout <<"\n		18 sec : 3,3 euro";
					cout <<"\n		21 sec : 3,7 euro";
					cout <<"\n		24 sec : 4 euro";
					cout <<"\n\nIMPORTANTE: in caso di ritardo 0.1 euro/sec\n";
		
					cout << titolo <<" e' disponibile. Vuoi noleggiarlo? SI o NO?   ";
					cin.getline(risposta,3 );
					fflush(stdin);
					__upper_string(risposta);
					if(strcmp(risposta, "SI")==0 ){
						f.disp--;
						sprintf(f.noleggiatore,"%s_%s",nome,cognome);
						f.dt.costruisci_data();
						f.dt.suddividi_data(); /* ci serve per poi fare operazioni sulle date*/ 
						cout << "\n\n\nComplimenti hai noleggiato il film " << titolo << "\n\n\n";
						
					}

				}
				else 			
				{
					cout << titolo <<" non e' disponibile al momento. Riprova piu' tardi!\n\n\n\n";
					fclose(fp);
				return 2;
				}
	
				
			}

	lst_film.push_back(f);

			
	}

fclose(fp);

		if(flag==0)
		{
			cout << "Il film cercato non è presente ";
			return 3;
		}


fp=fopen("film.txt", "w");

		for(int i=0; i<lst_film.size(); i++)
		{
			fprintf(fp, "%s\t%d\t%s\t%s\n", lst_film[i].nome, lst_film[i].disp, lst_film[i].dt.toString() , lst_film[i].noleggiatore);
			
		}
fclose(fp);
return 0;
}
int controlla_limite (char * nome_noleggiatore)
{
	char acquirente[40];
	int limite=0;
	FILE *fp;
	fp=fopen("film.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM \n\n";
		return 0;
	}
	while(fscanf(fp, "%*s\t%*d\t%*s\t%s",acquirente)!=EOF && limite <3)
	{
		if(strcmp(acquirente, nome_noleggiatore)==0)
			limite++;
	}
	fclose(fp);

	return limite;
}
vector<film> lst_film_posseduti (char * utente)
{
	vector<film> lst_film;
	film f;
	FILE *fp;
	fp=fopen("film.txt", "r");
	if(!fp)
	{
		return lst_film;
	}
	while(fscanf(fp, "%s\t%d\t%s\t%s",f.nome, &f.disp, f.dt.sdata, f.noleggiatore)!=EOF)
	{
		f.dt.suddividi_data();
		if(strcmp(f.noleggiatore, utente)==0)
			lst_film.push_back(f);
			
	}
	fclose(fp);
return lst_film;
}
int noleggiatore::restituisci_film()
{	char utente[30];
	film f;
	FILE *fp;
	vector<film> lst_film;
	vector<film> lst_movie;
	vector<film>::iterator el;
	//int i=0;

	Data cur_time;
	cur_time.costruisci_data();
	cur_time.suddividi_data();

	sprintf(utente, "%s_%s", nome, cognome);
	if(controlla_limite(utente)==0)
	{
		cout << "Gentile utente, non ci sono film da restituire\n\n\n";
		return 0;
	}
	lst_movie = lst_film_posseduti(utente); //inizializzo un secondo vettore in cui inserisco i film da restituire lista movie è la lista dei 3 film...sempre se sono tre!*/
	el=lst_movie.begin();
	 // dato che la funzione begin dell'oggeto vector ritorno il puntatore al primo elemento
	// del vettore dinamico cambio i parametri da modificare

	long int differenza =  el->dt-cur_time;
	if(differenza>0 && differenza <=8)
		scala_credito(2.5);
	else if (differenza>8 && differenza <=14)
		scala_credito(2.7);
	else if (differenza>14 && differenza <=18)
		scala_credito(3.3);
	else if (differenza>18 && differenza <=21)
		scala_credito(3.7);
	else if (differenza>21 && differenza <=24)
		scala_credito(4);
	else if (differenza>24)
		scala_credito((differenza-24)*0.10+4);

	el->dt.azzera_data();
	strcpy(el->dt.sdata, "_");								
	strcpy(el->noleggiatore, "_");
	

	el->disp++;

	
	
	fp=fopen("film.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA FILM \n\n";
		return 0;
	}
	while(fscanf(fp, "%s\t%d\t%s\t%s",f.nome, &f.disp, f.dt.sdata, f.noleggiatore)!=EOF)
	{
		f.dt.suddividi_data();
		if(strcmp(f.nome, el->nome)==0)
		{
				lst_film.push_back(*el);
		}
		else
			lst_film.push_back(f);

	}
	fclose(fp);

	fp=fopen("film.txt", "w");
	
	for(int i=0; i<lst_film.size(); i++)
		{
			fprintf(fp, "%s\t%d\t%s\t%s\n", lst_film[i].nome, lst_film[i].disp, lst_film[i].dt.toString() , lst_film[i].noleggiatore);
			
		}
	fclose(fp);
	return 1;
}
void noleggiatore::da_restituire(char *utente)
{
	vector<film> lst_da_rest;
	lst_da_rest= lst_film_posseduti(utente);
	if(lst_da_rest.size()>0)
	{
	cout << " Devi ancora resituire questi film: " << endl;
	
	for(int i=0; i<lst_da_rest.size(); i++)
		cout << lst_da_rest[i].nome << endl;
	}
	cout << "\n\n\n\n";
}
void noleggiatore::ricarica_credito(int soldi)
{
	vector<cliente> lst_clienti;
	cliente cl;
	FILE *fp;
	fp=fopen("clienti.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA CLIENTI DOVE RICARICARE CREDITO\n\n";
		return;
	}
	while (fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%f", cl.cog, cl.nom, cl.nascita,cl.username, cl.password, &cl.credito)!= EOF)
	{
	
		if(strcmp(cl.nom, nome)==0 && strcmp(cl.cog, cognome)==0)
		{cl.credito += soldi;
		credito += soldi;}
		lst_clienti.push_back(cl);
			
	}
	fclose(fp);


		fp=fopen("clienti.txt", "w");
		for(int i=0; i<lst_clienti.size(); i++)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%3.2f\n",  lst_clienti[i].cog, lst_clienti[i].nom, lst_clienti[i].nascita,lst_clienti[i].username, lst_clienti[i].password, lst_clienti[i].credito);
		}


fclose(fp);



}
void noleggiatore::scala_credito(float prezzo)
{
	credito-= prezzo;
	vector<cliente> lst_clienti;
	cliente cl;
	FILE *fp;
	fp=fopen("clienti.txt", "r");
	if(!fp)
	{
		cout << "NON E' PRESENTE ALCUNA LISTA \n\n";
		return;
	}
	while (fscanf(fp, "%s\t%s\t%s\t%s\t%s\t%f", cl.cog,cl.nom,  cl.nascita, cl.username,cl.password, &cl.credito)!= EOF)
	{
	
		if(strcmp(cl.nom, nome)==0 && strcmp(cl.cog, cognome)==0)
		cl.credito = credito;
		lst_clienti.push_back(cl);
			
	}
	fclose(fp);


		fp=fopen("clienti.txt", "w");
		for(int i=0; i<lst_clienti.size(); i++)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%3.2f\n", lst_clienti[i].cog,lst_clienti[i].nom,  lst_clienti[i].nascita,lst_clienti[i].username, lst_clienti[i].password, lst_clienti[i].credito);
		}


fclose(fp);




}