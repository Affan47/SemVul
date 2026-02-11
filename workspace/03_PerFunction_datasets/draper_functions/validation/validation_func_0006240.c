getAlignment()
{
  if (presentationLUT == DVPSP_table)
  {
    Uint16 numberOfEntries = 0;
    Uint16 firstEntryMapped = 0xFFFF;
    if (EC_Normal != presentationLUTDescriptor.getUint16(numberOfEntries, 0)) numberOfEntries = 0;
    if (EC_Normal != presentationLUTDescriptor.getUint16(firstEntryMapped, 1)) firstEntryMapped = 0xFFFF;
    if ((numberOfEntries == 256)&&(firstEntryMapped == 0)) return DVPSK_table8;
    if ((numberOfEntries == 4096)&&(firstEntryMapped == 0)) return DVPSK_table12;
    return DVPSK_other;
  }
  return DVPSK_shape;
}
