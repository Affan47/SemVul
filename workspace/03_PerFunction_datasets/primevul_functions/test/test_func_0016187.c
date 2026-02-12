void DL_Dxf::writeBlockRecord(DL_WriterA& dw, const std::string& name) {
    dw.dxfString(  0, "BLOCK_RECORD");
    if (version==DL_VERSION_2000) {
        dw.handle();
    }

    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbSymbolTableRecord");
        dw.dxfString(100, "AcDbBlockTableRecord");
    }
    dw.dxfString(  2, name);
    dw.dxfHex(340, 0);
}
