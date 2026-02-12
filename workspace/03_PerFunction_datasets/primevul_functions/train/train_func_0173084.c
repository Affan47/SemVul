void get_auto_index(LOGBOOK *lbs, int index, char *format, char *retstr, int size)


{
   int i, message_id, loc, len, old_index;
   char *p, attrib[MAX_N_ATTR][NAME_LENGTH], att[MAX_ATTACHMENTS][256], draft[256];
   time_t now;

   if (strchr(format, '%') == NULL && strchr(format, '#') == NULL) {
      strlcpy(retstr, format, size);
      return;
   }

   time(&now);
   my_strftime(retstr, size, format, localtime(&now));

   p = strchr(retstr, '#');
   if (p == NULL)
      return;

   if (p > retstr && *(p - 1) == '\\') {
      memmove(p - 1, p, strlen(p) + 1);
      return;
   }


   for (i = loc = 0, len = 1; i < (int) strlen(retstr); i++) {
      if (retstr[i] == '#') {
         if (loc == 0)
            loc = i;
         if (i > 0 && retstr[i - 1] == '#')
            len++;
      }
   }


   message_id = el_search_message(lbs, EL_LAST, 0, FALSE);

   if (!message_id) {

      sprintf(retstr + loc, "%0*d", len, 1);
      return;
   }


   old_index = 0;
   do {
      el_retrieve(lbs, message_id, NULL, attr_list, attrib, lbs->n_attr, NULL, 0, NULL, NULL, att, NULL,
                  NULL, draft);


      if (strlen(attrib[index]) > 0 && strncmp(attrib[index], retstr, loc) == 0)
         if (atoi(attrib[index] + loc) > old_index)
            old_index = atoi(attrib[index] + loc);

      message_id = el_search_message(lbs, EL_PREV, message_id, FALSE);

   } while (message_id);


   sprintf(retstr + loc, "%0*d", len, old_index + 1);
}
