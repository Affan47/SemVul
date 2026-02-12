void TiffEncoder::encodeTiffComponent(
              TiffEntryBase* object,
        const Exifdatum*     datum
    )
    {
        assert(object != 0);

        ExifData::iterator pos = exifData_.end();
        const Exifdatum* ed = datum;
        if (ed == 0) {

            ExifKey key(object->tag(), groupName(object->group()));
            pos = exifData_.findKey(key);
            if (pos != exifData_.end()) {
                ed = &(*pos);
                if (object->idx() != pos->idx()) {

                    ExifData::iterator pos2 =
                        std::find_if(exifData_.begin(), exifData_.end(),
                                     FindExifdatum2(object->group(), object->idx()));
                    if (pos2 != exifData_.end() && pos2->key() == key.key()) {
                        ed = &(*pos2);
                        pos = pos2;
                    }
                }
            }
            else {
                setDirty();
#ifdef DEBUG
                std::cerr << "DELETING          " << key << ", idx = " << object->idx() << "\n";
#endif
            }
        }
        else {


            object->idx_ = ed->idx();
        }


        if (ed && !isImageTag(object->tag(), object->group())) {
            const EncoderFct fct = findEncoderFct_(make_, object->tag(), object->group());
            if (fct) {

                EXV_CALL_MEMBER_FN(*this, fct)(object, ed);
            }
            else {


                object->encode(*this, ed);
            }
        }
        if (del_ && pos != exifData_.end()) {
            exifData_.erase(pos);
        }
#ifdef DEBUG
        std::cerr << "\n";
#endif
    }
