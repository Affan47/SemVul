void __fastcall TSCPFileSystem::SCPSource(const UnicodeString FileName,
  const UnicodeString TargetDir, const TCopyParamType * CopyParam, int Params,
  TFileOperationProgressType * OperationProgress, int Level)
{
  UnicodeString DestFileName =
    FTerminal->ChangeFileName(
      CopyParam, ExtractFileName(FileName), osLocal, Level == 0);

  FTerminal->LogEvent(FORMAT(L"File: \"%s\"", (FileName)));

  OperationProgress->SetFile(FileName, false);

  if (!FTerminal->AllowLocalFileTransfer(FileName, CopyParam, OperationProgress))
  {
    throw ESkipFile();
  }

  TLocalFileHandle Handle;
  FTerminal->OpenLocalFile(FileName, GENERIC_READ, Handle);

  OperationProgress->SetFileInProgress();

  if (Handle.Directory)
  {
    SCPDirectorySource(FileName, TargetDir, CopyParam, Params, OperationProgress, Level);
  }
  else
  {
    UnicodeString AbsoluteFileName = FTerminal->AbsolutePath(TargetDir + DestFileName, false);

    DebugAssert(Handle.Handle);
    std::unique_ptr<TStream> Stream(new TSafeHandleStream((THandle)Handle.Handle));


    FTerminal->LogEvent(FORMAT(L"Copying \"%s\" to remote directory started.", (FileName)));

    OperationProgress->SetLocalSize(Handle.Size);


    OperationProgress->SetTransferSize(OperationProgress->LocalSize);
    OperationProgress->SetTransferringFile(false);

    FTerminal->SelectSourceTransferMode(Handle, CopyParam);

    TUploadSessionAction Action(FTerminal->ActionLog);
    Action.FileName(ExpandUNCFileName(FileName));
    Action.Destination(AbsoluteFileName);

    TRights Rights = CopyParam->RemoteFileRights(Handle.Attrs);

    try
    {


      TFileBuffer AsciiBuf;
      bool ConvertToken = false;
      do
      {

        TFileBuffer BlockBuf;


        FILE_OPERATION_LOOP_BEGIN
        {
          BlockBuf.LoadStream(Stream.get(), OperationProgress->LocalBlockSize(), true);
        }
        FILE_OPERATION_LOOP_END_EX(
          FMTLOAD(READ_ERROR, (FileName)),
          FLAGMASK(!OperationProgress->TransferringFile, folAllowSkip));

        OperationProgress->AddLocallyUsed(BlockBuf.Size);


        if (OperationProgress->AsciiTransfer)
        {
          int ConvertParams =
            FLAGMASK(CopyParam->RemoveCtrlZ, cpRemoveCtrlZ) |
            FLAGMASK(CopyParam->RemoveBOM, cpRemoveBOM);
          BlockBuf.Convert(FTerminal->Configuration->LocalEOLType,
            FTerminal->SessionData->EOLType,
            ConvertParams, ConvertToken);
          BlockBuf.Memory->Seek(0, soFromBeginning);
          AsciiBuf.ReadStream(BlockBuf.Memory, BlockBuf.Size, true);

          BlockBuf.Memory->Clear();


          if (OperationProgress->LocallyUsed)
          {
            __int64 X = OperationProgress->LocalSize;
            X *= AsciiBuf.Size;
            X /= OperationProgress->LocallyUsed;
            OperationProgress->ChangeTransferSize(X);
          }
            else
          {
            OperationProgress->ChangeTransferSize(0);
          }
        }


        if (!OperationProgress->TransferringFile &&
            (!OperationProgress->AsciiTransfer || OperationProgress->IsLocallyDone()))
        {
          UnicodeString Buf;

          if (CopyParam->PreserveTime)
          {


            Buf.sprintf(L"T%lu 0 %lu 0", static_cast<unsigned long>(Handle.MTime),
              static_cast<unsigned long>(Handle.ATime));
            FSecureShell->SendLine(Buf);
            SCPResponse();
          }


          Buf.sprintf(L"C%s %Ld %s",
            Rights.Octal.data(),
            (OperationProgress->AsciiTransfer ? (__int64)AsciiBuf.Size :
              OperationProgress->LocalSize),
            DestFileName.data());
          FSecureShell->SendLine(Buf);
          SCPResponse();


          OperationProgress->SetTransferringFile(true);


          if (OperationProgress->AsciiTransfer)
          {
            FTerminal->LogEvent(FORMAT(L"Sending ASCII data (%u bytes)",
              (AsciiBuf.Size)));

            OperationProgress->ChangeTransferSize(AsciiBuf.Size);
            while (!OperationProgress->IsTransferDone())
            {
              unsigned long BlockSize = OperationProgress->TransferBlockSize();
              FSecureShell->Send(
                reinterpret_cast<unsigned char *>(AsciiBuf.Data + (unsigned int)OperationProgress->TransferredSize),
                BlockSize);
              OperationProgress->AddTransferred(BlockSize);
              if (OperationProgress->Cancel == csCancelTransfer)
              {
                throw Exception(MainInstructions(LoadStr(USER_TERMINATED)));
              }
            }
          }
        }


        if (!OperationProgress->AsciiTransfer)
        {
          if (!OperationProgress->TransferredSize)
          {
            FTerminal->LogEvent(FORMAT(L"Sending BINARY data (first block, %u bytes)",
              (BlockBuf.Size)));
          }
          else if (FTerminal->Configuration->ActualLogProtocol >= 1)
          {
            FTerminal->LogEvent(FORMAT(L"Sending BINARY data (%u bytes)",
              (BlockBuf.Size)));
          }
          FSecureShell->Send(reinterpret_cast<const unsigned char *>(BlockBuf.Data), BlockBuf.Size);
          OperationProgress->AddTransferred(BlockBuf.Size);
        }

        if ((OperationProgress->Cancel == csCancelTransfer) ||
            (OperationProgress->Cancel == csCancel && !OperationProgress->TransferringFile))
        {
          throw Exception(MainInstructions(LoadStr(USER_TERMINATED)));
        }
      }
      while (!OperationProgress->IsLocallyDone() || !OperationProgress->IsTransferDone());

      FSecureShell->SendNull();
      try
      {
        SCPResponse();


      }
      catch (EScp &E)
      {

        OperationProgress->SetTransferringFile(false);
        throw;
      }
      catch (EScpFileSkipped &E)
      {

        OperationProgress->SetTransferringFile(false);
        throw;
      }


      OperationProgress->SetTransferringFile(false);
    }
    catch (Exception &E)
    {


      if (dynamic_cast<EScpFileSkipped *>(&E) != NULL)
      {
        Action.Rollback(&E);
      }
      else
      {
        FTerminal->RollbackAction(Action, OperationProgress, &E);
      }


      if (OperationProgress->TransferringFile)
      {
        FTerminal->FatalError(&E, FMTLOAD(COPY_FATAL, (FileName)));
      }
      else
      {
        throw;
      }
    }


    if (CopyParam->PreserveTime)
    {
      TTouchSessionAction(FTerminal->ActionLog, AbsoluteFileName, Handle.Modification);
    }
    if (CopyParam->PreserveRights)
    {
      TChmodSessionAction(FTerminal->ActionLog, AbsoluteFileName,
        Rights);
    }

    FTerminal->LogFileDone(OperationProgress, AbsoluteFileName);

  }

  Handle.Release();

  FTerminal->UpdateSource(Handle, CopyParam, Params);

  FTerminal->LogEvent(FORMAT(L"Copying \"%s\" to remote directory finished.", (FileName)));
}
