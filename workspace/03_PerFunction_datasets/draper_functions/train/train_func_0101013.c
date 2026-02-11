_evas_gl_common_version_check()
{
   char *version;
   char *tmp;
   char *tmp2;
   int major;
   int minor;


   version = (char *)glGetString(GL_VERSION);


   if ((tmp = strstr(version, "OpenGL ES-CM ")) || (tmp = strstr(version, "OpenGL ES-CL ")))
     {

        return 0;
     }


   if ((tmp = strstr(version, "OpenGL ES ")))
     {

        return 1;
     }


   version = strdup(version);
   if (!version)
     return 0;

   tmp = strchr(version, '.');

   *tmp = '\0';
   major = atoi(version);

   tmp2 = ++tmp;
   while ((*tmp != '.') && (*tmp != ' ') && (*tmp != '\0'))
     tmp++;


   *tmp = '\0';
   minor = atoi(tmp2);
   free(version);

   if (((major == 1) && (minor >= 4)) || (major >= 2))
     return 1;

   return 0;
}
