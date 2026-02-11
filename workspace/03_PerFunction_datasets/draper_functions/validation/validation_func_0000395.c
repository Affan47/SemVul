DoRememberExpandedNodes(wxTreeCtrl* tree, const wxTreeItemId& parent, wxArrayString& nodePaths, wxString& path)
{

    if (!tree || !parent.IsOk())
        return false;

    wxString originalPath = path;
    bool found = false;

    wxTreeItemIdValue cookie = nullptr;

    wxTreeItemId child = tree->GetFirstChild(parent, cookie);
    while (child.IsOk())
    {
        if (tree->ItemHasChildren(child) && tree->IsExpanded(child))
        {
            found = true;
            path << _T("/") << tree->GetItemText(child);
            DoRememberExpandedNodes(tree, child, nodePaths, path);
            nodePaths.Add(path);
            path = originalPath;
        }
        child = tree->GetNextChild(parent, cookie);
    }
    return found;
}
