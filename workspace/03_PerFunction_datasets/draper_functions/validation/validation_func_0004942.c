BasicAddToContextMenu(wxMenu* popup,ModuleType type)
{
    bool noeditor = (type != mtEditorManager);
    if (type == mtOpenFilesList)
    {
      popup->Append(idCloseMe, _("Close"));
      popup->Append(idCloseAll, _("Close all"));
      popup->Append(idCloseAllOthers, _("Close all others"));
      popup->AppendSeparator();
      popup->Append(idSaveMe, _("Save"));
      popup->Append(idSaveAll, _("Save all"));
      popup->AppendSeparator();

      popup->Enable(idSaveMe, GetModified());

      bool hasOthers = ThereAreOthers();
      popup->Enable(idCloseAll, hasOthers);
      popup->Enable(idCloseAllOthers, hasOthers);
    }
    if(!noeditor)
    {
        wxMenu* switchto = CreateContextSubMenu(idSwitchTo);
        if(switchto)
            popup->Append(idSwitchTo, _("Switch to"), switchto);
    }
}
