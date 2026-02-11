CreateEscapeSequences( wxString& dst_str, wxString& src_str )
{
    if ( src_str.length() == 0 )
    {
        dst_str = src_str;
        return src_str;
    }

    wxString::const_iterator i = src_str.begin();

    dst_str.clear();

    for ( ; i != src_str.end(); i++ )
    {
        wxChar a = wxPGGetIterChar(src_str, i);

        if ( a >= wxT(' ') )
        {

            dst_str << a;
        }
        else
        {

            if ( a == wxT('\r')  )
            {


            }
            else if ( a == wxT('\n') )

                dst_str << wxT("\\n");
            else if ( a == wxT('\t') )

                dst_str << wxT('\t');
            else
            {

                dst_str << a;
            }
        }

    }
    return dst_str;
}
