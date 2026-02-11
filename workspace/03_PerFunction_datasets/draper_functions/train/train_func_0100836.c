mailmime_encoding_parse(const char * message, size_t length,
				   size_t * indx, int * result)
{
  size_t cur_token;
  int encoding;

  cur_token = * indx;

  if (cur_token >= length)
    return MAILIMF_ERROR_PARSE;

  switch ((char) toupper((unsigned char) message[cur_token])) {
  case 'Q':
    encoding = MAILMIME_ENCODING_Q;
    break;
  case 'B':
    encoding = MAILMIME_ENCODING_B;
    break;
  default:
    return MAILIMF_ERROR_INVAL;
  }

  cur_token ++;

  * result = encoding;
  * indx = cur_token;

  return MAILIMF_NO_ERROR;
}
