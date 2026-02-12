void DL_Dxf::addInsert(DL_CreationInterface* creationInterface) {


    std::string name = getStringValue(2, "");
    if (name.length()==0) {
        return;
    }

    DL_InsertData d(name,

                    getRealValue(10, 0.0),
                    getRealValue(20, 0.0),
                    getRealValue(30, 0.0),

                    getRealValue(41, 1.0),
                    getRealValue(42, 1.0),
                    getRealValue(43, 1.0),

                    getRealValue(50, 0.0),

                    getIntValue(70, 1),
                    getIntValue(71, 1),

                    getRealValue(44, 0.0),
                    getRealValue(45, 0.0));

    creationInterface->addInsert(d);
}
