void handler::rebind_psi()
{


  m_psi= PSI_CALL_rebind_table(ha_table_share_psi(), this, m_psi);
}
