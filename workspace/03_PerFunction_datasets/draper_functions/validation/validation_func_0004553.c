GetFileByFilename(const wxString& filename, bool isRelative, bool isUnixFilename)
{

    wxString tmp = filename;
    if (!isRelative)
    {

        wxFileName fname(realpath(filename));
        fname.MakeRelativeTo( GetBasePath() );
        tmp = fname.GetFullPath();
    }
    else
    {


        if (tmp.StartsWith(_T(".\\")) ||
            tmp.StartsWith(_T("./")))
        {
            tmp.Remove(0, 2);
        }
    }

    if (isUnixFilename)
        return m_ProjectFilesMap[tmp];

    return m_ProjectFilesMap[UnixFilename(tmp)];
}
