void DL_Dxf::writeStyle(DL_WriterA& dw, const DL_StyleData& style) {


    dw.dxfString(  0, "STYLE");
    if (version==DL_VERSION_2000) {
        if (style.name=="Standard") {

            styleHandleStd = dw.handle();
        }
        else {
            dw.handle();
        }
    }

    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbSymbolTableRecord");
        dw.dxfString(100, "AcDbTextStyleTableRecord");
    }
    dw.dxfString(  2, style.name);
    dw.dxfInt( 70, style.flags);
    dw.dxfReal( 40, style.fixedTextHeight);
    dw.dxfReal( 41, style.widthFactor);
    dw.dxfReal( 50, style.obliqueAngle);
    dw.dxfInt( 71, style.textGenerationFlags);
    dw.dxfReal( 42, style.lastHeightUsed);
    if (version==DL_VERSION_2000) {
        dw.dxfString(  3, "");
        dw.dxfString(  4, "");
        dw.dxfString(1001, "ACAD");

        dw.dxfString(1000, style.primaryFontFile);
        int xFlags = 0;
        if (style.bold) {
            xFlags = xFlags|0x2000000;
        }
        if (style.italic) {
            xFlags = xFlags|0x1000000;
        }
        dw.dxfInt(1071, xFlags);
    }
    else {
        dw.dxfString(  3, style.primaryFontFile);
        dw.dxfString(  4, style.bigFontFile);
    }

}
