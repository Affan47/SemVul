ListChange()
{
    wxTextCtrl* pText = XRCCTRL(*this, "txtFileMasks", wxTextCtrl);
    int sel = XRCCTRL(*this, "lstCategories", wxListBox)->GetSelection();

    if (sel != m_LastListSelection)
    {

        if (pText->GetValue() != m_FileGroupsAndMasksCopy.GetFileMasks(m_LastListSelection))
            m_FileGroupsAndMasksCopy.SetFileMasks(m_LastListSelection, pText->GetValue());
    }

    pText->SetValue(m_FileGroupsAndMasksCopy.GetFileMasks(sel));
    m_LastListSelection = sel;
}
