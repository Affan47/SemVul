char convert_char(curl_infotype infotype, char this_char)
{

  switch(infotype) {
  case CURLINFO_DATA_IN:
  case CURLINFO_DATA_OUT:
  case CURLINFO_SSL_DATA_IN:
  case CURLINFO_SSL_DATA_OUT:

    if ((this_char >= 0x20) && (this_char < 0x7f)) {

      convert_from_network(&this_char, 1);
    }
    else {

      return UNPRINTABLE_CHAR;
    }

  default:

    if (ISPRINT(this_char)
        &&  (this_char != '\t')
        &&  (this_char != '\r')
        &&  (this_char != '\n')) {

      return this_char;
    }
    break;
  }

  return UNPRINTABLE_CHAR;
}
