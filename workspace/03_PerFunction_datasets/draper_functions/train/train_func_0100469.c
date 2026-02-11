NotifyPlugins(wxEventType type, const wxString& targetName, const wxString& oldTargetName)
{
    CodeBlocksEvent event(type);
    event.SetProject(this);
    event.SetBuildTargetName(targetName);
    event.SetOldBuildTargetName(oldTargetName);
    Manager::Get()->ProcessEvent(event);
}
