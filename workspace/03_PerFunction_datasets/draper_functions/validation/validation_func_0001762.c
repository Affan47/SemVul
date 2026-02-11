DoCheckScripts(CompileTargetBase* base)
{
    const wxArrayString& scripts = base->GetBuildScripts();
    for (size_t i = 0; i < scripts.GetCount(); ++i)
    {
        ProjectBuildTarget* bt = dynamic_cast<ProjectBuildTarget*>(base);
        if (!IsScriptValid(bt, scripts[i]))
        {
            wxString msg;
            msg << _("Invalid build script: ") + scripts[i] << _T('\n');
            msg << _("First seen in: ") + base->GetTitle() << _T('\n');
            cbMessageBox(msg, _("Error"), wxICON_ERROR, this);
            return false;
        }
    }
    return true;
}
