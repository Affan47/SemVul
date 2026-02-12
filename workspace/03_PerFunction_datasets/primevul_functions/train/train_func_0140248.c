ReadFile (
  IN      EFI_BLOCK_IO_PROTOCOL           *BlockIo,
  IN      EFI_DISK_IO_PROTOCOL            *DiskIo,
  IN      UDF_VOLUME_INFO                 *Volume,
  IN      UDF_LONG_ALLOCATION_DESCRIPTOR  *ParentIcb,
  IN      VOID                            *FileEntryData,
  IN OUT  UDF_READ_FILE_INFO              *ReadFileInfo
  )
{
  EFI_STATUS              Status;
  UINT32                  LogicalBlockSize;
  VOID                    *Data;
  UINT64                  Length;
  VOID                    *Ad;
  UINT64                  AdOffset;
  UINT64                  Lsn;
  BOOLEAN                 DoFreeAed;
  UINT64                  FilePosition;
  UINT64                  Offset;
  UINT64                  DataOffset;
  UINT64                  BytesLeft;
  UINT64                  DataLength;
  BOOLEAN                 FinishedSeeking;
  UINT32                  ExtentLength;
  UDF_FE_RECORDING_FLAGS  RecordingFlags;

  LogicalBlockSize  = Volume->LogicalVolDesc.LogicalBlockSize;
  DoFreeAed         = FALSE;


  BytesLeft = 0;
  DataOffset = 0;
  FilePosition = 0;
  FinishedSeeking = FALSE;
  Data = NULL;

  switch (ReadFileInfo->Flags) {
  case ReadFileGetFileSize:
  case ReadFileAllocateAndRead:


    ReadFileInfo->ReadLength = 0;
    ReadFileInfo->FileData = NULL;
    break;
  case ReadFileSeekAndRead:


    Length = ReadFileInfo->FileSize - ReadFileInfo->FilePosition;
    if (ReadFileInfo->FileDataSize > Length) {


      ReadFileInfo->FileDataSize = Length;
    }


    BytesLeft = ReadFileInfo->FileDataSize;
    DataOffset = 0;
    FilePosition = 0;
    FinishedSeeking = FALSE;

    break;
  }

  RecordingFlags = GET_FE_RECORDING_FLAGS (FileEntryData);
  switch (RecordingFlags) {
  case InlineData:


    Status = GetFileEntryData (FileEntryData, Volume->FileEntrySize, &Data, &Length);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    if (ReadFileInfo->Flags == ReadFileGetFileSize) {
      ReadFileInfo->ReadLength = Length;
    } else if (ReadFileInfo->Flags == ReadFileAllocateAndRead) {


      ReadFileInfo->FileData = AllocatePool ((UINTN) Length);
      if (ReadFileInfo->FileData == NULL) {
        return EFI_OUT_OF_RESOURCES;
      }


      CopyMem (ReadFileInfo->FileData, Data, (UINTN) Length);
      ReadFileInfo->ReadLength = Length;
    } else if (ReadFileInfo->Flags == ReadFileSeekAndRead) {


      CopyMem (
        ReadFileInfo->FileData,
        (VOID *)((UINT8 *)Data + ReadFileInfo->FilePosition),
        (UINTN) ReadFileInfo->FileDataSize
        );

      ReadFileInfo->FilePosition += ReadFileInfo->FileDataSize;
    } else {
      ASSERT (FALSE);
      return EFI_INVALID_PARAMETER;
    }

    Status = EFI_SUCCESS;
    break;

  case LongAdsSequence:
  case ShortAdsSequence:


    Status = GetAdsInformation (FileEntryData, Volume->FileEntrySize, &Data, &Length);
    if (EFI_ERROR (Status)) {
      return Status;
    }

    AdOffset = 0;

    for (;;) {


      Status = GetAllocationDescriptor (
        RecordingFlags,
        Data,
        &AdOffset,
        Length,
        &Ad
        );
      if (Status == EFI_DEVICE_ERROR) {
        Status = EFI_SUCCESS;
        goto Done;
      }


      if (GET_EXTENT_FLAGS (RecordingFlags, Ad) == ExtentIsNextExtent) {
        if (!DoFreeAed) {
          DoFreeAed = TRUE;
        } else {
          FreePool (Data);
        }

        Status = GetAedAdsData (
          BlockIo,
          DiskIo,
          Volume,
          ParentIcb,
          RecordingFlags,
          Ad,
          &Data,
          &Length
          );
        if (EFI_ERROR (Status)) {
          goto Error_Get_Aed;
        }
        ASSERT (Data != NULL);

        AdOffset = 0;
        continue;
      }

      ExtentLength = GET_EXTENT_LENGTH (RecordingFlags, Ad);

      Status = GetAllocationDescriptorLsn (RecordingFlags,
                                           Volume,
                                           ParentIcb,
                                           Ad,
                                           &Lsn);
      if (EFI_ERROR (Status)) {
        goto Done;
      }

      switch (ReadFileInfo->Flags) {
      case ReadFileGetFileSize:
        ReadFileInfo->ReadLength += ExtentLength;
        break;
      case ReadFileAllocateAndRead:


        Status = GrowUpBufferToNextAd (
          RecordingFlags,
          Ad,
          &ReadFileInfo->FileData,
          ReadFileInfo->ReadLength
          );
        if (EFI_ERROR (Status)) {
          goto Error_Alloc_Buffer_To_Next_Ad;
        }


        Status = DiskIo->ReadDisk (
          DiskIo,
          BlockIo->Media->MediaId,
          MultU64x32 (Lsn, LogicalBlockSize),
          ExtentLength,
          (VOID *)((UINT8 *)ReadFileInfo->FileData +
                   ReadFileInfo->ReadLength)
          );
        if (EFI_ERROR (Status)) {
          goto Error_Read_Disk_Blk;
        }

        ReadFileInfo->ReadLength += ExtentLength;
        break;
      case ReadFileSeekAndRead:


        if (FinishedSeeking) {
          Offset = 0;
          goto Skip_File_Seek;
        }

        if (FilePosition + ExtentLength < ReadFileInfo->FilePosition) {
          FilePosition += ExtentLength;
          goto Skip_Ad;
        }

        if (FilePosition + ExtentLength > ReadFileInfo->FilePosition) {
          Offset = ReadFileInfo->FilePosition - FilePosition;
        } else {
          Offset = 0;
        }


        FinishedSeeking = TRUE;

      Skip_File_Seek:


        if (ExtentLength - Offset > BytesLeft) {
          DataLength = BytesLeft;
        } else {
          DataLength = ExtentLength - Offset;
        }


        Status = DiskIo->ReadDisk (
          DiskIo,
          BlockIo->Media->MediaId,
          Offset + MultU64x32 (Lsn, LogicalBlockSize),
          (UINTN) DataLength,
          (VOID *)((UINT8 *)ReadFileInfo->FileData +
                   DataOffset)
          );
        if (EFI_ERROR (Status)) {
          goto Error_Read_Disk_Blk;
        }


        DataOffset += DataLength;
        ReadFileInfo->FilePosition += DataLength;

        BytesLeft -= DataLength;
        if (BytesLeft == 0) {


          Status = EFI_SUCCESS;
          goto Done;
        }

        break;
      }

    Skip_Ad:


      AdOffset += AD_LENGTH (RecordingFlags);
    }

    break;
  case ExtendedAdsSequence:

    ASSERT (FALSE);
    Status = EFI_UNSUPPORTED;
    break;

  default:


    Status = EFI_UNSUPPORTED;
    break;
  }

Done:
  if (DoFreeAed) {
    FreePool (Data);
  }

  return Status;

Error_Read_Disk_Blk:
Error_Alloc_Buffer_To_Next_Ad:
  if (ReadFileInfo->Flags != ReadFileSeekAndRead) {
    FreePool (ReadFileInfo->FileData);
  }

  if (DoFreeAed) {
    FreePool (Data);
  }

Error_Get_Aed:
  return Status;
}
