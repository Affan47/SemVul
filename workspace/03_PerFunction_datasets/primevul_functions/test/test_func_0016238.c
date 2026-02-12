void DL_Dxf::addDimDiametric(DL_CreationInterface* creationInterface) {
    DL_DimensionData d = getDimData();


    DL_DimDiametricData dr(

        getRealValue(15, 0.0),
        getRealValue(25, 0.0),
        getRealValue(35, 0.0),

        getRealValue(40, 0.0));
    creationInterface->addDimDiametric(d, dr);
}
