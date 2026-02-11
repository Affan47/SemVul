GetDocName(wxInt32 item, wxString& strBuffer) const {
    RESULT* result = wxGetApp().GetDocument()->result(item);

    if (result) {
        strBuffer = wxString(result->name, wxConvUTF8);
    }
}
