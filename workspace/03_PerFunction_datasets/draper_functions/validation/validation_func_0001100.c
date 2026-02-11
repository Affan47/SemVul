SaveLayout()
{
    if (m_Filename.IsEmpty())
        return false;

    wxFileName fname(m_Filename);
    fname.SetExt(_T("layout"));
    ProjectLayoutLoader loader(this);
    return loader.Save(fname.GetFullPath());
}
