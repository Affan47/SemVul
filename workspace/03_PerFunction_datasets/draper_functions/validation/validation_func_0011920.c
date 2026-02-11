m_erase_redundant_separator(string_type::size_type sep_pos)
  {
    if (sep_pos
      && sep_pos < m_pathname.size()
      && (m_pathname[sep_pos+1] == separator
#      ifdef BOOST_WINDOWS_API
       || m_pathname[sep_pos+1] == preferred_separator
#      endif
)) { m_pathname.erase(sep_pos, 1); }
  }
