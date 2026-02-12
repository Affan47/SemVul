void DL_Dxf::writeBlockRecord(DL_WriterA& dw) {
    dw.dxfString(  0, "TABLE");
    dw.dxfString(  2, "BLOCK_RECORD");
    if (version==DL_VERSION_2000) {
        dw.dxfHex(5, 1);
    }

    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbSymbolTable");
    }
    dw.dxfInt( 70, 1);

    dw.dxfString(  0, "BLOCK_RECORD");
    if (version==DL_VERSION_2000) {
        dw.dxfHex(5, 0x1F);
    }


    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbSymbolTableRecord");
        dw.dxfString(100, "AcDbBlockTableRecord");
    }
    dw.dxfString(  2, "*Model_Space");
    dw.dxfHex(340, 0x22);

    dw.dxfString(  0, "BLOCK_RECORD");
    if (version==DL_VERSION_2000) {
        dw.dxfHex(5, 0x1B);
    }


    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbSymbolTableRecord");
        dw.dxfString(100, "AcDbBlockTableRecord");
    }
    dw.dxfString(  2, "*Paper_Space");
    dw.dxfHex(340, 0x1E);

    dw.dxfString(  0, "BLOCK_RECORD");
    if (version==DL_VERSION_2000) {
        dw.dxfHex(5, 0x23);
    }


    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbSymbolTableRecord");
        dw.dxfString(100, "AcDbBlockTableRecord");
    }
    dw.dxfString(  2, "*Paper_Space0");
    dw.dxfHex(340, 0x26);


}
