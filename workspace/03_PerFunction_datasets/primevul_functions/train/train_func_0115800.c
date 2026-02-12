std::string TiffImage::primaryGroup() const
    {
        if (!primaryGroup_.empty()) return primaryGroup_;

        static const char* keys[] = {
            "Exif.Image.NewSubfileType",
            "Exif.SubImage1.NewSubfileType",
            "Exif.SubImage2.NewSubfileType",
            "Exif.SubImage3.NewSubfileType",
            "Exif.SubImage4.NewSubfileType",
            "Exif.SubImage5.NewSubfileType",
            "Exif.SubImage6.NewSubfileType",
            "Exif.SubImage7.NewSubfileType",
            "Exif.SubImage8.NewSubfileType",
            "Exif.SubImage9.NewSubfileType"
        };

        primaryGroup_ = std::string("Image");
        for (unsigned int i = 0; i < EXV_COUNTOF(keys); ++i) {
            ExifData::const_iterator md = exifData_.findKey(ExifKey(keys[i]));

            if (md != exifData_.end() && md->count() > 0 && md->toLong() == 0) {

                primaryGroup_ = md->groupName();
                std::string key = "Exif." + primaryGroup_ + ".JPEGInterchangeFormat";
                if (exifData_.findKey(ExifKey(key)) == exifData_.end()) break;
            }
        }
        return primaryGroup_;
    }
