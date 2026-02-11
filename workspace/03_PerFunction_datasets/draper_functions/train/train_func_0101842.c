_e_fm2_uri_parse(const char *val)
{
   E_Fm2_Uri *uri;
   const char *p;
   char hostname[PATH_MAX], path[PATH_MAX];
   int i = 0;


   if (val[0] == '/')
     {
        uri = E_NEW(E_Fm2_Uri, 1);
        uri->hostname = NULL;
        uri->path = eina_stringshare_add(val);
        return uri;
     }


   if (strlen(val) <= 7 && strncmp(val, "file://", 7)) return NULL;
   memset(path, 0, PATH_MAX);


   p = val + 7;
   if (*p != '/')
     {
        for (i = 0; *p != '/' && *p != '\0' && i < _POSIX_HOST_NAME_MAX; p++, i++)
          hostname[i] = *p;
     }
   hostname[i] = '\0';


   for (i = 0; (*p != '\0') && (i < (PATH_MAX-1)); i++, p++)
     {
        if (*p == '%')
          {
             path[i] = *(++p);
             path[i + 1] = *(++p);
             path[i] = (char)strtol(&(path[i]), NULL, 16);
             path[i + 1] = '\0';
          }
        else
          path[i] = *p;
     }

   uri = E_NEW(E_Fm2_Uri, 1);
   if (hostname[0]) uri->hostname = eina_stringshare_add(hostname);
   else uri->hostname = NULL;
   uri->path = eina_stringshare_add(path);

   return uri;
}
