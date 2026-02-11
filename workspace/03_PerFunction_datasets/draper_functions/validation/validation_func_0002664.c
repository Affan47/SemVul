StringToValue( wxVariant& variant, const wxString& text, int argFlags ) const
{
    wxString s;
    double value;

    if ( text.length() == 0 )
    {
        variant.MakeNull();
        return true;
    }

    bool res = text.ToDouble(&value);
    if ( res )
    {
        if ( m_value.IsNull() || m_value != value )
        {
            variant = value;
            return true;
        }
    }
    else if ( argFlags & wxPG_REPORT_ERROR )
    {
    }
    return false;
}
