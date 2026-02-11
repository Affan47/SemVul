OnPageChanged(wxAuiNotebookEvent& event)
{
    EditorBase* eb = static_cast<EditorBase*>(m_pNotebook->GetPage(event.GetSelection()));
    EditorBase* eb_old = nullptr;
    if (event.GetOldSelection()!=-1)
        eb_old = static_cast<EditorBase*>(m_pNotebook->GetPage(event.GetOldSelection()));

    CodeBlocksEvent evt(cbEVT_EDITOR_SWITCHED, -1, nullptr, eb, nullptr, eb_old);
    Manager::Get()->GetPluginManager()->NotifyPlugins(evt);

    CodeBlocksEvent evt2(cbEVT_EDITOR_ACTIVATED, -1, nullptr, eb);
    Manager::Get()->GetPluginManager()->NotifyPlugins(evt2);

    if (Manager::Get()->GetConfigManager(_T("app"))->ReadBool(_T("/environment/tabs_stacked_based_switching")))
    {
        wxWindow*        wnd;
        cbNotebookStack* body;
        cbNotebookStack* tmp;
        wnd = m_pNotebook->GetPage(event.GetSelection());
        for (body = m_pNotebookStackHead; body->next != nullptr; body = body->next)
        {
            if (wnd == body->next->window)
            {
                if (m_pNotebookStackTail == body->next)
                    m_pNotebookStackTail = body;
                tmp = body->next;
                body->next = tmp->next;
                tmp->next = m_pNotebookStackHead->next;
                m_pNotebookStackHead->next = tmp;
                break;
            }
        }
        if (   (m_pNotebookStackHead->next == nullptr)
            || (wnd != m_pNotebookStackHead->next->window) )
        {
            body = new cbNotebookStack(wnd);
            body->next = m_pNotebookStackHead->next;
            m_pNotebookStackHead->next = body;
            ++m_nNotebookStackSize;
        }
    }


    m_pData->m_SetFocusFlag = true;

    event.Skip();
}
