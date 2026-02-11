bLoad( SimnGnuCap & roSimn )
{
  bool  bRtn=TRUE;


  PnlAnaBase::LoadSrcNames( roSimn.m_oaCpnts, wxT("VI") );


  if( ! roSimn.m_oCmdTR.bIsValid( ) )                        return( FALSE );


  if( ! PnlAnaBase::bSetSrcCpnt( roSimn.m_oCpntSwpSrc ) )    bRtn = FALSE;


  if( ! m_oPnlStart.bSetValue( roSimn.m_oCmdTR.m_osStart ) ) bRtn = FALSE;
  if( ! m_oPnlStop .bSetValue( roSimn.m_oCmdTR.m_osStop  ) ) bRtn = FALSE;
  if( ! m_oPnlStep .bSetValue( roSimn.m_oCmdTR.m_osStep  ) ) bRtn = FALSE;
  if( m_oPnlStart.dfGetValue( ) == 0.0 )
        m_oPnlStart.bSetUnits( m_oPnlStop.rosGetUnits( ) );


  if( roSimn.m_oCmdTR.m_eInitC != eINITC_NONE )
    m_oRbxInitC.SetSelection( roSimn.m_oCmdTR.m_eInitC );


  if( ! m_oDlgCfgGEN.bSetValues( roSimn.m_oCmdGEN ) )        bRtn = FALSE;

  if( roSimn.eGetAnaType( ) == eCMD_TR )
  {

    m_oCbxVoltage.SetValue( roSimn.m_oCmdPR.m_bParmtrs[ ePAR_VLT ] );
    m_oCbxCurrent.SetValue( roSimn.m_oCmdPR.m_bParmtrs[ ePAR_CUR ] );
    m_oCbxPower  .SetValue( roSimn.m_oCmdPR.m_bParmtrs[ ePAR_PWR ] );
    m_oCbxResist .SetValue( roSimn.m_oCmdPR.m_bParmtrs[ ePAR_RES ] );
  }


  if( ! m_oPnlTemp.bSetValue( roSimn.m_oCmdTR.m_osTempC ) )  bRtn = FALSE;

  return( bRtn );
}
