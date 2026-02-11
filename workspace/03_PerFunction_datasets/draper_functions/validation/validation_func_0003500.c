password_read_file(char **users[], char**encryped_pwds[], const char *filename)
{
   struct saved_vars_s *context;
   int    j;
   int    ret = 0;
   FILE   *fp = NULL;
   char   *uname = NULL;
   char   *pwd = NULL;
   char   input[MAX_LINE_LENGTH];
   bool   do_loop = true;
   size_t size = 0;
   int    i = 0;

   DENTER(TOP_LAYER, "password_read_file");
   fp = fopen(filename, "r");
   if (fp != NULL) {
      size = password_get_size(filename);
      if (size == -1){

         ret = 2;
         size = 0;
         do_loop = false;
      }
      size = size + 2;
      *users = malloc(size * sizeof(char*));
      *encryped_pwds = malloc(size * sizeof(char*));

      while (do_loop) {
         uname = NULL;
         pwd = NULL;
         context = NULL;

         if (fscanf(fp, "%[^\n]\n", input) == 1) {
            uname = sge_strtok_r(input, " ", &context);
            pwd = sge_strtok_r(NULL, " ", &context);
            if ((uname == NULL) || (pwd == NULL)){
                do_loop = false;

                ret = 2;
                do_loop = false;
            } else {
               (*users)[i] = strdup(uname);
               (*encryped_pwds)[i] = strdup(pwd);
               i++;
            }
         } else {
            do_loop = false;
         }
         sge_free_saved_vars(context);
      }
      if (ret == 2) {
         for (j=0; j<i; j++) {
            free((*users)[j]);
            free((*encryped_pwds)[j]);
         }
         free(*users);
         free(*encryped_pwds);
         DPRINTF(("sgepasswd file is corrupted"));
      } else {
         (*users)[i] = NULL;
         (*encryped_pwds)[i] = NULL; i++;
         (*users)[i] = NULL;
         (*encryped_pwds)[i] = NULL; i++;
      }

      FCLOSE(fp);
   } else {
      *users = malloc(2 * sizeof(char*));
      *encryped_pwds = malloc(2 * sizeof(char*));
      (*users)[0] = NULL;
      (*encryped_pwds)[0] = NULL;
      (*users)[1] = NULL;
      (*encryped_pwds)[1] = NULL;


      ret = 1;
   }
   DEXIT;
   return ret;
FCLOSE_ERROR:
   DEXIT;
   return 1;
}
