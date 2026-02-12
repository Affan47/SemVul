FindUdfFileSystem (
  IN EFI_BLOCK_IO_PROTOCOL  *BlockIo,
  IN EFI_DISK_IO_PROTOCOL   *DiskIo,
  OUT EFI_LBA               *StartingLBA,
  OUT EFI_LBA               *EndingLBA
  )
{
  EFI_STATUS                            Status;
  UDF_ANCHOR_VOLUME_DESCRIPTOR_POINTER  AnchorPoint;
  EFI_LBA                               LastRecordedBlock;


  Status = FindUdfVolumeIdentifiers (BlockIo, DiskIo);
  if (EFI_ERROR (Status)) {
    return Status;
  }


  Status = FindAnchorVolumeDescriptorPointer (
    BlockIo,
    DiskIo,
    &AnchorPoint,
    &LastRecordedBlock
    );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  Status = FindLogicalVolumeLocation (
    BlockIo,
    DiskIo,
    &AnchorPoint,
    LastRecordedBlock,
    (UINT64 *)StartingLBA,
    (UINT64 *)EndingLBA
    );

  return Status;
}
