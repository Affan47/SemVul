sizeof_datatype(int datatype) {
  switch (datatype) {
  case TSTRING:
    return sizeof(char *);
  case TLOGICAL:
    return sizeof(logical);
  case TSBYTE:
    return sizeof(sbyte);
  case TBYTE:
    return sizeof(byte);
  case TUSHORT:
    return sizeof(unsigned short);
  case TSHORT:
    return sizeof(short);
  case TUINT:
    return sizeof(unsigned int);
  case TINT:
    return sizeof(int);
  case TULONG:
    return sizeof(unsigned long);
  case TLONG:
    return sizeof(long);
  case TLONGLONG:
    return sizeof(LONGLONG);
  case TFLOAT:
    return sizeof(float);
  case TDOUBLE:
    return sizeof(double);
  case TCOMPLEX:
    return 2*sizeof(float);
  case TDBLCOMPLEX:
    return 2*sizeof(double);
  default:
    croak("sizeof_datatype() - invalid datatype (%d) given",datatype);
  }
}
