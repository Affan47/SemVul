OnRelease(cb_unused bool appShutDown)
{


    UnregisterScripting();
    SaveAutoCompleteConfig();

    if (m_Singleton == this)
        m_Singleton = nullptr;


    EditorHooks::UnregisterHook(m_EditorHookId, true);

    ClearAutoCompLanguageMap();
}
