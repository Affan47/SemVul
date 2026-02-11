Create( void )
{
#ifndef LAYOUT_MNGR
  int  ix, iy;


  SetSwpPnlLbl( wxT(" Operating Point Sweep ") );

  m_oSbxSwpPars.GetSize( &ix, &iy );
  m_oSbxSwpPars.SetSize(  ix, 167 );
  m_oSbxSwpPars.SetLabel( wxT(" Operating Point Sweep ") );
#endif
  m_oPnlStart  .bSetName( wxT("Start Temperature") );
  m_oPnlStop   .bSetName( wxT("Stop Temperature") );


  m_oPnlStart.bSetUnitsType( eUNITS_TEMP );
  m_oPnlStop .bSetUnitsType( eUNITS_TEMP );
  m_oPnlStep .bSetUnitsType( eUNITS_TEMP );


  PnlAnaBase::CreateScale( );
  m_oRbxScale.Enable( eSCALE_OCT, FALSE );

  PnlAnaBase::CreateSrc( );

  PnlAnaBase::DoLayout( );

#ifdef LAYOUT_MNGR
  SetSwpPnlLbl( wxT(" Operating Point Sweep ") );
#endif
}
