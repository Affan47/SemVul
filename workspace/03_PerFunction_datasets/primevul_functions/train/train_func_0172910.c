int getcfg(char *group, char *param, char *value, int vsize)


{
   char str[256];
   int status;


   if (strieq(group, "global") && getcfg_topgroup()) {
      sprintf(str, "global %s", getcfg_topgroup());
      status = getcfg(str, param, value, vsize);
      if (status)
         return status;
   }


   if (_condition[0]) {
      status = getcfg_simple(group, param, value, vsize, TRUE);
      if (status)
         return status;
   }

   status = getcfg_simple(group, param, value, vsize, FALSE);
   if (status)
      return status;


   if (!group || is_logbook(group))
      return getcfg("global", param, value, vsize);

   return 0;
}
