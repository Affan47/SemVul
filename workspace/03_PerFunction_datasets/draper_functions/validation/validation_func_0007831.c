extract_conv_spec(CORD_pos source, char *buf,
                             int * width, int *prec, int *left, int * long_arg)
{
    register int result = 0;
    register int current_number = 0;
    register int saw_period = 0;
    register int saw_number = 0;
    register int chars_so_far = 0;
    register char current;

    *width = NONE;
    buf[chars_so_far++] = '%';
    while(CORD_pos_valid(source)) {
        if (chars_so_far >= CONV_SPEC_LEN) return(-1);
        current = CORD_pos_fetch(source);
        buf[chars_so_far++] = current;
        switch(current) {
          case '*':
            saw_number = 1;
            current_number = VARIABLE;
            break;
          case '0':
            if (!saw_number) {

                break;
            }
          case '1':
          case '2':
          case '3':
          case '4':
          case '5':
          case '6':
          case '7':
          case '8':
          case '9':
            saw_number = 1;
            current_number *= 10;
            current_number += current - '0';
            break;
          case '.':
            saw_period = 1;
            if(saw_number) {
                *width = current_number;
                saw_number = 0;
            }
            current_number = 0;
            break;
          case 'l':
          case 'L':
            *long_arg = 1;
            current_number = 0;
            break;
          case 'h':
            *long_arg = -1;
            current_number = 0;
            break;
          case ' ':
          case '+':
          case '#':
            current_number = 0;
            break;
          case '-':
            *left = 1;
            current_number = 0;
            break;
          case 'd':
          case 'i':
          case 'o':
          case 'u':
          case 'x':
          case 'X':
          case 'f':
          case 'e':
          case 'E':
          case 'g':
          case 'G':
          case 'c':
          case 'C':
          case 's':
          case 'S':
          case 'p':
          case 'n':
          case 'r':
            goto done;
          default:
            return(-1);
        }
        CORD_next(source);
    }
    return(-1);
  done:
    if (saw_number) {
        if (saw_period) {
            *prec = current_number;
        } else {
            *prec = NONE;
            *width = current_number;
        }
    } else {
        *prec = NONE;
    }
    buf[chars_so_far] = '\0';
    return(result);
}
