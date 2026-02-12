check_token(unsigned long token)
{
  int result;
  unsigned long pos;

  if (token < token_base) {

    result = 0;
  } else {
    pos = token - token_base;
    if (pos >= issue_pointer) {

      result = 0;
    } else {
      if (returned_tokens & (1UL << pos)) {

        result = 0;
      } else {

        result = 1;
        returned_tokens |= (1UL << pos);
        if (pos == 0) {
          shift_tokens();
        }
      }
    }
  }

  return result;

}
