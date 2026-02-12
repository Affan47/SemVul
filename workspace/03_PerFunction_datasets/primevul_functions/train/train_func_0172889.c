void set_sid_cookie(LOGBOOK *lbs, char *sid, char *full_name) {
   char str[256], lb_name[256], exp[80];
   BOOL global;

   rsprintf("HTTP/1.1 302 Found\r\n");
   rsprintf("Server: ELOG HTTP %s-%s\r\n", VERSION, git_revision());
   if (keep_alive) {
      rsprintf("Connection: Keep-Alive\r\n");
      rsprintf("Keep-Alive: timeout=60, max=10\r\n");
   }

   if (lbs)
      strcpy(lb_name, lbs->name);
   else
      strcpy(lb_name, "global");


   if (getcfg(lb_name, "Login expiration", str, sizeof(str)) || atof(str) > 0)
      strcpy(exp, str);
   else if (isparam("remember")) {
      strcpy(exp, "744");
   } else
      exp[0] = 0;


   global = getcfg("global", "Password file", str, sizeof(str));


   set_cookie(lbs, "sid", sid, global, exp);


   set_cookie(lbs, "ufnm", full_name, global, exp);


   if (isparam("remember"))
      set_cookie(lbs, "urem", "1", global, "8760");
   else
      set_cookie(lbs, "urem", "0", global, "8760");

   set_redir(lbs, isparam("redir") ? getparam("redir") : "");
}
