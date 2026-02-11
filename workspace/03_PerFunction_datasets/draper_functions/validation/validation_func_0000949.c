prepare_for_resend()
{
  DBUG_ASSERT(alloc_root_inited(&m_rset_root));

  opt_add_row_to_rset();

  m_current_row= (Ed_column *) alloc_root(&m_rset_root,
                                          sizeof(Ed_column) * m_column_count);
  m_current_column= m_current_row;
}
