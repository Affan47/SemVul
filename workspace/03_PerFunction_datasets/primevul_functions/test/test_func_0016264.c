unsigned long DL_Dxf::writeImage(DL_WriterA& dw,
                       const DL_ImageData& data,
                       const DL_Attributes& attrib) {


    dw.entity("IMAGE");

    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbEntity");
    }
    dw.entityAttributes(attrib);
    if (version==DL_VERSION_2000) {
        dw.dxfString(100, "AcDbRasterImage");
        dw.dxfInt(90, 0);
    }

    dw.dxfReal(10, data.ipx);
    dw.dxfReal(20, data.ipy);
    dw.dxfReal(30, data.ipz);


    dw.dxfReal(11, data.ux);
    dw.dxfReal(21, data.uy);
    dw.dxfReal(31, data.uz);


    dw.dxfReal(12, data.vx);
    dw.dxfReal(22, data.vy);
    dw.dxfReal(32, data.vz);


    dw.dxfReal(13, data.width);
    dw.dxfReal(23, data.height);


    unsigned long handle = dw.handle(340);


    dw.dxfInt(70, 15);


    dw.dxfInt(280, 0);


    dw.dxfInt(281, data.brightness);
    dw.dxfInt(282, data.contrast);
    dw.dxfInt(283, data.fade);

    return handle;
}
