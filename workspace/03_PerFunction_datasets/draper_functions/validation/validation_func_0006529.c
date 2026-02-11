ParseCurrent(bool forced)
{
    if (m_Ignore)
        return;
    cbEditor* ed = Manager::Get()->GetEditorManager()->GetBuiltinEditor(Manager::Get()->GetEditorManager()->GetActiveEditor());
    if (ed)
    {
        wxString filename = ed->GetFilename();
        if (forced || filename != m_LastFile)
        {
            m_LastFile = filename;
            m_Items.Clear();
            ParseEditor(ed);
        }
    }
    FillList();
}
