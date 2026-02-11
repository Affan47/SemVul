DisplayStatus(const char* message, float s)
{
  cmake* cm = this->GetLocalGenerator()->GetGlobalGenerator()
                                                          ->GetCMakeInstance();
  if (cm->GetWorkingMode() == cmake::FIND_PACKAGE_MODE)
    {


    return;
    }
  cm->UpdateProgress(message, s);
}
