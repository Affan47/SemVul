Variant php_split(const String& spliton, const String& str, int count,
                  bool icase) {
  const char* strp = str.data();
  const char* endp = strp + str.size();

  regex_t re;
  int copts = icase ? REG_ICASE : 0;
  int err = regcomp(&re, spliton.data(), REG_EXTENDED | copts);
  if (err) {
    php_reg_eprint(err, &re);
    return false;
  }

  Array return_value = Array::CreateVArray();
  regmatch_t subs[1];


  while ((count == -1 || count > 1) &&
         !(err = regexec(&re, strp, 1, subs, 0))) {
    if (subs[0].rm_so == 0 && subs[0].rm_eo) {

      return_value.append("");

      strp += subs[0].rm_eo;
    } else if (subs[0].rm_so == 0 && subs[0].rm_eo == 0) {

      regfree(&re);
      raise_warning("Invalid Regular Expression to split()");
      return false;
    } else {


      int size = subs[0].rm_so;


      return_value.append(String(strp, size, CopyString));


      strp = strp + subs[0].rm_eo;
    }


    if (count != -1) {
      count--;
    }
  }


  if (err && err != REG_NOMATCH) {
    php_reg_eprint(err, &re);
    regfree(&re);
    return false;
  }


  int size = endp - strp;
  return_value.append(String(strp, size, CopyString));

  regfree(&re);
  return return_value;
}
