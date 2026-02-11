InvertTable()
{
  vtkLookupTable *lut = vtkLookupTable::SafeDownCast(this->LookupTable);

  if ( lut )
    {
    int index = lut->GetNumberOfTableValues();
    unsigned char swap[4];
    size_t num = 4*sizeof(unsigned char);
    vtkUnsignedCharArray* table = lut->GetTable();
    for ( int count = 0; count < --index; count++ )
      {
      unsigned char *rgba1 = table->GetPointer(4*count);
      unsigned char *rgba2 = table->GetPointer(4*index);
      memcpy( swap,  rgba1, num );
      memcpy( rgba1, rgba2, num );
      memcpy( rgba2, swap,  num );
      }


    lut->SetTableValue( 0, lut->GetTableValue( 0 ) );
    }
}
