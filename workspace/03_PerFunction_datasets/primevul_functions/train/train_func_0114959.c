uint32_t TiffDirectory::doSize() const
    {
        uint32_t compCount = count();

        uint32_t len = 2 + 12 * compCount + (hasNext_ ? 4 : 0);

        for (Components::const_iterator i = components_.begin(); i != components_.end(); ++i) {
            uint32_t sv = (*i)->size();
            if (sv > 4) {
                sv += sv & 1;
                len += sv;
            }
            uint32_t sd = (*i)->sizeData();
            sd += sd & 1;
            len += sd;
        }

        uint32_t sizeNext = 0;
        if (pNext_) {
            sizeNext = pNext_->size();
            len += sizeNext;
        }

        if (compCount == 0 && sizeNext == 0) len = 0;
        return len;
    }
