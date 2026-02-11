FillZeissStruct(char *cz)
{
  memset(cz, 0, TIF_CZ_LSMINFO_SIZE);
  zeiss_info *z = reinterpret_cast< zeiss_info * >( cz );
  z->U32MagicNumber = 0x0400494c;
  z->S32StructureSize = TIF_CZ_LSMINFO_SIZE;
  z->S32DimensionX = m_Dimensions[0];
  z->S32DimensionY = m_Dimensions[1];
  if ( m_NumberOfDimensions == 3 )
    {
    z->S32DimensionZ = m_Dimensions[2];
    }
  z->S32DimensionChannels = m_NumberOfComponents;
  z->S32DimensionTime = 1;
  z->S32DataType = 0;
  z->S32ThumbnailX = 128 * m_Dimensions[0] / m_Dimensions[1];
  z->S32ThumbnailY = 128;
  z->F64VoxelSizeX = m_Spacing[0];
  z->F64VoxelSizeY = m_Spacing[1];
  if ( m_NumberOfDimensions == 3 )
    {
    z->F64VoxelSizeZ = m_Spacing[2];
    }
}
