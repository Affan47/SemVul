checkForFileModification()
{
    helpers::FileInfo fi;

    if (helpers::getFileInfo (&fi, propertyFilename) != 0)
        return false;

    bool modified = fi.mtime > lastFileInfo.mtime
        || fi.size != lastFileInfo.size;

#if defined(DCMTK_LOG4CPLUS_HAVE_LSTAT)
    if (!modified && fi.is_link)
    {
        struct stat fileStatus;
        if (lstat(DCMTK_LOG4CPLUS_TSTRING_TO_STRING(propertyFilename).c_str(),
                &fileStatus) == -1)
            return false;

        helpers::Time linkModTime(fileStatus.st_mtime);
        modified = (linkModTime > fi.mtime);
    }
#endif

    return modified;
}
