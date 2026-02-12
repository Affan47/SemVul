uint32_t TiffMnEntry::doCount() const
    {
        if (!mn_) {
            return TiffEntryBase::doCount();
        }


        assert(tiffType() == ttUndefined || tiffType() == ttUnsignedByte || tiffType() == ttSignedByte);
        return mn_->size();
    }
