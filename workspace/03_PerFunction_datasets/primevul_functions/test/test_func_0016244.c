void DL_Dxf::addDimLinear(DL_CreationInterface* creationInterface) {
    DL_DimensionData d = getDimData();


    DL_DimLinearData dl(

        getRealValue(13, 0.0),
        getRealValue(23, 0.0),
        getRealValue(33, 0.0),

        getRealValue(14, 0.0),
        getRealValue(24, 0.0),
        getRealValue(34, 0.0),

        getRealValue(50, 0.0),

        getRealValue(52, 0.0));
    creationInterface->addDimLinear(d, dl);
}
