init_sendfax_parms(void) {


  efax_parms_vec = prog_config.parms;


  struct std::tm* time_p;
  std::time_t time_count;

  std::time(&time_count);
  time_p = std::localtime(&time_count);

  char date_string[150];


  const char format[] = "%Y-%m-%d %H:%M";
  std::strftime(date_string, sizeof(date_string), format, time_p);

  std::string temp("-h");
  temp += date_string;
  temp += "    ";
  temp += prog_config.my_name;

  temp += " (";
  temp += prog_config.my_number + ") --> ";
  if (prog_config.addr_in_header) temp += last_fax_item_sent.number;
  temp += "      %d/%d";
  efax_parms_vec.push_back(temp);

  if (last_fax_item_sent.number.empty()) {
    efax_parms_vec.push_back("-jX3");
    efax_parms_vec.push_back("-t");
    efax_parms_vec.push_back("");
  }
  else {
    temp = "-t";
    if (prog_config.tone_dial) temp += 'T';
    else temp += 'P';
    temp += last_fax_item_sent.number;
    efax_parms_vec.push_back(temp);
  }
}
