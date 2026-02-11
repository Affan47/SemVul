getUserDB(void)
{
   char *userdir = getenv("HOME");
   char *nssdir = NULL;

   if (userdir == NULL) {
	return NULL;
   }

   nssdir = PORT_Alloc(strlen(userdir)
		+sizeof(NSS_USER_PATH1)+sizeof(NSS_USER_PATH2));
   if (nssdir == NULL) {
	return NULL;
   }
   PORT_Strcpy(nssdir, userdir);

   if (!testdir(nssdir)) {
	PORT_Free(nssdir);
	return NULL;
   }
   PORT_Strcat(nssdir, NSS_USER_PATH1);
   if (!testdir(nssdir) && mkdir(nssdir, 0760)) {
	PORT_Free(nssdir);
	return NULL;
   }
   PORT_Strcat(nssdir, NSS_USER_PATH2);
   if (!testdir(nssdir) && mkdir(nssdir, 0760)) {
	PORT_Free(nssdir);
	return NULL;
   }
   return nssdir;
}
