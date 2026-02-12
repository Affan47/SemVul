void JBIG2Stream::readGenericRefinementRegionSeg(unsigned int segNum, bool imm, bool lossless, unsigned int length, unsigned int *refSegs, unsigned int nRefSegs)
{
    std::unique_ptr<JBIG2Bitmap> bitmap;
    JBIG2Bitmap *refBitmap;
    unsigned int w, h, x, y, segInfoFlags, extCombOp;
    unsigned int flags, templ, tpgrOn;
    int atx[2], aty[2];
    JBIG2Segment *seg;


    if (!readULong(&w) || !readULong(&h) || !readULong(&x) || !readULong(&y) || !readUByte(&segInfoFlags)) {
        goto eofError;
    }
    extCombOp = segInfoFlags & 7;


    if (!readUByte(&flags)) {
        goto eofError;
    }
    templ = flags & 1;
    tpgrOn = (flags >> 1) & 1;


    if (!templ) {
        if (!readByte(&atx[0]) || !readByte(&aty[0]) || !readByte(&atx[1]) || !readByte(&aty[1])) {
            goto eofError;
        }
    }


    if (nRefSegs == 0 || imm) {
        if (pageH == 0xffffffff && y + h > curPageH) {
            pageBitmap->expand(y + h, pageDefPixel);
        }
    }


    if (nRefSegs > 1) {
        error(errSyntaxError, curStr->getPos(), "Bad reference in JBIG2 generic refinement segment");
        return;
    }
    if (nRefSegs == 1) {
        seg = findSegment(refSegs[0]);
        if (seg == nullptr || seg->getType() != jbig2SegBitmap) {
            error(errSyntaxError, curStr->getPos(), "Bad bitmap reference in JBIG2 generic refinement segment");
            return;
        }
        refBitmap = (JBIG2Bitmap *)seg;
    } else {
        refBitmap = pageBitmap->getSlice(x, y, w, h);
    }


    resetRefinementStats(templ, nullptr);
    arithDecoder->start();


    bitmap = readGenericRefinementRegion(w, h, templ, tpgrOn, refBitmap, 0, 0, atx, aty);


    if (imm && bitmap) {
        pageBitmap->combine(bitmap.get(), x, y, extCombOp);


    } else {
        if (bitmap) {
            bitmap->setSegNum(segNum);
            segments.push_back(std::move(bitmap));
        } else {
            error(errSyntaxError, curStr->getPos(), "readGenericRefinementRegionSeg with null bitmap");
        }
    }


    if (nRefSegs == 1) {
        discardSegment(refSegs[0]);
    } else {
        delete refBitmap;
    }

    return;

eofError:
    error(errSyntaxError, curStr->getPos(), "Unexpected EOF in JBIG2 stream");
}
