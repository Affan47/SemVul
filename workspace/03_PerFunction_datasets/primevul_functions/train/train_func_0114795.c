long PreviewImage::writeFile(const std::wstring& wpath) const
    {
        std::wstring name = wpath + wextension();

        DataBuf buf(pData_, size_);
        return Exiv2::writeFile(buf, name);
    }
