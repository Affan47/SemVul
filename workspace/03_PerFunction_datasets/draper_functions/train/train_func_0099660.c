minorCode2String(const minorCodeLookup table[], CORBA::ULong code) {
  int i = 0;

  while (table[i].value != code) {
    if (table[i].name)
      i++;
    else
      break;
  }
  return table[i].name;
}
