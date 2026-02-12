void DL_Dxf::addText(DL_CreationInterface* creationInterface) {
    DL_TextData d(

        getRealValue(10, 0.0),
        getRealValue(20, 0.0),
        getRealValue(30, 0.0),

        getRealValue(11, DL_NANDOUBLE),
        getRealValue(21, DL_NANDOUBLE),
        getRealValue(31, DL_NANDOUBLE),

        getRealValue(40, 2.5),

        getRealValue(41, 1.0),

        getIntValue(71, 0),

        getIntValue(72, 0),

        getIntValue(73, 0),

        getStringValue(1, ""),

        getStringValue(7, ""),

        (getRealValue(50, 0.0)*2*M_PI)/360.0);

    creationInterface->addText(d);
}
