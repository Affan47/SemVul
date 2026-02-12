std::string t_go_generator::camelcase(const std::string& value) const {
  std::string value2(value);
  std::setlocale(LC_ALL, "C");


  fix_common_initialism(value2, 0);


  for (std::string::size_type i = 1; i < value2.size() - 1; ++i) {
    if (value2[i] == '_') {
      if (islower(value2[i + 1])) {
        value2.replace(i, 2, 1, toupper(value2[i + 1]));
      }
      fix_common_initialism(value2, i);
    }
  }

  return value2;
}
