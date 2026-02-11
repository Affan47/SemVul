OnAddFileToProject(wxCommandEvent& event)
{
    ProjectManager *prjManager = Manager::Get()->GetProjectManager();
    cbProject* prj = nullptr;
    wxString basePath;

    if (event.GetId() == idMenuAddFile)
    {
        prj = prjManager->GetActiveProject();
        if (prj)
            basePath = prj->GetBasePath();
    }
    else
    {
        wxTreeItemId sel = GetTreeSelection();
        if (!sel.IsOk())
            return;

        FileTreeData* ftd = (FileTreeData*)m_pTree->GetItemData(sel);
        if (ftd)
        {
            prj = ftd->GetProject();
            if (prj)
            {
                basePath = ftd->GetFolder();
                if (!wxDirExists(basePath))
                    basePath = prj->GetBasePath();
            }
        }
    }
    if (!prj)
        return;

    wxFileDialog dlg(Manager::Get()->GetAppWindow(),
                    _("Add files to project..."),
                    basePath,
                    wxEmptyString,
                    FileFilters::GetFilterString(),
                    wxFD_OPEN | wxFD_MULTIPLE | wxFD_FILE_MUST_EXIST | compatibility::wxHideReadonly);
    dlg.SetFilterIndex(FileFilters::GetIndexForFilterAll());

    PlaceWindow(&dlg);
    if (dlg.ShowModal() == wxID_OK)
    {
        wxArrayInt targets;

        if (prj->GetBuildTargetsCount() == 1)
             targets.Add(0);

        wxArrayString array;
        dlg.GetPaths(array);
        prjManager->AddMultipleFilesToProject(array, prj, targets);
        RebuildTree();
    }
}
