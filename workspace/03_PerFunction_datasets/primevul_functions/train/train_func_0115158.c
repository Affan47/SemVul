void ExifThumb::setJpegThumbnail(const std::string& path)
    {
        DataBuf thumb = readFile(path);
        setJpegThumbnail(thumb.pData_, (long)thumb.size_);
    }
