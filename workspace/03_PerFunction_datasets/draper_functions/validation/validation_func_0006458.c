TIFFReadRawStrip1(TIFF* tif,
    tstrip_t strip, tdata_t buf, tsize_t size, const char* module)
{
        TIFFDirectory *td = &tif->tif_dir;

        if (!isMapped(tif)) {
                tsize_t cc;

                if (!SeekOK(tif, td->td_stripoffset[strip])) {
                        TIFFErrorExt(tif->tif_clientdata, module,
                            "%s: Seek error at scanline %lu, strip %lu",
                            tif->tif_name,
                            (unsigned long) tif->tif_row, (unsigned long) strip);
                        return (-1);
                }
                cc = TIFFReadFile(tif, buf, size);
                if (cc != size) {
                        TIFFErrorExt(tif->tif_clientdata, module,
                "%s: Read error at scanline %lu; got %lu bytes, expected %lu",
                            tif->tif_name,
                            (unsigned long) tif->tif_row,
                            (unsigned long) cc,
                            (unsigned long) size);
                        return (-1);
                }
        } else {
                if (td->td_stripoffset[strip] + size > tif->tif_size) {
                        TIFFErrorExt(tif->tif_clientdata, module,
    "%s: Read error at scanline %lu, strip %lu; got %lu bytes, expected %lu",
                            tif->tif_name,
                            (unsigned long) tif->tif_row,
                            (unsigned long) strip,
                            (unsigned long) tif->tif_size - td->td_stripoffset[strip],
                            (unsigned long) size);
                        return (-1);
                }
                _TIFFmemcpy(buf, tif->tif_base + td->td_stripoffset[strip],
                            size);
        }
        return (size);
}
