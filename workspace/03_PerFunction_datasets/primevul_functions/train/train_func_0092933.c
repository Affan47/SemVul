EbmlElement::EbmlElement(uint64 aDefaultSize, bool bValueSet)
  :DefaultSize(aDefaultSize)
  ,SizeLength(0)
  ,bSizeIsFinite(true)
  ,ElementPosition(0)
  ,SizePosition(0)
  ,bValueIsSet(bValueSet)
  ,DefaultIsSet(false)
  ,bLocked(false)
{
  Size = DefaultSize;
}
