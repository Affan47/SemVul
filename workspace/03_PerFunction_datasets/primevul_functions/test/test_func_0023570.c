bool Predicant_to_list_comparator::make_unique_cmp_items(THD *thd,
                                                         CHARSET_INFO *cs)
{
  for (uint i= 0; i < m_comparator_count; i++)
  {
    if (m_comparators[i].m_handler &&
        m_comparators[i].m_handler_index == i &&
        !(m_comparators[i].m_cmp_item=
          m_comparators[i].m_handler->make_cmp_item(thd, cs)))
       return true;
  }
  return false;
}
