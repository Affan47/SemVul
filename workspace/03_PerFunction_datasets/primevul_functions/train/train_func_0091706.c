void __fastcall TSCPFileSystem::SCPResponse(bool * GotLastLine)
{


  unsigned char Resp;
  FSecureShell->Receive(&Resp, 1);

  switch (Resp)
  {
    case 0:
      FTerminal->LogEvent(L"SCP remote side confirmation (0)");
      return;

    default:
    case 1:
    case 2:

      UnicodeString Msg = FSecureShell->ReceiveLine();
      UnicodeString Line = UnicodeString(static_cast<char>(Resp)) + Msg;
      if (IsLastLine(Line))
      {
        if (GotLastLine != NULL)
        {
          *GotLastLine = true;
        }


        FSecureShell->ClearStdError();

        try
        {
          ReadCommandOutput(coExpectNoOutput | coRaiseExcept | coOnlyReturnCode);
        }
        catch(...)
        {

          if (GotLastLine != NULL)
          {
            *GotLastLine = true;
          }
          throw;
        }
      }
      else if (Resp == 1)
      {


        if (SameText(Msg, L"scp: ambiguous target") ||
            StartsText(L"scp: error: unexpected filename: ", Msg) ||
            StartsText(L"scp: protocol error: ", Msg))
        {
          FTerminal->LogEvent(L"SCP remote side error (1), fatal error detected from error message");
          Resp = 2;
          FScpFatalError = true;
        }
        else
        {
          FTerminal->LogEvent(L"SCP remote side error (1)");
        }
      }
      else
      {
        FTerminal->LogEvent(L"SCP remote side fatal error (2)");
        FScpFatalError = true;
      }

      if (Resp == 1)
      {
        throw EScpFileSkipped(NULL, Msg);
      }
      else
      {
        throw EScp(NULL, Msg);
      }
  }
}
