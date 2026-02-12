bool isTiffImageTag(uint16_t tag, IfdId group)
    {

        static const TiffImgTagStruct tiffImageTags[] = {
            { 0x00fe, ifd0Id },
            { 0x00ff, ifd0Id },
            { 0x0100, ifd0Id },
            { 0x0101, ifd0Id },
            { 0x0102, ifd0Id },
            { 0x0103, ifd0Id },
            { 0x0106, ifd0Id },
            { 0x010a, ifd0Id },
            { 0x0111, ifd0Id },
            { 0x0115, ifd0Id },
            { 0x0116, ifd0Id },
            { 0x0117, ifd0Id },
            { 0x011a, ifd0Id },
            { 0x011b, ifd0Id },
            { 0x011c, ifd0Id },
            { 0x0122, ifd0Id },
            { 0x0123, ifd0Id },
            { 0x0124, ifd0Id },
            { 0x0125, ifd0Id },
            { 0x0128, ifd0Id },
            { 0x0129, ifd0Id },
            { 0x012d, ifd0Id },
            { 0x013d, ifd0Id },
            { 0x013e, ifd0Id },
            { 0x013f, ifd0Id },
            { 0x0140, ifd0Id },
            { 0x0141, ifd0Id },
            { 0x0142, ifd0Id },
            { 0x0143, ifd0Id },
            { 0x0144, ifd0Id },
            { 0x0145, ifd0Id },
            { 0x014c, ifd0Id },
            { 0x014d, ifd0Id },
            { 0x014e, ifd0Id },
            { 0x0150, ifd0Id },
            { 0x0151, ifd0Id },
            { 0x0152, ifd0Id },
            { 0x0153, ifd0Id },
            { 0x0154, ifd0Id },
            { 0x0155, ifd0Id },
            { 0x0156, ifd0Id },
            { 0x0157, ifd0Id },
            { 0x0158, ifd0Id },
            { 0x0159, ifd0Id },
            { 0x015a, ifd0Id },
            { 0x015b, ifd0Id },
            { 0x0200, ifd0Id },
            { 0x0201, ifd0Id },
            { 0x0202, ifd0Id },
            { 0x0203, ifd0Id },
            { 0x0205, ifd0Id },
            { 0x0206, ifd0Id },
            { 0x0207, ifd0Id },
            { 0x0208, ifd0Id },
            { 0x0209, ifd0Id },
            { 0x0211, ifd0Id },
            { 0x0212, ifd0Id },
            { 0x0213, ifd0Id },
            { 0x0214, ifd0Id },
            { 0x828d, ifd0Id },
            { 0x828e, ifd0Id },

            { 0x8824, ifd0Id },
            { 0x8828, ifd0Id },
            { 0x9102, ifd0Id },
            { 0x9217, ifd0Id },
        };


        if (find(tiffImageTags, TiffImgTagStruct::Key(tag, group))) {
#ifdef DEBUG
            ExifKey key(tag, groupName(group));
            std::cerr << "Image tag: " << key << " (3)\n";
#endif
            return true;
        }
#ifdef DEBUG
        std::cerr << "Not an image tag: " << tag << " (4)\n";
#endif
        return false;
    }
