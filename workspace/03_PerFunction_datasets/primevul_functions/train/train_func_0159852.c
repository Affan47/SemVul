IsLogicalVolumeDescriptorSupported (
  UDF_LOGICAL_VOLUME_DESCRIPTOR *LogicalVolDesc
  )
{


  switch (LogicalVolDesc->DomainIdentifier.Suffix.Domain.UdfRevision) {
  case 0x0102:
  case 0x0150:
  case 0x0200:
  case 0x0201:
  case 0x0250:
  case 0x0260:
    break;
  default:
    return FALSE;
  }


  if (LogicalVolDesc->NumberOfPartitionMaps > 1) {
    return FALSE;
  }


  if (LogicalVolDesc->PartitionMaps[0] != 1 ||
      LogicalVolDesc->PartitionMaps[1] != 6) {
    return FALSE;
  }

  return TRUE;
}
