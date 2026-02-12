bool DL_Dxf::handleMTextData(DL_CreationInterface* creationInterface) {

    if (groupCode==3) {
        creationInterface->addMTextChunk(groupValue);
        return true;
    }

    return false;
}
