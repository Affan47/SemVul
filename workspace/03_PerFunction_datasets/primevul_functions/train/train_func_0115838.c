bool TiffHeader::isImageTag(      uint16_t       tag,
                                      IfdId          group,
                                const PrimaryGroups* pPrimaryGroups) const
    {
        if (!hasImageTags_) {
#ifdef DEBUG
            std::cerr << "No image tags in this image\n";
#endif
            return false;
        }
#ifdef DEBUG
        ExifKey key(tag, groupName(group));
#endif

        if (   pPrimaryGroups != 0
            && !pPrimaryGroups->empty()
            && std::find(pPrimaryGroups->begin(), pPrimaryGroups->end(), group)
               == pPrimaryGroups->end()) {
#ifdef DEBUG
            std::cerr << "Not an image tag: " << key << " (1)\n";
#endif
            return false;
        }


        if (   pPrimaryGroups != 0
            && !pPrimaryGroups->empty()
            && group != ifd0Id) {
#ifdef DEBUG
            ExifKey key(tag, groupName(group));
            std::cerr << "Image tag: " << key << " (2)\n";
#endif
            return true;
        }

        return isTiffImageTag(tag, group);
    }
