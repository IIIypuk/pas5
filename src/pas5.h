#ifndef _PAS5_H
#define _PAS5_H

typedef struct 
{
  char *url;
  char *email;
  char *login;
  char *pass;
  char *desc;
} pas5_pwd;

int callback(void *, int, char **, char **);

#endif
