BOOL is_user_allowed(LOGBOOK *lbs, char *command) {
   char str[1000], users[2000];
   char list[MAX_N_LIST][NAME_LENGTH];
   int i, n;


   if (!getcfg(lbs->name, "Password file", str, sizeof(str)))
      return TRUE;


   sprintf(str, "Deny %s", command);
   if (getcfg(lbs->name, str, users, sizeof(users))) {

      if (!isparam("unm"))
         return FALSE;


      n = strbreak(users, list, MAX_N_LIST, ",", FALSE);
      for (i = 0; i < n; i++)
         if (strieq(list[i], getparam("unm")))
            break;

      if (i < n)
         return FALSE;
   }


   if (strieq(command, loc("Admin"))) {
      if (getcfg(lbs->name, "Admin user", str, sizeof(str))) {
         return is_admin_user(lbs, getparam("unm"));
      }
   }


   sprintf(str, "Allow %s", command);
   if (!getcfg(lbs->name, str, users, sizeof(users)))
      return TRUE;


   if (!isparam("unm"))
      return FALSE;

   n = strbreak(users, list, MAX_N_LIST, ",", FALSE);
   for (i = 0; i < n; i++)
      if (strieq(list[i], getparam("unm")))
         return TRUE;

   return FALSE;
}
