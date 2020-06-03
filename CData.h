#ifndef DATA
#define DATA
#include<stdio.h>
#include<cstring>
#include<ctime>


class Data
{
private:
	int secondi;
	int minuti;
	int ore;
	int giorno;
	int mese;
	int anno;
	time_t diff_sec;

public:
	char sdata[20];
	Data(){
		giorno=0;
		mese=0;
		anno=0;
	};

	char* toString()
	{
		
		if(giorno==0 && mese==0  && anno==0)
			strcpy(sdata, "_");
		else
			sprintf(sdata, "%d/%d/%d-%d.%d.%d", giorno, mese, anno, ore, minuti, secondi);

		return sdata;
	}


	void suddividi_data ()
	{		
		
			int res = sscanf(sdata, "%d%*c%d%*c%d%*c%d%*c%d%*c%d", &giorno, &mese, &anno, &ore, &minuti, &secondi);
			//LA FUNZIONE sscanf restituisce(nel caso in cui l'esito è positivo) il numero di letture fatte, altrimenti
			//la funzione restituisce 0 in caso di errore. quindi nel nostro caso restituisce 3 se l'esito è positivo.
			if(res==0)
			{
			secondi=0;
		    minuti=0;
		    ore=0;
			giorno =0;
			mese=0;
			anno=0;
			}
	}

	void azzera_data()
	{
		    secondi=0;
		    minuti=0;
		    ore=0;
			giorno =0;
			mese=0;
			anno=0;
	}


	/*costruiamo la stringa data dalla struttura tm*/
	void costruisci_data ()
	{
						time_t t; /*t di tipo time_t*/ 
						tm* lt; //puntatore a struttura

						time(&t);
						lt = localtime(&t); /*local time è la funzione presente in ctime */
						sprintf(sdata, "%d/%d/%d-%d.%d.%d", lt->tm_mday, lt->tm_mon+1, 
							lt->tm_year+1900, lt->tm_hour,lt->tm_min, lt->tm_sec ); 
											
						/*leggiamo la data come interi e ci costruiamo la stringa da essi 
						mettendola in sdata. 
					mon+1 xkè il mese esce indietro*/

	}


	//OVERLOADING OPERATORE - per restituire la differenza dei secondi 
	//che deve essere confrontata per scalare il credito
	
		
	double operator-(Data d1)
	{
		tm lt_past, lt_pres;
		time_t t_past, t_pres;
  
	lt_past.tm_sec=secondi;
	lt_past.tm_min=minuti;
	lt_past.tm_hour=ore;
	lt_past.tm_year=anno-1900;  /*dobbiamo assegnare al campo anno della struttura tm l'anno sottratto di 1900 perchè altrimenti non lo accetta perchè lui conta a partire dal 1900. ottenendo in questo 110 se stiamo nel 2010*/
	lt_past.tm_mon=mese-1; /*stesso discorso qui*/
	lt_past.tm_mday=giorno;
    
	lt_pres.tm_sec=d1.secondi;
	lt_pres.tm_min=d1.minuti;
	lt_pres.tm_hour=d1.ore;
	lt_pres.tm_year=d1.anno-1900;
	lt_pres.tm_mon=d1.mese-1;
	lt_pres.tm_mday=d1.giorno;
 

	t_past = mktime(&lt_past); 
		t_pres = mktime(&lt_pres); 

		return (difftime(t_pres, t_past));
	}

/*	Una visibilita' (scope) limitata al sorgente in cui e' definita; in altri termini, una funzione static 
puo' essere invocata solamente da altre funzioni che siano definite nello stesso file sorgente*/
	static int verifica_data(char * data){
		unsigned int g, m, a;
		sscanf(data, "%d/%d/%d", &g, &m, &a);

		switch(m)
				{
					case 11:
					case 4:
					case 6:
					case 9:
						if(g<=30)
							return 1;//ok
						break;
					case 2:
						if(a%4==0 && g<=29)
						return 1;
						else if(a%4!=0 && g<=28)
						return 1;
						break;
					default:
						if(a<=31)
							return 1;
				}

		return 0;

	}
	
};

#endif