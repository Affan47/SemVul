pcx_write_page(gx_device_printer * pdev, gp_file * file, pcx_header * phdr,
               bool planar)
{
    int raster = gdev_prn_raster(pdev);
    uint rsize = ROUND_UP((pdev->width * phdr->bpp + 7) >> 3, 2);
    int height = pdev->height;
    int depth = pdev->color_info.depth;
    uint lsize = raster + rsize;
    byte *line = gs_alloc_bytes(pdev->memory, lsize, "pcx file buffer");
    byte *plane = line + raster;
    int y;
    int code = 0;

    if (line == 0)
        return_error(gs_error_VMerror);


    assign_ushort(phdr->x2, pdev->width - 1);
    assign_ushort(phdr->y2, height - 1);
    assign_ushort(phdr->hres, (int)pdev->x_pixels_per_inch);
    assign_ushort(phdr->vres, (int)pdev->y_pixels_per_inch);
    assign_ushort(phdr->bpl, (planar || depth == 1 ? rsize :
                              raster + (raster & 1)));


    if (gp_fwrite((const char *)phdr, 1, 128, file) < 128) {
        code = gs_error_ioerror;
        goto pcx_done;
    }

    for (y = 0; y < height; y++) {
        byte *row;
        byte *end;

        code = gdev_prn_get_bits(pdev, y, line, &row);
        if (code < 0)
            break;
        end = row + raster;
        if (!planar) {
            if (raster & 1) {
                *end = end[-1];
                ++end;
            }
            pcx_write_rle(row, end, 1, file);
        } else
            switch (depth) {

                case 4:
                    {
                        byte *pend = plane + rsize;
                        int shift;

                        for (shift = 0; shift < 4; shift++) {
                            register byte *from, *to;
                            register int bright = 1 << shift;
                            register int bleft = bright << 4;

                            for (from = row, to = plane;
                                 from < end; from += 4
                                ) {
                                *to++ =
                                    (from[0] & bleft ? 0x80 : 0) |
                                    (from[0] & bright ? 0x40 : 0) |
                                    (from[1] & bleft ? 0x20 : 0) |
                                    (from[1] & bright ? 0x10 : 0) |
                                    (from[2] & bleft ? 0x08 : 0) |
                                    (from[2] & bright ? 0x04 : 0) |
                                    (from[3] & bleft ? 0x02 : 0) |
                                    (from[3] & bright ? 0x01 : 0);
                            }

                            if (to < pend)
                                *to = to[-1];
                            pcx_write_rle(plane, pend, 1, file);
                        }
                    }
                    break;

                case 24:
                    {
                        int pnum;

                        for (pnum = 0; pnum < 3; ++pnum) {
                            pcx_write_rle(row + pnum, row + raster, 3, file);
                            if (pdev->width & 1)
                                gp_fputc(0, file);
                        }
                    }
                    break;

                default:
                    code = gs_note_error(gs_error_rangecheck);
                    goto pcx_done;

            }
    }

  pcx_done:
    gs_free_object(pdev->memory, line, "pcx file buffer");

    return code;
}
