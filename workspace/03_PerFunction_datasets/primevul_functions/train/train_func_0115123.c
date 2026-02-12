void TiffReader::visitIfdMakernote(TiffIfdMakernote* object)
    {
        assert(object != 0);

        object->setImageByteOrder(byteOrder());

        if (!object->readHeader(object->start(),
                                static_cast<uint32_t>(pLast_ - object->start()),
                                byteOrder())) {
#ifndef SUPPRESS_WARNINGS
            EXV_ERROR << "Failed to read "
                      << groupName(object->ifd_.group())
                      << " IFD Makernote header.\n";
#ifdef DEBUG
            if (static_cast<uint32_t>(pLast_ - object->start()) >= 16) {
                hexdump(std::cerr, object->start(), 16);
            }
#endif
#endif
            setGo(geKnownMakernote, false);
            return;
        }

        object->ifd_.setStart(object->start() + object->ifdOffset());


        object->mnOffset_ = static_cast<uint32_t>(object->start() - pData_);
        TiffRwState state(object->byteOrder(), object->baseOffset());
        setMnState(&state);

    }
