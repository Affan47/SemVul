StringToValue( wxVariant& variant, const wxString& text, int ) const
{
    if ( m_value.IsNull() || m_value != text )
    {
        variant = text;
        return true;
    }
    return false;
}
