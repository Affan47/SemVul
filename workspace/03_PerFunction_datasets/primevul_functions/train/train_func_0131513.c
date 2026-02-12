cmsBool HandleEXIF(struct jpeg_decompress_struct* cinfo)
{
    jpeg_saved_marker_ptr ptr;
    uint32_t ifd_ofs;
    int pos = 0, swapBytes = 0;
    uint32_t i, numEntries;
    double XRes = -1, YRes = -1;
    int Unit = 2;


    for (ptr = cinfo ->marker_list; ptr; ptr = ptr ->next) {

        if ((ptr ->marker == JPEG_APP0+1) && ptr ->data_length > 6) {
            JOCTET FAR* data = ptr -> data;

            if (memcmp(data, "Exif\0\0", 6) == 0) {

                data += 6;


                pos = 0;
                if (read16(data, pos, 0) == INTEL_BYTE_ORDER) {
                    swapBytes = 1;
                }

                pos += 2;


                pos += 2;


                ifd_ofs = read32(data, pos, swapBytes);


                numEntries = read16(data, ifd_ofs, swapBytes);

                for (i=0; i < numEntries; i++) {

                    uint32_t entryOffset = ifd_ofs + 2 + (12 * i);
                    uint32_t tag = read16(data, entryOffset, swapBytes);

                    switch (tag) {

                    case RESOLUTION_UNIT:
                        if (!read_tag(data, entryOffset, swapBytes, &Unit)) return FALSE;
                        break;

                    case XRESOLUTION:
                        if (!read_tag(data, entryOffset, swapBytes, &XRes)) return FALSE;
                        break;

                    case YRESOLUTION:
                        if (!read_tag(data, entryOffset, swapBytes, &YRes)) return FALSE;
                        break;

                    default:;
                    }

                }


                if (XRes != -1 && YRes != -1)
                {


                    switch (Unit) {

                    case 2:

                        cinfo ->X_density = (UINT16) floor(XRes + 0.5);
                        cinfo ->Y_density = (UINT16) floor(YRes + 0.5);
                        break;

                    case 1:

                        cinfo ->X_density = (UINT16) floor(XRes * 2.54 + 0.5);
                        cinfo ->Y_density = (UINT16) floor(YRes * 2.54 + 0.5);
                        break;

                    default: return FALSE;
                    }

                    cinfo ->density_unit = 1;

                }


            }
        }
    }
    return FALSE;
}
