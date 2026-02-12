void __fastcall TSCPFileSystem::SCPSendError(const UnicodeString Message, bool Fatal)
{
  unsigned char ErrorLevel = (char)(Fatal ? 2 : 1);
  FTerminal->LogEvent(FORMAT(L"Sending SCP error (%d) to remote side:",
    ((int)ErrorLevel)));
  FSecureShell->Send(&ErrorLevel, 1);


  FSecureShell->SendLine(L"scp: error");
}
