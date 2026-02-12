void TiffEncoder::visitIfdMakernote(TiffIfdMakernote* object)
    {
        assert(object != 0);

        ExifData::iterator pos = exifData_.findKey(ExifKey("Exif.MakerNote.ByteOrder"));
        if (pos != exifData_.end()) {

            ByteOrder bo = stringToByteOrder(pos->toString());
            if (bo != invalidByteOrder && bo != object->byteOrder()) {
                object->setByteOrder(bo);
                setDirty();
            }
            if (del_)
                exifData_.erase(pos);
        }
        if (del_) {

            static const char* synthesizedTags[] = {
                "Exif.MakerNote.Offset",
            };
            for (unsigned int i = 0; i < EXV_COUNTOF(synthesizedTags); ++i) {
                pos = exifData_.findKey(ExifKey(synthesizedTags[i]));
                if (pos != exifData_.end())
                    exifData_.erase(pos);
            }
        }

        byteOrder_ = object->byteOrder();

    }
