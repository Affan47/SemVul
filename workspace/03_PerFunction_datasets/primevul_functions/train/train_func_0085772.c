String string_metaphone(const char *input, int word_len, long max_phonemes,
                        int traditional) {
  unsigned char *word = (unsigned char *)input;

  int w_idx = 0;
  int max_buffer_len = 0;


  if (max_phonemes < 0)
    return String();


  if (word == nullptr)
    return String();


  if (max_phonemes == 0) {
    max_buffer_len = word_len;
  } else {
    max_buffer_len = max_phonemes;
  }
  StringBuffer buffer(max_buffer_len);


  for (; !isalpha(Curr_Letter); w_idx++) {

    if (Curr_Letter == '\0') {
      return buffer.detach();
    }
  }

  switch (Curr_Letter) {

  case 'A':
    if (Next_Letter == 'E') {
      Phonize('E');
      w_idx += 2;
    }

    else {
      Phonize('A');
      w_idx++;
    }
    break;

  case 'G':
  case 'K':
  case 'P':
    if (Next_Letter == 'N') {
      Phonize('N');
      w_idx += 2;
    }
    break;


  case 'W':
    if (Next_Letter == 'H' ||
      Next_Letter == 'R') {
      Phonize(Next_Letter);
      w_idx += 2;
    } else if (isvowel(Next_Letter)) {
      Phonize('W');
      w_idx += 2;
    }

    break;

  case 'X':
    Phonize('S');
    w_idx++;
    break;


  case 'E':
  case 'I':
  case 'O':
  case 'U':
    Phonize(Curr_Letter);
    w_idx++;
    break;
  default:

    break;
  }


  for (; Curr_Letter != '\0' &&
         (max_phonemes == 0 || Phone_Len < max_phonemes);
       w_idx++) {


    unsigned short int skip_letter = 0;


    if (!isalpha(Curr_Letter))
      continue;


    if (Curr_Letter == Prev_Letter &&
      Curr_Letter != 'C')
      continue;

    switch (Curr_Letter) {

    case 'B':
      if (Prev_Letter != 'M')
        Phonize('B');
      break;


    case 'C':
      if (MAKESOFT(Next_Letter)) {
        if (After_Next_Letter == 'A' &&
          Next_Letter == 'I') {
          Phonize(SH);
        }

        else if (Prev_Letter == 'S') {

        } else {
          Phonize('S');
        }
      } else if (Next_Letter == 'H') {
        if ((!traditional) && (After_Next_Letter == 'R' ||
                               Prev_Letter == 'S')) {
          Phonize('K');
        } else {
          Phonize(SH);
        }
        skip_letter++;
      } else {
        Phonize('K');
      }
      break;


    case 'D':
      if (Next_Letter == 'G' && MAKESOFT(After_Next_Letter)) {
        Phonize('J');
        skip_letter++;
      } else
        Phonize('T');
      break;


    case 'G':
      if (Next_Letter == 'H') {
        if (!(NOGHTOF(Look_Back_Letter(3)) || Look_Back_Letter(4) == 'H')) {
          Phonize('F');
          skip_letter++;
        } else {

        }
      } else if (Next_Letter == 'N') {
        if (Isbreak(After_Next_Letter) ||
            (After_Next_Letter == 'E' && Look_Ahead_Letter(3) == 'D')) {

        } else
          Phonize('K');
      } else if (MAKESOFT(Next_Letter) && Prev_Letter != 'G') {
        Phonize('J');
      } else {
        Phonize('K');
      }
      break;

    case 'H':
      if (isvowel(Next_Letter) && !AFFECTH(Prev_Letter))
        Phonize('H');
      break;


    case 'K':
      if (Prev_Letter != 'C')
        Phonize('K');
      break;


    case 'P':
      if (Next_Letter == 'H') {
        Phonize('F');
      } else {
        Phonize('P');
      }
      break;


    case 'Q':
      Phonize('K');
      break;


    case 'S':
      if (Next_Letter == 'I' &&
          (After_Next_Letter == 'O' || After_Next_Letter == 'A')) {
        Phonize(SH);
      } else if (Next_Letter == 'H') {
        Phonize(SH);
        skip_letter++;
      } else if ((!traditional) &&
                 (Next_Letter == 'C' && Look_Ahead_Letter(2) == 'H' &&
                  Look_Ahead_Letter(3) == 'W')) {
        Phonize(SH);
        skip_letter += 2;
      } else {
        Phonize('S');
      }
      break;


    case 'T':
      if (Next_Letter == 'I' &&
        (After_Next_Letter == 'O' || After_Next_Letter == 'A')) {
        Phonize(SH);
      } else if (Next_Letter == 'H') {
        Phonize(TH);
        skip_letter++;
      } else {
        Phonize('T');
      }
      break;

    case 'V':
      Phonize('F');
      break;

    case 'W':
      if (isvowel(Next_Letter))
        Phonize('W');
      break;

    case 'X':
      Phonize('K');
      Phonize('S');
      break;

    case 'Y':
      if (isvowel(Next_Letter))
        Phonize('Y');
      break;

    case 'Z':
      Phonize('S');
      break;

    case 'F':
    case 'J':
    case 'L':
    case 'M':
    case 'N':
    case 'R':
      Phonize(Curr_Letter);
      break;
    default:

      break;
    }

    w_idx += skip_letter;
  }

  return buffer.detach();
}
