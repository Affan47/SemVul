insert_wstring(const CORBA::WChar* value)
{
  if( !value )
    throw DynamicAny::DynAny::InvalidValue();

  if ( tckind() != CORBA::tk_wstring )
    throw DynamicAny::DynAny::TypeMismatch();

  CORBA::ULong maxlen = actualTc()->NP_length();
  cdrAnyMemoryStream& buf = doWrite(CORBA::tk_wstring);
  try {
    buf.marshalWString(value,maxlen);
  }
  catch (CORBA::MARSHAL& ex) {
    if (ex.minor() == MARSHAL_WStringIsTooLong)
      throw DynamicAny::DynAny::InvalidValue();
    else
      throw;
  }
}
