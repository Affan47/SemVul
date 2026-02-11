OnExpand(wxPropertyGridEvent &event)
{
    WatchesProperty *prop = static_cast<WatchesProperty*>(event.GetProperty());
    prop->GetWatch()->Expand(true);

    cbDebuggerPlugin *plugin = Manager::Get()->GetDebuggerManager()->GetActiveDebugger();
    if (plugin)
        plugin->ExpandWatch(prop->GetWatch());
    Fit();
}
