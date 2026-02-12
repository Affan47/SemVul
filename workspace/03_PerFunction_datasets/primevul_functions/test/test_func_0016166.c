void DL_Dxf::addTextStyle(DL_CreationInterface* creationInterface) {
    std::string name = getStringValue(2, "");
    if (name.length()==0) {
        return;
    }

    DL_StyleData d(

        name,

        getIntValue(70, 0),

        getRealValue(40, 0.0),

        getRealValue(41, 0.0),

        getRealValue(50, 0.0),

        getIntValue(71, 0),

        getRealValue(42, 0.0),

        getStringValue(3, ""),

        getStringValue(4, "")
        );
    creationInterface->addTextStyle(d);
}
