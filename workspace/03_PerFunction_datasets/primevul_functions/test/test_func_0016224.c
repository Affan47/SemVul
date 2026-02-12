void DL_Dxf::addAttribute(DL_CreationInterface* creationInterface) {
    DL_AttributeData d(

        getRealValue(10, 0.0),
        getRealValue(20, 0.0),
        getRealValue(30, 0.0),

        getRealValue(11, 0.0),
        getRealValue(21, 0.0),
        getRealValue(31, 0.0),

        getRealValue(40, 2.5),

        getRealValue(41, 1.0),

        getIntValue(71, 0),

        getIntValue(72, 0),

        getIntValue(74, 0),

        getStringValue(2, ""),

        getStringValue(1, ""),

        getStringValue(7, ""),

        (getRealValue(50, 0.0)*2*M_PI)/360.0);

    creationInterface->addAttribute(d);
}
