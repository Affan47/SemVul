FindAnchorVolumeDescriptorPointer (
  IN   EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  IN   EFI_DISK_IO_PROTOCOL                  *DiskIo,
  OUT  UDF_ANCHOR_VOLUME_DESCRIPTOR_POINTER  *AnchorPoint,
  OUT  EFI_LBA                               *LastRecordedBlock
  )
{
  EFI_STATUS                            Status;
  UINT32                                BlockSize;
  EFI_LBA                               EndLBA;
  UDF_DESCRIPTOR_TAG                    *DescriptorTag;
  UINTN                                 AvdpsCount;
  UINTN                                 Size;
  UDF_ANCHOR_VOLUME_DESCRIPTOR_POINTER  *AnchorPoints;
  INTN                                  Index;
  UDF_ANCHOR_VOLUME_DESCRIPTOR_POINTER  *AnchorPointPtr;
  EFI_LBA                               LastAvdpBlockNum;


  BlockSize = BlockIo->Media->BlockSize;
  EndLBA = BlockIo->Media->LastBlock;
  *LastRecordedBlock = EndLBA;
  AvdpsCount = 0;


  if (BlockSize < sizeof (UDF_ANCHOR_VOLUME_DESCRIPTOR_POINTER)) {
    DEBUG ((
      DEBUG_ERROR,
      "%a: Media block size 0x%x unable to hold an AVDP.\n",
      __FUNCTION__,
      BlockSize
      ));
    return EFI_UNSUPPORTED;
  }


  Status = DiskIo->ReadDisk (
    DiskIo,
    BlockIo->Media->MediaId,
    MultU64x32 (256, BlockSize),
    sizeof (*AnchorPoint),
    AnchorPoint
    );
  if (EFI_ERROR (Status)) {
    return Status;
  }

  DescriptorTag = &AnchorPoint->DescriptorTag;


  if (DescriptorTag->TagIdentifier == UdfAnchorVolumeDescriptorPointer) {
    DEBUG ((DEBUG_INFO, "%a: found AVDP at block %d\n", __FUNCTION__, 256));
    AvdpsCount++;
  }


  Status = DiskIo->ReadDisk (
    DiskIo,
    BlockIo->Media->MediaId,
    MultU64x32 ((UINT64)EndLBA - 256, BlockSize),
    sizeof (*AnchorPoint),
    AnchorPoint
    );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  if (DescriptorTag->TagIdentifier == UdfAnchorVolumeDescriptorPointer &&
      ++AvdpsCount == 2) {
    DEBUG ((DEBUG_INFO, "%a: found AVDP at block %Ld\n", __FUNCTION__,
            EndLBA - 256));
    return EFI_SUCCESS;
  }


  if (AvdpsCount == 0) {
    return EFI_VOLUME_CORRUPTED;
  }


  Status = DiskIo->ReadDisk (
    DiskIo,
    BlockIo->Media->MediaId,
    MultU64x32 ((UINT64)EndLBA, BlockSize),
    sizeof (*AnchorPoint),
    AnchorPoint
    );
  if (EFI_ERROR (Status)) {
    return Status;
  }


  if (DescriptorTag->TagIdentifier == UdfAnchorVolumeDescriptorPointer) {
    return EFI_SUCCESS;
  }


  Size = MAX_CORRECTION_BLOCKS_NUM * BlockSize;

  AnchorPoints = AllocateZeroPool (Size);
  if (AnchorPoints == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }


  Status = DiskIo->ReadDisk (
    DiskIo,
    BlockIo->Media->MediaId,
    MultU64x32 ((UINT64)EndLBA - MAX_CORRECTION_BLOCKS_NUM, BlockSize),
    Size,
    AnchorPoints
    );
  if (EFI_ERROR (Status)) {
    goto Out_Free;
  }

  Status = EFI_VOLUME_CORRUPTED;


  for (Index = MAX_CORRECTION_BLOCKS_NUM - 2; Index >= 0; Index--) {
    AnchorPointPtr = (VOID *)((UINTN)AnchorPoints + Index * BlockSize);

    DescriptorTag = &AnchorPointPtr->DescriptorTag;


    if (DescriptorTag->TagIdentifier == UdfAnchorVolumeDescriptorPointer) {


      LastAvdpBlockNum = EndLBA - (MAX_CORRECTION_BLOCKS_NUM - Index);
      DEBUG ((DEBUG_WARN, "%a: found AVDP at block %Ld\n", __FUNCTION__,
              LastAvdpBlockNum));
      DEBUG ((DEBUG_WARN, "%a: correcting last block from %Ld to %Ld\n",
              __FUNCTION__, EndLBA, LastAvdpBlockNum));


      CopyMem (AnchorPoint, AnchorPointPtr, sizeof (*AnchorPointPtr));


      *LastRecordedBlock = LastAvdpBlockNum;
      Status = EFI_SUCCESS;
      break;
    }
  }

Out_Free:
  FreePool (AnchorPoints);
  return Status;
}
