void TiffEncoder::encodeIptc()
    {


        bool del = false;
        ExifKey iptcNaaKey("Exif.Image.IPTCNAA");
        ExifData::iterator pos = exifData_.findKey(iptcNaaKey);
        if (pos != exifData_.end()) {
            iptcNaaKey.setIdx(pos->idx());
            exifData_.erase(pos);
            del = true;
        }
        DataBuf rawIptc = IptcParser::encode(iptcData_);
        ExifKey irbKey("Exif.Image.ImageResources");
        pos = exifData_.findKey(irbKey);
        if (pos != exifData_.end()) {
            irbKey.setIdx(pos->idx());
        }
        if (rawIptc.size_ != 0 && (del || pos == exifData_.end())) {
            Value::UniquePtr value = Value::create(unsignedLong);
            DataBuf buf;
            if (rawIptc.size_ % 4 != 0) {

                buf.alloc((rawIptc.size_ / 4) * 4 + 4);
                memset(buf.pData_, 0x0, buf.size_);
                memcpy(buf.pData_, rawIptc.pData_, rawIptc.size_);
            }
            else {
                buf = rawIptc;
            }
            value->read(buf.pData_, buf.size_, byteOrder_);
            Exifdatum iptcDatum(iptcNaaKey, value.get());
            exifData_.add(iptcDatum);
            pos = exifData_.findKey(irbKey);
        }


        if (pos != exifData_.end()) {
            DataBuf irbBuf(pos->value().size());
            pos->value().copy(irbBuf.pData_, invalidByteOrder);
            irbBuf = Photoshop::setIptcIrb(irbBuf.pData_, irbBuf.size_, iptcData_);
            exifData_.erase(pos);
            if (irbBuf.size_ != 0) {
                Value::UniquePtr value = Value::create(unsignedByte);
                value->read(irbBuf.pData_, irbBuf.size_, invalidByteOrder);
                Exifdatum iptcDatum(irbKey, value.get());
                exifData_.add(iptcDatum);
            }
        }
    }
