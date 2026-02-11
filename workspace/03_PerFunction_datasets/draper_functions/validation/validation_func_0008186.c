Get(String& buffer) const
{
  buffer.trunc();

  switch(type) {

  case WORD_RECORD_DATA:
    buffer << info.data;
    break;

  case WORD_RECORD_STATS:
    buffer << info.stats.noccurrence << "\t";
    buffer << info.stats.ndoc;
    break;

  case WORD_RECORD_NONE:
    break;

  default:
    fprintf(stderr, "WordRecord::Get: unknown type %d\n", type);
    return NOTOK;
    break;
  }

  return OK;
}
