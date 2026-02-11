cson_value_fetch_double( cson_value const * val, cson_double_t * v )
{
    if( ! val || !val->api ) return cson_rc.ArgError;
    else
    {
        cson_double_t d = 0.0;
        int rc = 0;
        switch(val->api->typeID)
        {
          case CSON_TYPE_UNDEF:
          case CSON_TYPE_NULL:
              d = 0;
              break;
          case CSON_TYPE_BOOL: {
              char b = 0;
              cson_value_fetch_bool( val, &b );
              d = b ? 1.0 : 0.0;
              break;
          }
          case CSON_TYPE_INTEGER: {
              cson_int_t i = 0;
              cson_value_fetch_integer( val, &i );
              d = i;
              break;
          }
          case CSON_TYPE_DOUBLE: {
              cson_double_t const* dv = CSON_DBL(val);
              d = dv ? *dv : 0.0;
              break;
          }
          default:
              rc = cson_rc.TypeError;
              break;
        }
        if(v) *v = d;
        return rc;
    }
}
