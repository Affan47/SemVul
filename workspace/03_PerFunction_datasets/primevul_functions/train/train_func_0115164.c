void TiffEncoder::encodeMnEntry(TiffMnEntry* object, const Exifdatum* datum)
    {

        if (!object->mn_) encodeTiffEntryBase(object, datum);
    }
