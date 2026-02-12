DL_DimensionData DL_Dxf::getDimData() {

    DL_DimensionData ret(

               getRealValue(10, 0.0),
               getRealValue(20, 0.0),
               getRealValue(30, 0.0),

               getRealValue(11, 0.0),
               getRealValue(21, 0.0),
               getRealValue(31, 0.0),

               getIntValue(70, 0),

               getIntValue(71, 5),

               getIntValue(72, 1),

               getRealValue(41, 1.0),

               getStringValue(1, ""),

               getStringValue(3, ""),

               getRealValue(53, 0.0));
    ret.arrow1Flipped = getIntValue(74, 0)==1;
    ret.arrow2Flipped = getIntValue(75, 0)==1;
    return ret;
}
