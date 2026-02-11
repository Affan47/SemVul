RenameBuildTarget(const wxString& oldTargetName, const wxString& newTargetName)
{
    int idx = buildTargets.Index(oldTargetName);
    if (idx != wxNOT_FOUND)
        buildTargets[idx] = newTargetName;


    for (size_t i = 0; i < generatedFiles.size(); ++i)
        generatedFiles[i]->RenameBuildTarget(oldTargetName, newTargetName);
}
