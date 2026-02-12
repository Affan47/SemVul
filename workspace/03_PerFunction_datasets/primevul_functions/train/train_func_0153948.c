void JBIG2Stream::readGenericRegionSeg(unsigned int segNum, bool imm, bool lossless, unsigned int length)
{
    std::unique_ptr<JBIG2Bitmap> bitmap;
    unsigned int w, h, x, y, segInfoFlags, extCombOp, rowCount;
    unsigned int flags, mmr, templ, tpgdOn;
    int atx[4], aty[4];


    if (!readULong(&w) || !readULong(&h) || !readULong(&x) || !readULong(&y) || !readUByte(&segInfoFlags)) {
        goto eofError;
    }
    extCombOp = segInfoFlags & 7;


    if (!readUByte(&flags)) {
        goto eofError;
    }
    mmr = flags & 1;
    templ = (flags >> 1) & 3;
    tpgdOn = (flags >> 3) & 1;


    if (!mmr) {
        if (templ == 0) {
            if (!readByte(&atx[0]) || !readByte(&aty[0]) || !readByte(&atx[1]) || !readByte(&aty[1]) || !readByte(&atx[2]) || !readByte(&aty[2]) || !readByte(&atx[3]) || !readByte(&aty[3])) {
                goto eofError;
            }
        } else {
            if (!readByte(&atx[0]) || !readByte(&aty[0])) {
                goto eofError;
            }
        }
    }


    if (!mmr) {
        resetGenericStats(templ, nullptr);
        arithDecoder->start();
    }


    bitmap = readGenericBitmap(mmr, w, h, templ, tpgdOn, false, nullptr, atx, aty, mmr ? length - 18 : 0);
    if (!bitmap) {
        return;
    }


    if (imm) {
        if (pageH == 0xffffffff && y + h > curPageH) {
            pageBitmap->expand(y + h, pageDefPixel);
            if (!pageBitmap->isOk()) {
                error(errSyntaxError, curStr->getPos(), "JBIG2Stream::readGenericRegionSeg: expand failed");
                return;
            }
        }
        pageBitmap->combine(bitmap.get(), x, y, extCombOp);


    } else {
        bitmap->setSegNum(segNum);
        segments.push_back(std::move(bitmap));
    }


    if (imm && length == 0xffffffff) {
        readULong(&rowCount);
    }

    return;

eofError:
    error(errSyntaxError, curStr->getPos(), "Unexpected EOF in JBIG2 stream");
}
