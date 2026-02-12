gb18030_left_adjust_char_head(const UChar* start, const UChar* s)
{
  const UChar *p;
  enum state state = S_START;

  DEBUG_GB18030(("----------------\n"));
  for (p = s; p >= start; p--) {
    DEBUG_GB18030(("state %d --(%02x)-->\n", state, *p));
    switch (state) {
    case S_START:
      switch (GB18030_MAP[*p]) {
      case C1:
        return (UChar *)s;
      case C2:
        state = S_one_C2;
        break;
      case C4:
        state = S_one_C4;
        break;
      case CM:
        state = S_one_CM;
        break;
      }
      break;
    case S_one_C2:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)s;
      case CM:
        state = S_odd_CM_one_CX;
        break;
      }
      break;
    case S_one_C4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)s;
      case CM:
        state = S_one_CMC4;
        break;
      }
      break;
    case S_one_CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
        return (UChar *)s;
      case C4:
        state = S_odd_C4CM;
        break;
      case CM:
        state = S_odd_CM_one_CX;
        break;
      }
      break;

    case S_odd_CM_one_CX:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 1);
      case CM:
        state = S_even_CM_one_CX;
        break;
      }
      break;
    case S_even_CM_one_CX:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)s;
      case CM:
        state = S_odd_CM_one_CX;
        break;
      }
      break;

    case S_one_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
        return (UChar *)(s - 1);
      case C4:
        state = S_one_C4_odd_CMC4;
        break;
      case CM:
        state = S_even_CM_one_CX;
        break;
      }
      break;
    case S_odd_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
        return (UChar *)(s - 1);
      case C4:
        state = S_one_C4_odd_CMC4;
        break;
      case CM:
        state = S_odd_CM_odd_CMC4;
        break;
      }
      break;
    case S_one_C4_odd_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 1);
      case CM:
        state = S_even_CMC4;
        break;
      }
      break;
    case S_even_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
        return (UChar *)(s - 3);
      case C4:
        state = S_one_C4_even_CMC4;
        break;
      case CM:
        state = S_odd_CM_even_CMC4;
        break;
      }
      break;
    case S_one_C4_even_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 3);
      case CM:
        state = S_odd_CMC4;
        break;
      }
      break;

    case S_odd_CM_odd_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 3);
      case CM:
        state = S_even_CM_odd_CMC4;
        break;
      }
      break;
    case S_even_CM_odd_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 1);
      case CM:
        state = S_odd_CM_odd_CMC4;
        break;
      }
      break;

    case S_odd_CM_even_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 1);
      case CM:
        state = S_even_CM_even_CMC4;
        break;
      }
      break;
    case S_even_CM_even_CMC4:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 3);
      case CM:
        state = S_odd_CM_even_CMC4;
        break;
      }
      break;

    case S_odd_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)s;
      case CM:
        state = S_one_CM_odd_C4CM;
        break;
      }
      break;
    case S_one_CM_odd_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
        return (UChar *)(s - 2);
      case C4:
        state = S_even_C4CM;
        break;
      case CM:
        state = S_even_CM_odd_C4CM;
        break;
      }
      break;
    case S_even_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 2);
      case CM:
        state = S_one_CM_even_C4CM;
        break;
      }
      break;
    case S_one_CM_even_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
        return (UChar *)(s - 0);
      case C4:
        state = S_odd_C4CM;
        break;
      case CM:
        state = S_even_CM_even_C4CM;
        break;
      }
      break;

    case S_even_CM_odd_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 0);
      case CM:
        state = S_odd_CM_odd_C4CM;
        break;
      }
      break;
    case S_odd_CM_odd_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 2);
      case CM:
        state = S_even_CM_odd_C4CM;
        break;
      }
      break;

    case S_even_CM_even_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 2);
      case CM:
        state = S_odd_CM_even_C4CM;
        break;
      }
      break;
    case S_odd_CM_even_C4CM:
      switch (GB18030_MAP[*p]) {
      case C1:
      case C2:
      case C4:
        return (UChar *)(s - 0);
      case CM:
        state = S_even_CM_even_C4CM;
        break;
      }
      break;
    }
  }

  DEBUG_GB18030(("state %d\n", state));
  switch (state) {
  case S_START:             return (UChar *)(s - 0);
  case S_one_C2:            return (UChar *)(s - 0);
  case S_one_C4:            return (UChar *)(s - 0);
  case S_one_CM:            return (UChar *)(s - 0);

  case S_odd_CM_one_CX:     return (UChar *)(s - 1);
  case S_even_CM_one_CX:    return (UChar *)(s - 0);

  case S_one_CMC4:          return (UChar *)(s - 1);
  case S_odd_CMC4:          return (UChar *)(s - 1);
  case S_one_C4_odd_CMC4:   return (UChar *)(s - 1);
  case S_even_CMC4:         return (UChar *)(s - 3);
  case S_one_C4_even_CMC4:  return (UChar *)(s - 3);

  case S_odd_CM_odd_CMC4:   return (UChar *)(s - 3);
  case S_even_CM_odd_CMC4:  return (UChar *)(s - 1);

  case S_odd_CM_even_CMC4:  return (UChar *)(s - 1);
  case S_even_CM_even_CMC4: return (UChar *)(s - 3);

  case S_odd_C4CM:          return (UChar *)(s - 0);
  case S_one_CM_odd_C4CM:   return (UChar *)(s - 2);
  case S_even_C4CM:         return (UChar *)(s - 2);
  case S_one_CM_even_C4CM:  return (UChar *)(s - 0);

  case S_even_CM_odd_C4CM:  return (UChar *)(s - 0);
  case S_odd_CM_odd_C4CM:   return (UChar *)(s - 2);
  case S_even_CM_even_C4CM: return (UChar *)(s - 2);
  case S_odd_CM_even_C4CM:  return (UChar *)(s - 0);
  }

  return (UChar* )s;
}
