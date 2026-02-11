_GD_CDivideData(DIRFILE *D, void *A, gd_spf_t spfA,
    GD_DCOMPLEXP(B), gd_spf_t spfB, gd_type_t type, size_t n)
{
  size_t i;

  dtrace("%p, %p, %u, %p, %u, 0x%x, %zu", D, A, spfA, B, spfB, type, n);

  switch (type) {
    case GD_NULL:                         break;
    case GD_UINT8:      DIVIDE( uint8_t); break;
    case GD_INT8:       DIVIDE(  int8_t); break;
    case GD_UINT16:     DIVIDE(uint16_t); break;
    case GD_INT16:      DIVIDE( int16_t); break;
    case GD_UINT32:     DIVIDE(uint32_t); break;
    case GD_INT32:      DIVIDE( int32_t); break;
    case GD_UINT64:     DIVIDE(uint64_t); break;
    case GD_INT64:      DIVIDE( int64_t); break;
    case GD_FLOAT32:    DIVIDE(   float); break;
    case GD_FLOAT64:    DIVIDE(  double); break;
    case GD_COMPLEX64:  DIVIDEC(  float); break;
    case GD_COMPLEX128: DIVIDEC( double); break;
    default:            _GD_SetError(D, GD_E_BAD_TYPE, type, NULL, 0, NULL);
                        break;
  }

  dreturnvoid();
}
