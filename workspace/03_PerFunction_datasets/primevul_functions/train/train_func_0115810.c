TypeId toTypeId(TiffType tiffType, uint16_t tag, IfdId group)
    {
        TypeId ti = TypeId(tiffType);

        if (tag == 0x9286 && group == exifId && ti == undefined) {
            ti = comment;
        }


        if ( ti == Exiv2::unsignedByte ) {
            if ( (tag == 0x0002 && group == nikonAFTId ) || (tag == 0x0047 && group == pentaxId) ) {
                ti = Exiv2::signedByte;
            }
        }
        return ti;
    }
