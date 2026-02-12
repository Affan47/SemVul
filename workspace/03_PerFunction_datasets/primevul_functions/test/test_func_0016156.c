void DL_Dxf::addDimOrdinate(DL_CreationInterface* creationInterface) {
    DL_DimensionData d = getDimData();


    DL_DimOrdinateData dl(

        getRealValue(13, 0.0),
        getRealValue(23, 0.0),
        getRealValue(33, 0.0),

        getRealValue(14, 0.0),
        getRealValue(24, 0.0),
        getRealValue(34, 0.0),
        (getIntValue(70, 0)&64)==64
    );
    creationInterface->addDimOrdinate(d, dl);
}
