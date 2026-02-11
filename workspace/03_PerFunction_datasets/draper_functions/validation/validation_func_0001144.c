probe_mpsub(char * line)
  {
  float f;
  while(isspace(*line) && (*line != '\0'))
    line++;

  if(!strncmp(line, "FORMAT=TIME", 11) || (sscanf(line, "FORMAT=%f", &f) == 1))
    return 1;
  return 0;
  }
