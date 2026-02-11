ApplyStyles(cbStyledTextCtrl* control)
{
    if (!control)
        return;
    InternalSetEditorStyleBeforeFileOpen(control);
    InternalSetEditorStyleAfterFileOpen(control);

    ConfigManager* mgr = Manager::Get()->GetConfigManager(_T("editor"));

    int pixelWidth = control->TextWidth(wxSCI_STYLE_LINENUMBER, _T("9"));
    if (mgr->ReadBool(_T("/show_line_numbers"), true))
        control->SetMarginWidth(0, 5 * pixelWidth);
}
