OnIdle(cb_unused wxIdleEvent& event)
{
    if (m_SetZoomOnIdle)
    {
        m_SetZoomOnIdle = false;
        int zoom = Manager::Get()->GetEditorManager()->GetZoom();
        for (size_t i = 0; i < GetPageCount(); ++i)
        {
            wxWindow* win = GetPage(i);
            if (win && static_cast<EditorBase*>(win)->IsBuiltinEditor())
                static_cast<cbEditor*>(win)->SetZoom(zoom);
        }
    }

    if (m_MinimizeFreeSpaceOnIdle)
    {
        m_MinimizeFreeSpaceOnIdle = false;
        UpdateTabControlsArray();
        for (size_t i = 0; i < m_TabCtrls.GetCount(); ++i)
            MinimizeFreeSpace(m_TabCtrls[i]);
    }

}
