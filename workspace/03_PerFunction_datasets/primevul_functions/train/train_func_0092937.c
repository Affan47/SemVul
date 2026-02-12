filepos_t EbmlElement::OverwriteHead(IOCallback & output, bool bKeepPosition)
{
  if (ElementPosition == 0) {
    return 0;
  }

  uint64 CurrentPosition = output.getFilePointer();
  output.setFilePointer(GetElementPosition());
  filepos_t Result = MakeRenderHead(output, bKeepPosition);
  output.setFilePointer(CurrentPosition);
  return Result;
}
