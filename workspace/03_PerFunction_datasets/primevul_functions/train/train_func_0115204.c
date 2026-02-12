void ExifThumb::setJpegThumbnail(
        const std::string& path,
              URational    xres,
              URational    yres,
              uint16_t     unit
    )
    {
        DataBuf thumb = readFile(path);
        setJpegThumbnail(thumb.pData_, thumb.size_, xres, yres, unit);
    }
