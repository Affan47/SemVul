void DL_Dxf::addVertex(DL_CreationInterface* creationInterface) {


    if ((getIntValue(70, 0)&128) && !(getIntValue(70, 0)&64)) {
        return;
    }

    DL_VertexData d(getRealValue(10, 0.0),
                    getRealValue(20, 0.0),
                    getRealValue(30, 0.0),
                    getRealValue(42, 0.0));

    creationInterface->addVertex(d);
}
