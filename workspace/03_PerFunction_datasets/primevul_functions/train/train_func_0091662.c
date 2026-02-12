void __fastcall TSCPFileSystem::SCPDirectorySource(const UnicodeString DirectoryName,
  const UnicodeString TargetDir, const TCopyParamType * CopyParam, int Params,
  TFileOperationProgressType * OperationProgress, int Level)
{
  int Attrs;

  FTerminal->LogEvent(FORMAT(L"Entering directory \"%s\".", (DirectoryName)));

  OperationProgress->SetFile(DirectoryName);
  UnicodeString DestFileName =
    FTerminal->ChangeFileName(
      CopyParam, ExtractFileName(DirectoryName), osLocal, Level == 0);


  FILE_OPERATION_LOOP_BEGIN
  {
    Attrs = FileGetAttrFix(ApiPath(DirectoryName));
    if (Attrs < 0) RaiseLastOSError();
  }
  FILE_OPERATION_LOOP_END(FMTLOAD(CANT_GET_ATTRS, (DirectoryName)));

  UnicodeString TargetDirFull = UnixIncludeTrailingBackslash(TargetDir + DestFileName);

  UnicodeString Buf;


  Buf = FORMAT(L"D%s 0 %s",
    (CopyParam->RemoteFileRights(Attrs).Octal, DestFileName));
  FSecureShell->SendLine(Buf);
  SCPResponse();

  try
  {
    TSearchRecOwned SearchRec;
    bool FindOK = FTerminal->LocalFindFirstLoop(IncludeTrailingBackslash(DirectoryName) + L"*.*", SearchRec);

    while (FindOK && !OperationProgress->Cancel)
    {
      UnicodeString FileName = IncludeTrailingBackslash(DirectoryName) + SearchRec.Name;
      try
      {
        if (SearchRec.IsRealFile())
        {
          SCPSource(FileName, TargetDirFull, CopyParam, Params, OperationProgress, Level + 1);
        }
      }


      catch (EScpFileSkipped &E)
      {
        TQueryParams Params(qpAllowContinueOnError);
        TSuspendFileOperationProgress Suspend(OperationProgress);

        if (FTerminal->QueryUserException(FMTLOAD(COPY_ERROR, (FileName)), &E,
              qaOK | qaAbort, &Params, qtError) == qaAbort)
        {
          OperationProgress->SetCancel(csCancel);
        }
        if (!FTerminal->HandleException(&E))
        {
          throw;
        }
      }
      catch (ESkipFile &E)
      {

        TSuspendFileOperationProgress Suspend(OperationProgress);
        if (!FTerminal->HandleException(&E))
        {
          throw;
        }
      }

      FindOK = FTerminal->LocalFindNextLoop(SearchRec);
    }

    SearchRec.Close();


    if (!OperationProgress->Cancel)
    {
      if (FLAGSET(Params, cpDelete))
      {
        RemoveDir(ApiPath(DirectoryName));
      }
      else if (CopyParam->ClearArchive && FLAGSET(Attrs, faArchive))
      {
        FILE_OPERATION_LOOP_BEGIN
        {
          THROWOSIFFALSE(FileSetAttr(ApiPath(DirectoryName), Attrs & ~faArchive) == 0);
        }
        FILE_OPERATION_LOOP_END(FMTLOAD(CANT_SET_ATTRS, (DirectoryName)));
      }
    }
  }
  __finally
  {
    if (FTerminal->Active)
    {

      FTerminal->LogEvent(FORMAT(L"Leaving directory \"%s\".", (DirectoryName)));
      FSecureShell->SendLine(L"E");
      SCPResponse();
    }
  }
}
