sortImageList()
{
  if ( m_SortOrder == SortByNameAscend )
    {
    std::sort( m_List.begin(), m_List.end(), IPLFileSortInfo_ascendbyname_compare() );
    }
  else if ( m_SortOrder == SortByNameDescend )
    {
    std::sort( m_List.begin(), m_List.end(), IPLFileSortInfo_descendbyname_compare() );
    }
  else if ( m_SortOrder == SortGlobalDescend )
    {
    std::sort( m_List.begin(), m_List.end(), IPLFileSortInfo_descend_compare() );
    }
  else if ( m_SortOrder == SortGlobalAscend )
    {
    std::sort( m_List.begin(), m_List.end(), IPLFileSortInfo_ascend_compare() );
    }
}
