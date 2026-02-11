TIFFWriteRationalArray(TIFF* tif, TIFFDirEntry* dir, float* v)
{
        uint32 i;
        uint32* t;
        int status;

        t = (uint32*) _TIFFmalloc(2 * dir->tdir_count * sizeof (uint32));
        if (t == NULL) {
                TIFFErrorExt(tif->tif_clientdata, tif->tif_name,
                    "No space to write RATIONAL array");
                return (0);
        }
        for (i = 0; i < dir->tdir_count; i++) {
                float fv = v[i];
                int sign = 1;
                uint32 den;

                if (fv < 0) {
                        if (dir->tdir_type == TIFF_RATIONAL) {
                                TIFFWarningExt(tif->tif_clientdata, tif->tif_name,
        "\"%s\": Information lost writing value (%g) as (unsigned) RATIONAL",
                                _TIFFFieldWithTag(tif,dir->tdir_tag)->field_name,
                                fv);
                                fv = 0;
                        } else
                                fv = -fv, sign = -1;
                }
                den = 1L;
                if (fv > 0) {
                        while (fv < 1L<<(31-3) && den < 1L<<(31-3))
                                fv *= 1<<3, den *= 1L<<3;
                }
                t[2*i+0] = (uint32) (sign * (fv + 0.5));
                t[2*i+1] = den;
        }
        status = TIFFWriteData(tif, dir, (char *)t);
        _TIFFfree((char*) t);
        return (status);
}
