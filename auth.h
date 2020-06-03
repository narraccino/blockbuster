#include"operatore.h"

int auth(noleggiatore*,char * username, char *);
int auth(venditore * vend,char * username,char * password);
int menu_vend(venditore *);
int menu_noleg(noleggiatore *);
void get_line(char* str, int len);
void replace_str(char * str, char space, char underscore );