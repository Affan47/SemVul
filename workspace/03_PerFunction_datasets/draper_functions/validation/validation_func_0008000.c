OnParserEnd(wxCommandEvent& event)
{
    ParserCommon::ParserState state = static_cast<ParserCommon::ParserState>(event.GetInt());
    if (state == ParserCommon::ptCreateParser)
    {
        if (   m_CCEnableHeaders
            && !m_SystemHeadersThreads.empty()
            && !m_SystemHeadersThreads.front()->IsRunning()
            && m_NativeParser.Done() )
        {
            m_SystemHeadersThreads.front()->Run();
        }
    }

    EditorManager* edMan = Manager::Get()->GetEditorManager();
    cbEditor* editor = edMan->GetBuiltinActiveEditor();
    if (editor)
    {
        m_ToolbarNeedReparse = true;
        TRACE(_T("CodeCompletion::OnParserEnd: Starting m_TimerToolbar."));
        m_TimerToolbar.Start(TOOLBAR_REFRESH_DELAY, wxTIMER_ONE_SHOT);
    }

    if (m_NeedsBatchColour)
    {
        for (int edIdx = edMan->GetEditorsCount() - 1; edIdx >= 0; --edIdx)
        {
            editor = edMan->GetBuiltinEditor(edIdx);
            if (editor)
                UpdateEditorSyntax(editor);
        }
        m_NeedsBatchColour = false;
    }

    event.Skip();
}
