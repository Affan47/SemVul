void __fastcall TSCPFileSystem::SendCommand(const UnicodeString Cmd)
{
  EnsureLocation();

  UnicodeString Line;
  FSecureShell->ClearStdError();
  FReturnCode = 0;
  FOutput->Clear();


  FSecureShell->SendLine(Cmd);
  FProcessingCommand = true;
}
