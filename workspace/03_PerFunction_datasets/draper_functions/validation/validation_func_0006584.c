bClear( void )
{
  bool  bRtn=TRUE;


  if( ! PnlAnaBase::bClear( ) )    bRtn = FALSE;


  m_oPnlStart.bSetValue( (float)   1.0 );
  m_oPnlStop .bSetValue( (float) 100.0 );
  m_oPnlStep .bSetValue( (float)   1.0 );
  m_oPnlStart.bSetUnits( wxT("kHz") );
  m_oPnlStop .bSetUnits( wxT("kHz") );
  m_oPnlStep .bSetUnits( wxT("kHz") );


  if( ! bSetInitC( eINITC_WARM ) ) bRtn = FALSE;


  m_oDlgCfgGEN.bClear( );


  m_oCbxMag   .SetValue( TRUE  );
  m_oCbxPhase .SetValue( FALSE );
  m_oCbxMagDb .SetValue( TRUE  );
  m_oCbxMagRel.SetValue( FALSE );

  return( bRtn );
}
