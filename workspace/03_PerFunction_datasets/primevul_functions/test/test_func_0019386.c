static void checkpasswd(const char *kind,
                        char **userpwd)
{
  char *ptr;
  if(!*userpwd)
    return;

  ptr = strchr(*userpwd, ':');
  if(!ptr) {

    char passwd[256]="";
    char prompt[256];
    size_t passwdlen;
    size_t userlen = strlen(*userpwd);
    char *passptr;


    curlx_msnprintf(prompt, sizeof(prompt),
                   "Enter %s password for user '%s':",
                   kind, *userpwd);


    getpass_r(prompt, passwd, sizeof(passwd));
    passwdlen = strlen(passwd);


    passptr = realloc(*userpwd,
                      passwdlen + 1 +
                      userlen + 1);

    if(passptr) {

      passptr[userlen]=':';
      memcpy(&passptr[userlen+1], passwd, passwdlen+1);
      *userpwd = passptr;
    }
  }
}
