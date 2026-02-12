void build_ref(char *ref, int size, char *mode, char *expand, char *attach, char *new_entries) {
   char str[1000], *p;

   if (strchr(getparam("cmdline"), '?'))
      strlcat(ref, strchr(getparam("cmdline"), '?'), size);


   if (strstr(ref, "cmd=Search&")) {
      strlcpy(str, strstr(ref, "cmd=Search&") + 11, sizeof(str));
      p = strstr(ref, "cmd=Search&");
      strlcpy(p, str, size - (p - ref));
   }


   if (strstr(ref, "id=")) {
      strlcpy(str, ref, sizeof(str));
      p = strstr(str, "id=") + 3;
      while (*p && isdigit(*p))
         p++;
      strlcpy(strstr(ref, "id="), p, size);
      if (strlen(ref) > 0 && ref[strlen(ref) - 1] == '?')
         ref[strlen(ref) - 1] = 0;
   }


   if (mode[0])
      subst_param(ref, size, "mode", mode);


   if (expand[0])
      subst_param(ref, size, "expand", expand);


   if (attach[0])
      subst_param(ref, size, "attach", attach);


   if (new_entries[0])
      subst_param(ref, size, "new_entries", new_entries);


   if (isparam("last"))
      subst_param(ref, size, "last", getparam("last"));


   strlcpy(str, ref, sizeof(str));
   strencode2(ref, str, size);
}
