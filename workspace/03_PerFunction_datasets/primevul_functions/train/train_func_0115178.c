void ExifThumb::setJpegThumbnail(const std::wstring& wpath)
    {
        DataBuf thumb = readFile(wpath);
        setJpegThumbnail(thumb.pData_, thumb.size_);
    }
