uint32_t TiffImageEntry::doSizeData() const
    {
        uint32_t len = 0;

        if (group() > mnId) {
            len = sizeImage();
        }
        return len;
    }
