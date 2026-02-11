handle_hsc_export(HSCPRC * hp, HSCTAG * tag) {
   STRPTR filename = get_vartext_byname(tag->attr, "FILE");
   STRPTR data = get_vartext_byname(tag->attr, "DATA");
   BOOL append = get_varbool_byname(tag->attr, "APPEND");
   BOOL relsrc = get_varbool_byname(tag->attr, "RELSRC");
   EXPSTR *real_filename = init_estr(1);

   if (filename && data) {
      FILE *outfile = NULL;
      STRPTR writemode = "w";

      if (append)
         writemode = "a";

      if(relsrc)
         set_estr(real_filename,get_vartext(find_varname(hp->defattr,"HSC.SOURCE.PATH")));
      else
         clr_estr(real_filename);
      app_estr(real_filename,filename);
      errno = 0;
      outfile = fopen(estr2str(real_filename), writemode);
      if (outfile) {
         fwrite(data, sizeof(char), strlen(data), outfile);
         fclose(outfile);
      }

      if (errno) {
         hsc_message(hp, MSG_IOERROR, "error opening/writing %q: %s",
               estr2str(real_filename), strerror(errno));
      }
   } else {
      panic("attribute missing");
   }
   del_estr(real_filename);
   return (FALSE);
}
