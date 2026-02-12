int ImagingLibTiffMergeFieldInfo(ImagingCodecState state, TIFFDataType field_type, int key, int is_var_length){

    TIFFSTATE *clientstate = (TIFFSTATE *)state->context;
    char field_name[10];
    uint32 n;
    int status = 0;


    int readcount = 0;

    int writecount = 1;

    int passcount = 0;

    TIFFFieldInfo info[] = {
        { key, readcount, writecount, field_type, FIELD_CUSTOM, 1, passcount, field_name }
    };

    if (is_var_length) {
        info[0].field_writecount = -1;
    }

    if (is_var_length && field_type != TIFF_ASCII) {
        info[0].field_passcount = 1;
    }

    n = sizeof(info) / sizeof(info[0]);


#if TIFFLIB_VERSION >= 20111221 && TIFFLIB_VERSION != 20120218 && TIFFLIB_VERSION != 20120922
    status = TIFFMergeFieldInfo(clientstate->tiff, info, n);
#else
    TIFFMergeFieldInfo(clientstate->tiff, info, n);
#endif
    return status;
}
