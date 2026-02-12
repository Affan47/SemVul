String string_soundex(const String& str) {
  assertx(!str.empty());
  int _small, code, last;
  String retString(4, ReserveString);
  char* soundex = retString.mutableData();

  static char soundex_table[26] = {
    0,
    '1',
    '2',
    '3',
    0,
    '1',
    '2',
    0,
    0,
    '2',
    '2',
    '4',
    '5',
    '5',
    0,
    '1',
    '2',
    '6',
    '2',
    '3',
    0,
    '1',
    0,
    '2',
    0,
    '2'
  };


  last = -1;
  auto p = str.slice().data();
  for (_small = 0; *p && _small < 4; p++) {


    code = toupper((int)(unsigned char)(*p));
    if (code >= 'A' && code <= 'Z') {
      if (_small == 0) {

        soundex[_small++] = code;
        last = soundex_table[code - 'A'];
      } else {


        code = soundex_table[code - 'A'];
        if (code != last) {
          if (code != 0) {
            soundex[_small++] = code;
          }
          last = code;
        }
      }
    }
  }

  while (_small < 4) {
    soundex[_small++] = '0';
  }
  retString.setSize(4);
  return retString;
}
