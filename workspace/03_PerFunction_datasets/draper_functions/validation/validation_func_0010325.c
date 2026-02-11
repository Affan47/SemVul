OnDropFiles(wxCoord x, wxCoord y, const wxArrayString& arrayData)

{


    if ( arrayData.GetCount())
        m_Window->OpenDroppedFiles(arrayData);
    return true;

}
