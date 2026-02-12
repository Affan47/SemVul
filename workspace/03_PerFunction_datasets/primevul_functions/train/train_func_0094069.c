QPDFWriter::interpretR3EncryptionParameters(
    std::set<int>& clear,
    char const* user_password, char const* owner_password,
    bool allow_accessibility, bool allow_extract,
    qpdf_r3_print_e print, qpdf_r3_modify_e modify)
{


    if (! allow_accessibility)
    {
	clear.insert(10);
    }
    if (! allow_extract)
    {
	clear.insert(5);
    }


    switch (print)
    {
      case qpdf_r3p_none:
	clear.insert(3);

      case qpdf_r3p_low:
	clear.insert(12);

      case qpdf_r3p_full:
	break;


    }

    switch (modify)
    {
      case qpdf_r3m_none:
	clear.insert(11);

      case qpdf_r3m_assembly:
	clear.insert(9);

      case qpdf_r3m_form:
	clear.insert(6);

      case qpdf_r3m_annotate:
	clear.insert(4);

      case qpdf_r3m_all:
	break;


    }
}
