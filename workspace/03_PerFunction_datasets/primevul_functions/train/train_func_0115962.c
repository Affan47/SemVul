int Insert::insertIccProfile(const std::string& path, Exiv2::DataBuf& iccProfileBlob) const
    {
        int rc = 0;

        if (!Exiv2::fileExists(path, true)) {
            std::cerr << path << ": " << _("Failed to open the file\n");
            rc = -1;
        }


        if (rc == 0) {
            Exiv2::Image::UniquePtr image = Exiv2::ImageFactory::open(path);
            image->readMetadata();

            image->clearIccProfile();
            if (iccProfileBlob.size_) {
                image->setIccProfile(iccProfileBlob);
            }
            image->writeMetadata();
        }

        return rc;
    }
