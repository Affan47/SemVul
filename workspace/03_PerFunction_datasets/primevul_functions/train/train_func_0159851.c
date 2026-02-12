FindLogicalVolumeLocation (
  IN   EFI_BLOCK_IO_PROTOCOL                 *BlockIo,
  IN   EFI_DISK_IO_PROTOCOL                  *DiskIo,
  IN   UDF_ANCHOR_VOLUME_DESCRIPTOR_POINTER  *AnchorPoint,
  IN   EFI_LBA                               LastRecordedBlock,
  OUT  UINT64                                *MainVdsStartBlock,
  OUT  UINT64                                *MainVdsEndBlock
  )
{
  EFI_STATUS                     Status;
  UINT32                         BlockSize;
  UDF_EXTENT_AD                  *ExtentAd;
  UINT64                         SeqBlocksNum;
  UINT64                         SeqStartBlock;
  UINT64                         GuardMainVdsStartBlock;
  VOID                           *Buffer;
  UINT64                         SeqEndBlock;
  BOOLEAN                        StopSequence;
  UINTN                          LvdsCount;
  UDF_LOGICAL_VOLUME_DESCRIPTOR  *LogicalVolDesc;
  UDF_DESCRIPTOR_TAG             *DescriptorTag;

  BlockSize = BlockIo->Media->BlockSize;
  ExtentAd = &AnchorPoint->MainVolumeDescriptorSequenceExtent;


  SeqBlocksNum = DivU64x32 ((UINT64)ExtentAd->ExtentLength, BlockSize);
  if (SeqBlocksNum < 16 || (EFI_LBA)SeqBlocksNum > LastRecordedBlock + 1) {
    return EFI_VOLUME_CORRUPTED;
  }


  SeqStartBlock = (UINT64)ExtentAd->ExtentLocation;
  if (SeqStartBlock > LastRecordedBlock ||
      SeqStartBlock + SeqBlocksNum - 1 > LastRecordedBlock) {
    return EFI_VOLUME_CORRUPTED;
  }

  GuardMainVdsStartBlock = SeqStartBlock;


  Buffer = AllocateZeroPool ((UINTN)BlockSize);
  if (Buffer == NULL) {
    return EFI_OUT_OF_RESOURCES;
  }

  SeqEndBlock = SeqStartBlock + SeqBlocksNum;
  StopSequence = FALSE;
  LvdsCount = 0;
  Status = EFI_VOLUME_CORRUPTED;


  for (; SeqStartBlock < SeqEndBlock && !StopSequence; SeqStartBlock++) {


    Status = BlockIo->ReadBlocks (
      BlockIo,
      BlockIo->Media->MediaId,
      SeqStartBlock,
      BlockSize,
      Buffer
      );
    if (EFI_ERROR (Status)) {
      goto Out_Free;
    }

    DescriptorTag = Buffer;


    switch (DescriptorTag->TagIdentifier) {
    case UdfPrimaryVolumeDescriptor:
    case UdfImplemenationUseVolumeDescriptor:
    case UdfPartitionDescriptor:
    case UdfUnallocatedSpaceDescriptor:
      break;

    case UdfLogicalVolumeDescriptor:
      LogicalVolDesc = Buffer;


      if (++LvdsCount > 1 ||
          !IsLogicalVolumeDescriptorSupported (LogicalVolDesc)) {
        Status = EFI_UNSUPPORTED;
        StopSequence = TRUE;
      }

      break;

    case UdfTerminatingDescriptor:


      StopSequence = TRUE;
      break;

    default:


      Status = EFI_VOLUME_CORRUPTED;
      goto Out_Free;
    }
  }


  if (!EFI_ERROR (Status) && LvdsCount == 1) {
    *MainVdsStartBlock = GuardMainVdsStartBlock;


    *MainVdsEndBlock = LastRecordedBlock;

    Status = EFI_SUCCESS;
  }

Out_Free:


  FreePool (Buffer);

  return Status;
}
