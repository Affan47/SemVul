filepos_t KaxBlockVirtual::ReadData(IOCallback & input, ScopeMode )
{
  input.setFilePointer(SizePosition + CodedSizeLength(Size, SizeLength, bSizeIsFinite) + Size, seek_beginning);
  return GetSize();
}
