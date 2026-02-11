DoClassMethodDeclImpl()
{
    if (!IsAttached() || !m_InitDone)
        return -1;

    EditorManager* edMan = Manager::Get()->GetEditorManager();
    cbEditor* ed = edMan->GetBuiltinActiveEditor();
    if (!ed)
        return -3;

    FileType ft = FileTypeOf(ed->GetShortName());
    if ( ft != ftHeader && ft != ftSource)
        return -4;

    if (!m_NativeParser.GetParser().Done())
    {
        wxString msg = _("The Parser is still parsing files.");
        msg += m_NativeParser.GetParser().NotDoneReason();
        CCLogger::Get()->DebugLog(msg);
        return -5;
    }

    int success = -6;


    CC_LOCKER_TRACK_TT_MTX_LOCK(s_TokenTreeMutex)


    wxString filename = ed->GetFilename();
    InsertClassMethodDlg dlg(Manager::Get()->GetAppWindow(), &m_NativeParser.GetParser(), filename);
    PlaceWindow(&dlg);
    if (dlg.ShowModal() == wxID_OK)
    {
        cbStyledTextCtrl* control = ed->GetControl();
        int pos = control->GetCurrentPos();
        int line = control->LineFromPosition(pos);
        control->GotoPos(control->PositionFromLine(line));

        wxArrayString result = dlg.GetCode();
        for (unsigned int i = 0; i < result.GetCount(); ++i)
        {
            pos = control->GetCurrentPos();
            line = control->LineFromPosition(pos);
            wxString str = ed->GetLineIndentString(line - 1) + result[i];
            MatchCodeStyle(str, control->GetEOLMode(), ed->GetLineIndentString(line - 1), control->GetUseTabs(), control->GetTabWidth());
            control->SetTargetStart(pos);
            control->SetTargetEnd(pos);
            control->ReplaceTarget(str);
            control->GotoPos(pos + str.Length());
        }
        success = 0;
    }

    CC_LOCKER_TRACK_TT_MTX_UNLOCK(s_TokenTreeMutex)

    return success;
}
