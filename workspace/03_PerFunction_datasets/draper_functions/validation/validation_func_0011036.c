inherit_env()
{
   if (inherit_environ == -1) {


      char *inherit = search_conf_val("inherit_env");

      if (inherit != NULL) {
         inherit_environ = (strcmp(inherit, "1") == 0);
      }
      else {

         inherit_environ = true;
      }
   }

   return (inherit_environ == 1) ? true : false;
}
