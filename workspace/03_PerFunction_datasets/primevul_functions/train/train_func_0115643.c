void TiffEncoder::add(
        TiffComponent* pRootDir,
        TiffComponent* pSourceDir,
        uint32_t       root
    )
    {
        assert(pRootDir != 0);

        writeMethod_ = wmIntrusive;
        pSourceTree_ = pSourceDir;


        del_ = false;

        ExifData::const_iterator posBo = exifData_.end();
        for (ExifData::const_iterator i = exifData_.begin();
             i != exifData_.end(); ++i) {

            IfdId group = groupId(i->groupName());

            if (group == mnId) {
                if (i->tag() == 0x0002) {
                    posBo = i;
                }
                continue;
            }


            if (isImageTag(i->tag(), group)) continue;


            TiffPath tiffPath;
            TiffCreator::getPath(tiffPath, i->tag(), group, root);
            TiffComponent* tc = pRootDir->addPath(i->tag(), tiffPath, pRootDir);
            TiffEntryBase* object = dynamic_cast<TiffEntryBase*>(tc);
#ifdef DEBUG
            if (object == 0) {
                std::cerr << "Warning: addPath() didn't add an entry for "
                          << i->groupName()
                          << " tag 0x" << std::setw(4) << std::setfill('0')
                          << std::hex << i->tag() << "\n";
            }
#endif
            if (object != 0) {
                encodeTiffComponent(object, &(*i));
            }
        }


        if (posBo == exifData_.end()) return;

        TiffFinder finder(0x927c, exifId);
        pRootDir->accept(finder);
        TiffMnEntry* te = dynamic_cast<TiffMnEntry*>(finder.result());
        if (te) {
            TiffIfdMakernote* tim = dynamic_cast<TiffIfdMakernote*>(te->mn_);
            if (tim) {

                ByteOrder bo = stringToByteOrder(posBo->toString());
                if (bo != invalidByteOrder) tim->setByteOrder(bo);
            }
        }

    }
