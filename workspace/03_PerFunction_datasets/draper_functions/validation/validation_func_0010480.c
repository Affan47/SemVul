get_type_values(int datatype, double *tmin, double *tmax)
{
  int status = 0;

  switch (datatype)
    {
    case DATATYPE_INT8:    *tmin = -SCHAR_MAX+1; *tmax = SCHAR_MAX;   break;
    case DATATYPE_UINT8:   *tmin = 0;            *tmax = UCHAR_MAX-1; break;
    case DATATYPE_INT16:   *tmin = -SHRT_MAX+1;  *tmax = SHRT_MAX;    break;
    case DATATYPE_UINT16:  *tmin = 0;            *tmax = USHRT_MAX-1; break;
    case DATATYPE_INT32:   *tmin = -INT_MAX+1;   *tmax = INT_MAX;     break;
    case DATATYPE_UINT32:  *tmin = 0;            *tmax = UINT_MAX-1;  break;
    default: status = 1; break;
    }

  return status;
}
