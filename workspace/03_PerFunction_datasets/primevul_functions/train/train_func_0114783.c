void TiffEncoder::visitMnEntry(TiffMnEntry* object)
    {

        if (!object->mn_) {
            encodeTiffComponent(object);
        }
        else if (del_) {

            ExifKey key(object->tag(), groupName(object->group()));
            ExifData::iterator pos = exifData_.findKey(key);
            if (pos != exifData_.end()) exifData_.erase(pos);
        }
    }
