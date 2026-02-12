void __fastcall TSCPFileSystem::CopyToLocal(TStrings * FilesToCopy,
  const UnicodeString TargetDir, const TCopyParamType * CopyParam,
  int Params, TFileOperationProgressType * OperationProgress,
  TOnceDoneOperation & OnceDoneOperation)
{
  bool CloseSCP = False;
  Params &= ~(cpAppend | cpResume);
  UnicodeString Options = L"";
  if (CopyParam->PreserveRights || CopyParam->PreserveTime) Options = L"-p";
  if (FTerminal->SessionData->Scp1Compatibility) Options += L" -1";

  FTerminal->LogEvent(FORMAT(L"Copying %d files/directories to local directory "
    "\"%s\"", (FilesToCopy->Count, TargetDir)));
  if (FTerminal->Configuration->ActualLogProtocol >= 0)
  {
    FTerminal->LogEvent(CopyParam->LogStr);
  }

  try
  {
    for (int IFile = 0; (IFile < FilesToCopy->Count) &&
      !OperationProgress->Cancel; IFile++)
    {
      UnicodeString FileName = FilesToCopy->Strings[IFile];
      TRemoteFile * File = (TRemoteFile *)FilesToCopy->Objects[IFile];
      DebugAssert(File);

      try
      {
        bool Success = true;
        SendCommand(FCommandSet->FullCommand(fsCopyToLocal,
          ARRAYOFCONST((Options, DelimitStr(FileName)))));
        SkipFirstLine();


        UnicodeString FullFileName = UnixExcludeTrailingBackslash(File->FullFileName);
        SCPSink(TargetDir, FullFileName, UnixExtractFilePath(FullFileName),
          CopyParam, Success, OperationProgress, Params, 0);


        if (OperationProgress->Cancel == csRemoteAbort)
        {
          OperationProgress->SetCancel(csContinue);
        }


        if ((Params & cpDelete) && Success && !OperationProgress->Cancel)
        {
          try
          {
            FTerminal->ExceptionOnFail = true;
            try
            {
              FILE_OPERATION_LOOP_BEGIN
              {


                FTerminal->DeleteFile(FileName, File);
              }
              FILE_OPERATION_LOOP_END(FMTLOAD(DELETE_FILE_ERROR, (FileName)));
            }
            __finally
            {
              FTerminal->ExceptionOnFail = false;
            }
          }
          catch (EFatal &E)
          {
            throw;
          }
          catch (...)
          {


            if (OperationProgress->Cancel == csCancel)
            {
              OperationProgress->SetCancel(csRemoteAbort);
            }
            Success = false;
          }
        }

        FTerminal->OperationFinish(
          OperationProgress, File, FileName, (!OperationProgress->Cancel && Success), OnceDoneOperation);
      }
      catch (...)
      {
        FTerminal->OperationFinish(OperationProgress, File, FileName, false, OnceDoneOperation);
        CloseSCP = (OperationProgress->Cancel != csRemoteAbort);
        throw;
      }
    }
  }
  __finally
  {


    if (FTerminal->Active && (CloseSCP ||
        (OperationProgress->Cancel == csCancel) ||
        (OperationProgress->Cancel == csCancelTransfer)))
    {
      bool LastLineRead;


      UnicodeString Line = FSecureShell->ReceiveLine();
      LastLineRead = IsLastLine(Line);
      if (!LastLineRead)
      {
        SCPSendError((OperationProgress->Cancel ? L"Terminated by user." : L"Exception"), true);
      }


      int ECParams = coOnlyReturnCode;
      if (!LastLineRead) ECParams |= coWaitForLastLine;
      ReadCommandOutput(ECParams);
    }
  }
}
