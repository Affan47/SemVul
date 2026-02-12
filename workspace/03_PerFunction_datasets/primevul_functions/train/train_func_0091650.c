void __fastcall TSCPFileSystem::Idle()
{

  if ((FTerminal->SessionData->PingType != ptOff) &&
      (Now() - FSecureShell->LastDataSent > FTerminal->SessionData->PingIntervalDT))
  {
    if ((FTerminal->SessionData->PingType == ptDummyCommand) &&
        FSecureShell->Ready)
    {
      if (!FProcessingCommand)
      {
        ExecCommand(fsNull, NULL, 0, 0);
      }
      else
      {
        FTerminal->LogEvent(L"Cannot send keepalive, command is being executed");


        FSecureShell->KeepAlive();
      }
    }
    else
    {
      FSecureShell->KeepAlive();
    }
  }

  FSecureShell->Idle();
}
