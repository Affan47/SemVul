CreateRegularBifrustum(uint32_t numBaseEdges,double baseRadius,double height1,double ratio1,double height2,double ratio2)	{
	return CreateBifrustum(generateBase(numBaseEdges,baseRadius),height1,ratio1,height2,ratio2);
}
