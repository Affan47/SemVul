void TiffEncoder::encodeTiffEntryBase(TiffEntryBase* object, const Exifdatum* datum)
    {
        assert(object != 0);
        assert(datum != 0);

#ifdef DEBUG
        bool tooLarge = false;
#endif
        size_t newSize = datum->size();
        if (newSize > object->size_) {
            setDirty();
#ifdef DEBUG
            tooLarge = true;
#endif
        }
        object->updateValue(datum->getValue(), byteOrder());
#ifdef DEBUG
        ExifKey key(object->tag(), groupName(object->group()));
        std::cerr << "UPDATING DATA     " << key;
        if (tooLarge) {
            std::cerr << "\t\t\t ALLOCATED " << std::dec << object->size_ << " BYTES";
        }
#endif
    }
