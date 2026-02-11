SetTextControlValue(const wxString& name, const wxString& value)
{
    wxWizardPage* page = m_pWizard->GetCurrentPage();
    if (page)
    {
        wxTextCtrl* win = dynamic_cast<wxTextCtrl*>(page->FindWindowByName(name, page));
        if (win)
            win->SetValue(value);
    }
}
