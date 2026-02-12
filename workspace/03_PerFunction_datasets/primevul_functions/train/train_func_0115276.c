long PreviewImage::writeFile(const std::string& path) const
    {
        std::string name = path + extension();

        DataBuf buf(pData_, size_);
        return Exiv2::writeFile(buf, name);
    }
