void DL_Dxf::addImage(DL_CreationInterface* creationInterface) {
    DL_ImageData id(
        getStringValue(340, ""),

        getRealValue(10, 0.0),
        getRealValue(20, 0.0),
        getRealValue(30, 0.0),

        getRealValue(11, 1.0),
        getRealValue(21, 0.0),
        getRealValue(31, 0.0),

        getRealValue(12, 0.0),
        getRealValue(22, 1.0),
        getRealValue(32, 0.0),

        getIntValue(13, 1),
        getIntValue(23, 1),

        getIntValue(281, 50),
        getIntValue(282, 50),
        getIntValue(283, 0));

    creationInterface->addImage(id);
    creationInterface->endEntity();
    currentObjectType = DL_UNKNOWN;
}
