SetupLinkLibraries(Compiler* compiler, ProjectBuildTarget* target)
{
    wxArrayString libs;

    if (target)
        libs = GetOrderedOptions(target, ortLinkerOptions, target->GetParentProject()->GetLinkLibs(), target->GetLinkLibs());


    const wxArrayString& carr = compiler->GetLinkLibs();
    for (unsigned int x = 0; x < carr.GetCount(); ++x)
        libs.Add(carr[x]);

    for (unsigned int x = 0; x < libs.GetCount(); ++x)
        libs[x] = FixupLinkLibraries(compiler, libs[x]);

    if (compiler->GetSwitches().linkerNeedsPathResolved)
    {
        wxArrayString path(GetOrderedLibrariesDirs(compiler, target));
        for (unsigned int x = 0; x < libs.GetCount(); ++x)
        {
            libs[x] = PathSearch(path, libs[x]);
        }
    }
    wxString result;
    bool subseq(false);
    for (unsigned int x = 0; x < libs.GetCount(); ++x)
    {
        if (subseq)
            result << compiler->GetSwitches().objectSeparator;
        subseq = true;
        wxString tmp(libs[x]);
        QuoteStringIfNeeded(tmp);
        result << tmp;
    }
    return result;
}
