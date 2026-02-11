_bin_to_base64(unsigned char *dest, const unsigned char source[3],
    int len) {
  switch (len) {
    case 1:
      dest[0] = alphabet[(source[0] >> 2)];
      dest[1] = alphabet[((source[0] & BITS(2)) << 4)];
      dest[2] = '=';
      dest[3] = '=';
      break;
    case 2:
      dest[0] = alphabet[source[0] >> 2];
      dest[1] = alphabet[(source[1] >> 4) | ((source[0] & BITS(2)) << 4)];
      dest[2] = alphabet[(source[1] & BITS(4)) << 2];
      dest[3] = '=';
      break;
    case 3:
      dest[0] = alphabet[(source[0] >> 2)];
      dest[1] = alphabet[(source[1] >> 4) | ((source[0] & BITS(2)) << 4)];
      dest[2] = alphabet[ (source[2] >> 6) | (source[1] & BITS(4)) << 2];
      dest[3] = alphabet[source[2] & BITS(6)];
      break;
  }
}
