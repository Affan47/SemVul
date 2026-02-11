Write(std::ostream &os) const
{
  assert( (ItemLength + 4 + 1 + 1) == Size() );
  os.write( (char*)&ItemType, sizeof(ItemType) );
  os.write( (char*)&Reserved2, sizeof(Reserved2) );

  uint32_t copy = ItemLength;
  SwapperDoOp::SwapArray(&copy,1);
  os.write( (char*)&copy, sizeof(ItemLength) );
  std::vector<PresentationDataValue>::const_iterator it = V.begin();
  for( ; it != V.end(); ++it )
    {
    it->Write( os );
    }

  return os;
}
