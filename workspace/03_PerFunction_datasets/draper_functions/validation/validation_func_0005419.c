ListBox2ArrayString(wxArrayString& array, const wxListBox* control)
{
    array.Clear();
    int count = control->GetCount();
    for (int i = 0; i < count; ++i)
    {
        wxString tmp = control->GetString(i);
        if (!tmp.IsEmpty())
            array.Add(tmp);
    }
}
