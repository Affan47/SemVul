parse_fieldlist (char *firstchar, FILE *fp) {
  List_T fieldlist = NULL;
  char Buffer[LINELENGTH], *fieldname, *p;

  while ((*firstchar = fgetc(fp)) != '>') {
    Buffer[0] = *firstchar;
    fgets(&(Buffer[1]),LINELENGTH-1,fp);
    if ((p = rindex(Buffer,'\n')) == NULL) {
      fprintf(stderr,"Line %s exceeds maximum length of %d\n",Buffer,LINELENGTH);
      exit(9);
    } else {
      *p = '\0';
    }
    fieldname = (char *) CALLOC(strlen(Buffer)+1,sizeof(char));
    strcpy(fieldname,Buffer);
    fieldlist = List_push(fieldlist,fieldname);
  }

  return List_reverse(fieldlist);
}
