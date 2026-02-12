void DL_Dxf::addSetting(DL_CreationInterface* creationInterface) {
    int c = -1;
    std::map<int,std::string>::iterator it = values.begin();
    if (it!=values.end()) {
        c = it->first;
    }


    if (c>=0 && c<=9) {
        creationInterface->setVariableString(settingKey, values[c], c);
 #ifdef DL_COMPAT

        creationInterface->setVariableString(settingKey.c_str(), values[c].c_str(), c);
 #endif
    }

    else if (c>=10 && c<=39) {
        if (c==10) {
            creationInterface->setVariableVector(
                settingKey,
                getRealValue(c, 0.0),
                getRealValue(c+10, 0.0),
                getRealValue(c+20, 0.0),
                c);
        }
    }

    else if (c>=40 && c<=59) {
        creationInterface->setVariableDouble(settingKey, getRealValue(c, 0.0), c);
    }

    else if (c>=60 && c<=99) {
        creationInterface->setVariableInt(settingKey, getIntValue(c, 0), c);
    }

    else if (c>=0) {
        creationInterface->setVariableString(settingKey, getStringValue(c, ""), c);
    }
}
