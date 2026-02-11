parse_uevent(const fileinfo *cfile) {
  char *equals= strchr(batlinebuf,'=');
  if (!equals)
    return batfailf("line without a equals");
  *equals= 0;
  batlinevalue = equals+1;

  const batinfo_field *field;
  for (field=cfile->extra; field->label; field++) {
    if (!strcmp(field->label,batlinebuf))
      goto found;
  }
  return 0;

 found:
  return parse_value(cfile, field);
}
