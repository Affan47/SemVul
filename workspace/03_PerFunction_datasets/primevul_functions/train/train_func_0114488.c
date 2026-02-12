bool getdata_pair(IStream & in, DataPair & d, String & buf)
  {
    char * p;


    do {
      buf.clear();
      buf.append('\0');
      if (!in.append_line(buf)) return false;
      d.line_num++;
      p = buf.mstr() + 1;
      while (*p == ' ' || *p == '\t') ++p;
    } while (*p == '#' || *p == '\0');


    d.key.str = p;
    while (*p != '\0' &&
           ((*p != ' ' && *p != '\t' && *p != '#') || *(p-1) == '\\')) ++p;
    d.key.size = p - d.key.str;


    d.value.str = p;
    d.value.size = 0;
    if (*p == '#' || *p == '\0') {*p = '\0'; return true;}
    *p = '\0';


    ++p;
    while (*p == ' ' || *p == '\t') ++p;
    if (*p == '\0' || *p == '#') {return true;}


    d.value.str = p;
    while (*p != '\0' && (*p != '#' || *(p-1) == '\\')) ++p;


    --p;
    while (*p == ' ' || *p == '\t') --p;
    if (*p == '\\' && *(p + 1) != '\0') ++p;
    ++p;
    d.value.size = p - d.value.str;
    *p = '\0';

    return true;
  }
