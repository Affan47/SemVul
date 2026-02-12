int el_submit(LOGBOOK *lbs, int message_id, BOOL bedit, char *date, char attr_name[MAX_N_ATTR][NAME_LENGTH],
              char attr_value[MAX_N_ATTR][NAME_LENGTH], int n_attr, char *text, char *in_reply_to,
              char *reply_to, char *encoding, char afilename[MAX_ATTACHMENTS][256], BOOL mark_original,
              char *locked_by, char *draft)


{
   int n, i, j, size, fh, index, tail_size, orig_size, delta, reply_id;
   char file_name[MAX_PATH_LENGTH * 3], dir[256], str[NAME_LENGTH], date1[256], attrib[MAX_N_ATTR][NAME_LENGTH],
           reply_to1[MAX_REPLY_TO * 10], in_reply_to1[MAX_REPLY_TO * 10], encoding1[80], *message, *p,
           *old_text, *buffer, locked_by1[256];
   char attachment_all[64 * MAX_ATTACHMENTS], subdir[MAX_PATH_LENGTH];
   time_t ltime;

   tail_size = orig_size = 0;

   buffer = NULL;
   message = xmalloc(TEXT_SIZE + 100);
   old_text = NULL;
   memcpy(attrib, attr_value, sizeof(attrib));
   strlcpy(reply_to1, reply_to, sizeof(reply_to1));
   strlcpy(in_reply_to1, in_reply_to, sizeof(in_reply_to1));
   strlcpy(encoding1, encoding, sizeof(encoding1));
   strlcpy(date1, date, sizeof(date1));
   if (locked_by)
      strlcpy(locked_by1, locked_by, sizeof(locked_by1));
   else
      locked_by1[0] = 0;


   strcpy(dir, lbs->data_dir);

   if (bedit) {

      for (index = 0; index < *lbs->n_el_index; index++)
         if (lbs->el_index[index].message_id == message_id)
            break;

      if (index == *lbs->n_el_index) {
         xfree(message);
         return -1;
      }

      snprintf(file_name, sizeof(file_name), "%s%s%s", lbs->data_dir, lbs->el_index[index].subdir,
               lbs->el_index[index].file_name);
      fh = open(file_name, O_CREAT | O_RDWR | O_BINARY, 0644);
      if (fh < 0) {
         xfree(message);
         return -1;
      }

      lseek(fh, lbs->el_index[index].offset, SEEK_SET);
      i = my_read(fh, message, TEXT_SIZE + 100 - 1);
      if (i >= 0)
         message[i] = 0;
      else
         message[0] = 0;


      if (strncmp(message, "$@MID@$:", 8) != 0) {
         close(fh);
         xfree(message);


         el_build_index(lbs, TRUE);
         return el_submit(lbs, message_id, bedit, date, attr_name, attrib, n_attr, text, in_reply_to,
                          reply_to, encoding, afilename, mark_original, locked_by, draft);
      }


      if (atoi(message + 8) != message_id) {
         close(fh);
         xfree(message);
         return -1;
      }


      p = strstr(message + 8, "$@MID@$:");
      if (p == NULL)
         size = strlen(message);
      else
         size = p - message;

      message[size] = 0;

      if (strcmp(text, "<keep>") == 0) {

         p = strstr(message, "========================================\n");

         if (p == NULL)
            p = strstr(message, "========================================\r");
         if (p) {
            p += 41;
            old_text = xmalloc(size + 1);
            strlcpy(old_text, p, size);
            if (old_text[strlen(old_text) - 1] == '\n' || old_text[strlen(old_text) - 1] == '\r')
               old_text[strlen(old_text) - 1] = 0;
         }
      }

      if (strieq(date1, "<keep>"))
         el_decode(message, "Date: ", date1, sizeof(date1));
      else
         strlcpy(date1, date, sizeof(date1));
      if (strieq(locked_by1, "<keep>"))
         el_decode_intlist(message, "Locked by: ", locked_by1, sizeof(locked_by1));
      if (strieq(reply_to1, "<keep>"))
         el_decode_intlist(message, "Reply to: ", reply_to1, sizeof(reply_to1));
      if (strieq(in_reply_to1, "<keep>"))
         el_decode_int(message, "In reply to: ", in_reply_to1, sizeof(in_reply_to1));
      if (strieq(encoding1, "<keep>"))
         el_decode(message, "Encoding: ", encoding1, sizeof(encoding1));
      el_decode(message, "Attachment: ", attachment_all, sizeof(attachment_all));

      for (i = 0; i < n_attr; i++) {
         sprintf(str, "%s: ", attr_name[i]);
         if (strieq(attrib[i], "<keep>"))
            el_decode(message, str, attrib[i], NAME_LENGTH);
      }


      lseek(fh, 0, SEEK_END);
      orig_size = size;
      tail_size = TELL(fh) - (lbs->el_index[index].offset + size);

      if (tail_size > 0) {
         buffer = xmalloc(tail_size);

         lseek(fh, lbs->el_index[index].offset + size, SEEK_SET);
         n = my_read(fh, buffer, tail_size);
      }
      lseek(fh, lbs->el_index[index].offset, SEEK_SET);
   } else {

      if (!date[0]) {
         get_rfc2822_date(date1, sizeof(date1), 0);
         ltime = date_to_ltime(date1);
      } else {
         ltime = date_to_ltime(date);
         get_rfc2822_date(date1, sizeof(date1), ltime);
      }

      for (i = 0; i < 12; i++)
         if (strncmp(date1 + 8, mname[i], 3) == 0)
            break;

      snprintf(file_name, sizeof(file_name), "%c%c%02d%c%ca.log", date1[14], date1[15], i + 1, date1[5], date1[6]);

      generate_subdir_name(file_name, subdir, sizeof(subdir));
      sprintf(str, "%s%s", dir, subdir);
      if (strlen(str) > 0 && str[strlen(str) - 1] == DIR_SEPARATOR)
         str[strlen(str) - 1] = 0;

#ifdef OS_WINNT
      mkdir(str);
#else
      mkdir(str, 0755);
#endif

      sprintf(str, "%s%s%s", dir, subdir, file_name);
      fh = open(str, O_CREAT | O_RDWR | O_BINARY, 0644);
      if (fh < 0) {
         xfree(message);
         if (old_text)
            xfree(old_text);
         return -1;
      }

      lseek(fh, 0, SEEK_END);


      if (message_id == 0) {
         message_id = 1;
         for (i = 0; i < *lbs->n_el_index; i++)
            if (lbs->el_index[i].message_id >= message_id)
               message_id = lbs->el_index[i].message_id + 1;
      }


      index = *lbs->n_el_index;

      (*lbs->n_el_index)++;
      lbs->el_index = xrealloc(lbs->el_index, sizeof(EL_INDEX) * (*lbs->n_el_index));
      lbs->el_index[index].message_id = message_id;
      strlcpy(lbs->el_index[index].file_name, file_name, sizeof(lbs->el_index[index].file_name));
      strlcpy(lbs->el_index[index].subdir, subdir, sizeof(lbs->el_index[index].subdir));
      lbs->el_index[index].file_time = ltime;
      lbs->el_index[index].offset = TELL(fh);
      lbs->el_index[index].in_reply_to = atoi(in_reply_to1);


      i = *lbs->n_el_index;
      if (i > 1 && lbs->el_index[i - 1].file_time < lbs->el_index[i - 2].file_time) {
         qsort(lbs->el_index, i, sizeof(EL_INDEX), eli_compare);


         for (index = 0; index < *lbs->n_el_index; index++)
            if (lbs->el_index[index].message_id == message_id)
               break;
      }


      for (i = 0; lb_list[i].name[0]; i++)
         if (&lb_list[i] != lbs && lb_list[i].n_el_index == lbs->n_el_index)
            lb_list[i].el_index = lbs->el_index;
   }


   sprintf(message, "$@MID@$: %d\n", message_id);
   sprintf(message + strlen(message), "Date: %s\n", date1);

   if (reply_to1[0])
      sprintf(message + strlen(message), "Reply to: %s\n", reply_to1);

   if (in_reply_to1[0])
      sprintf(message + strlen(message), "In reply to: %s\n", in_reply_to1);

   for (i = 0; i < n_attr; i++)
      sprintf(message + strlen(message), "%s: %s\n", attr_name[i], attrib[i]);

   sprintf(message + strlen(message), "Attachment: ");

   if (afilename) {
      sprintf(message + strlen(message), "%s", afilename[0]);
      for (i = 1; i < MAX_ATTACHMENTS; i++)
         if (afilename[i][0])
            sprintf(message + strlen(message), ",%s", afilename[i]);
   }
   sprintf(message + strlen(message), "\n");

   sprintf(message + strlen(message), "Encoding: %s\n", encoding1);
   if (locked_by1[0])
      sprintf(message + strlen(message), "Locked by: %s\n", locked_by1);
   if (draft && draft[0])
      sprintf(message + strlen(message), "Draft: %s\n", draft);

   sprintf(message + strlen(message), "========================================\n");

   if (strieq(text, "<keep>") && old_text)
      strlcat(message, old_text, TEXT_SIZE + 100);
   else
      strlcat(message, text, TEXT_SIZE + 100);
   strlcat(message, "\n", TEXT_SIZE + 100);

   if (old_text)
      xfree(old_text);

   n = write(fh, message, strlen(message));
   if (n != (int) strlen(message)) {
      if (tail_size > 0)
         xfree(buffer);
      close(fh);
      return -1;
   }


   MD5_checksum(message, strlen(message), lbs->el_index[index].md5_digest);

   if (bedit) {
      if (tail_size > 0) {
         n = write(fh, buffer, tail_size);
         xfree(buffer);


         delta = strlen(message) - orig_size;

         for (i = 0; i < *lbs->n_el_index; i++)
            if (lbs->el_index[i].message_id == message_id)
               break;

         for (j = i + 1; j < *lbs->n_el_index && strieq(lbs->el_index[i].file_name,
                                                        lbs->el_index[j].file_name); j++)
            lbs->el_index[j].offset += delta;
      }


      TRUNCATE(fh);
   }

   close(fh);


   reply_id = atoi(in_reply_to);

   if (mark_original && in_reply_to[0] && !bedit && atoi(in_reply_to) > 0) {
      char date[80], attr[MAX_N_ATTR][NAME_LENGTH], enc[80], att[MAX_ATTACHMENTS][256],
              reply_to[MAX_REPLY_TO * 10], in_reply_to[MAX_REPLY_TO * 10], lock[256], draft[256];


      size = TEXT_SIZE + 100;
      el_retrieve(lbs, reply_id, date, attr_list, attr, n_attr, message, &size, in_reply_to, reply_to, att,
                  enc, lock, draft);

      if (reply_to[0])
         strcat(reply_to, ", ");
      sprintf(reply_to + strlen(reply_to), "%d", message_id);


      el_submit(lbs, reply_id, TRUE, date, attr_list, attr, n_attr, message, in_reply_to, reply_to, enc, att,
                TRUE, lock, draft);
   }

   xfree(message);
   return message_id;
}
