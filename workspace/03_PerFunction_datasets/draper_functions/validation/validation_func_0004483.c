OnClose( wxCommandEvent & roEvtCmd )
{
  int  ix, iy, iw, ih;


  GetPosition( &ix, &iy );
  GetClientSize( &iw, &ih );
  m_poCfg->SetPath( wxT("/Help") );
  m_poCfg->Write( wxT("PosnX"), (long) ix );
  m_poCfg->Write( wxT("PosnY"), (long) iy );
  m_poCfg->Write( wxT("SizeW"), (long) iw );
  m_poCfg->Write( wxT("SizeH"), (long) ih );
  m_poCfg->Flush( );

  Show( FALSE );


  while( m_oHtmlWin.HistoryCanBack( ) )
    m_oHtmlWin.HistoryBack( );
  m_oHtmlWin.HistoryClear( );
  m_oHtmlWin.Scroll( 0, 0 );
}
