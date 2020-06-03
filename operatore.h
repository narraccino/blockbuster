#ifndef COPERATORE
#define COPERATORE

#include"CData.h"
#include<vector>


class cliente  {
		public:
				char username[10];
				char nom[20];
				char cog[20];
				char nascita[13];
				char password[10];
				float credito;
				};

class film {
public:
	char nome[50];
	int disp;
	char noleggiatore[20];
	Data dt;				// composizione di film con la classe data
};




class operatore
{
protected:
	char username[10];
	char nome[20];
	char cognome[20];
	Data nascita;
	char password[20];
public:
	virtual void mostra(void)=0; //funzione virtuale pura che viene ridefinita da venditore e noleggiatore
	char* get_nome(){return nome;};
	char * get_cognome(){return cognome;};
	void set_nome(char * n){strcpy(nome, n);}
	void set_cognome(char * c){strcpy(cognome, c);}
	void set_nascita(char * d) {/*da implementare successivamente attravero overloading di =*/};
	void set_password(char *p){strcpy(password, p);}
	char * get_password(){return password;}

	char * get_username() {return username;}
	void set_username(char *user ) {strcpy(username, user);}
	int ver_username(char * user);

};


class venditore: public operatore
{	
private:
	void ordina_film(); //funzioni utilizzate solo dalla classe
	void ordina_clienti();
public:
		void mostra();
		void crea_utente(char* cog, char* nom, char *nascita, char* user, char* password, float credito);
		void mostra_clienti();
		void aggiungi_film(char *);
		void rimuovi_film(char *);
		void rimuovi_cliente(char* username);
		void modifica_imp(char * nome, char * cognome, char * data, char* username, char *password);
		
			
};


class noleggiatore: public operatore
{	
private:
	float credito;
public:
		void mostra();
		
		float get_credito (){ return credito;};
	    void set_credito (float c){credito =c;};
		int noleggia_film(char *);	
		int restituisci_film ();
		void da_restituire(char *);
		void ricarica_credito(int);
		void scala_credito(float);

	
};
#endif