bSetValue( float fValue )
{
  wxString  osValue;
  float     f1;
  int       i1;

  if( ! bIsCreated( ) )      return( FALSE );
  if( fValue < m_fMinValue )
    if( !( (m_eVarType==eVAR_SCI || m_eVarType==eVAR_ENG) && fValue==0.0 ) )
                             return( FALSE );
  if( fValue > m_fMaxValue ) return( FALSE );

  m_oTxtValue.Clear( );
  switch( m_eVarType )
  {
    case eVAR_HEX :
      if( fValue < 0.0 )                 return( FALSE );
      i1 = (int) ( fValue + 0.5 );
      osValue.Printf( wxT("%X"), i1 );
      break;

    case eVAR_INT :
      if( fValue >= 0.0 ) i1 = (int) ( fValue + 0.5 );
      else                i1 = (int) ( fValue - 0.5 );
      osValue << i1;
      break;

    case eVAR_FLT :
      osValue.Printf( wxT("%#.2f"), fValue );
      break;

    case eVAR_SCI :
      osValue.Printf( wxT("%#.2E"), fValue );
      break;

    case eVAR_ENG :
      if( ! ConvertType::bParseFlt( (double) fValue, &f1, &i1 ) )
        return( FALSE );
      while( i1 % 3 ) { f1 *= 10.0; i1--; }
      osValue.Printf( wxT("%#.2fE%02i"), f1, i1 );
      break;

    default:                 return( FALSE );
  }

  osValue.Append( wxT(" ") );
  m_oTxtValue.SetValue( osValue );

  return( TRUE );
}
