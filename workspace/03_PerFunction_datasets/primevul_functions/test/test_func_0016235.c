void DL_Dxf::addMText(DL_CreationInterface* creationInterface) {
    double angle = 0.0;

    if (hasValue(50)) {
        if (libVersion<=0x02000200) {

            angle = getRealValue(50, 0.0);
        } else {
            angle = (getRealValue(50, 0.0)*2*M_PI)/360.0;
        }
    } else if (hasValue(11) && hasValue(21)) {
        double x = getRealValue(11, 0.0);
        double y = getRealValue(21, 0.0);

        if (fabs(x)<1.0e-6) {
            if (y>0.0) {
                angle = M_PI/2.0;
            } else {
                angle = M_PI/2.0*3.0;
            }
        } else {
            angle = atan(y/x);
        }
    }

    DL_MTextData d(

        getRealValue(10, 0.0),
        getRealValue(20, 0.0),
        getRealValue(30, 0.0),

        getRealValue(11, 0.0),
        getRealValue(21, 0.0),
        getRealValue(31, 0.0),

        getRealValue(40, 2.5),

        getRealValue(41, 0.0),

        getIntValue(71, 1),

        getIntValue(72, 1),

        getIntValue(73, 1),

        getRealValue(44, 1.0),

        getStringValue(1, ""),

        getStringValue(7, ""),

        angle);
    creationInterface->addMText(d);
}
