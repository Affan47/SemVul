FromFile(const wxString& file)
{
    wxFile f(file);
    wxString contents = cbReadFileContents(f);
    if (contents.IsEmpty())
        return 0;
    return FromString(contents);
}
