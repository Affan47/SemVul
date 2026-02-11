OnAttach()
{

    WX_CLEAR_ARRAY(m_MimeTypes);

    ConfigManager* conf = Manager::Get()->GetConfigManager(_T("mime_types"));
    wxArrayString list = conf->EnumerateKeys(_T("/"));
    for (unsigned int i = 0; i < list.GetCount(); ++i)
    {
        wxArrayString array = GetArrayFromString(conf->Read(list[i]), _T(";"), false);
        if (array.GetCount() < 3)
            continue;

        cbMimeType* mt = new cbMimeType;


        bool isOld = array.GetCount() == 3 || array.GetCount() == 4;
        if (isOld)
        {
            mt->useEditor = array[0] == _T("true");
            mt->useAssoc = false;
            mt->programIsModal = array[1] == _T("true");
            mt->wildcard = array[2];
            mt->program = array.GetCount() == 4 ? array[3] : _T("");
        }
        else
        {
            mt->useEditor = array[0] == _T("true");
            mt->useAssoc = array[1] == _T("true");
            mt->programIsModal = array[2] == _T("true");
            mt->wildcard = array[3];
            mt->program = array.GetCount() == 5 ? array[4] : _T("");
        }
        mt->program.Trim();

        if (!mt->useEditor && !mt->useAssoc && mt->program.IsEmpty())
            delete mt;
        else
            m_MimeTypes.Add(mt);
    }

    m_Html = new EmbeddedHtmlPanel(Manager::Get()->GetAppWindow());

    CodeBlocksDockEvent evt(cbEVT_ADD_DOCK_WINDOW);
    evt.pWindow = m_Html;
    evt.name = _T("DefMimeHandler_HTMLViewer");
    evt.title = _("HTML viewer");
    evt.dockSide = CodeBlocksDockEvent::dsFloating;
    evt.desiredSize.Set(350, 250);
    evt.floatingSize.Set(350, 250);
    evt.minimumSize.Set(150, 150);
    evt.shown = false;
    Manager::Get()->ProcessEvent(evt);
}
