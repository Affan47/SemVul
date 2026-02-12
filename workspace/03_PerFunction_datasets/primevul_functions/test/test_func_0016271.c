void DL_Dxf::addLinetype(DL_CreationInterface* creationInterface) {
    std::string name = getStringValue(2, "");
    if (name.length()==0) {
        return;
    }
    int numDashes = getIntValue(73, 0);


    DL_LinetypeData d(

        name,

        getStringValue(3, ""),

        getIntValue(70, 0),

        numDashes,

        getRealValue(40, 0.0)


    );

    if (name != "By Layer" && name != "By Block" && name != "BYLAYER" && name != "BYBLOCK") {
        creationInterface->addLinetype(d);
    }
}
