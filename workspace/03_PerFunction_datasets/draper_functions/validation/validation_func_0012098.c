GetDebuggee(wxString &pathToDebuggee, wxString &workingDirectory, ProjectBuildTarget* target)
{
    if (!target)
        return false;

    wxString out;
    switch (target->GetTargetType())
    {
        case ttExecutable:
        case ttConsoleOnly:
        case ttNative:
            {
                out = UnixFilename(target->GetOutputFilename());
                Manager::Get()->GetMacrosManager()->ReplaceEnvVars(out);
                wxFileName f(out);
                f.MakeAbsolute(target->GetParentProject()->GetBasePath());
                out = f.GetFullPath();
                Log(_("Adding file: ") + out);
                ConvertDirectory(out);
            }
            break;

        case ttStaticLib:
        case ttDynamicLib:

            if (target->GetHostApplication().IsEmpty())
            {
                cbMessageBox(_("You must select a host application to \"run\" a library..."));
                return false;
            }
            out = UnixFilename(target->GetHostApplication());
            Manager::Get()->GetMacrosManager()->ReplaceEnvVars(out);
            Log(_("Adding file: ") + out);
            ConvertDirectory(out);
            break;

        case ttCommandsOnly:
        default:
            Log(_("Unsupported target type (Project -> Properties -> Build Targets -> Type)"), Logger::error);
            return false;
    }
    if (out.empty())
    {
        Log(_("Couldn't find the path to the debuggee!"), Logger::error);
        return false;
    }

    workingDirectory = target->GetWorkingDir();
    Manager::Get()->GetMacrosManager()->ReplaceEnvVars(workingDirectory);
    wxFileName cd(workingDirectory);
    if (cd.IsRelative())
        cd.MakeAbsolute(target->GetParentProject()->GetBasePath());
    workingDirectory = cd.GetFullPath();

    pathToDebuggee = out;
    return true;
}
