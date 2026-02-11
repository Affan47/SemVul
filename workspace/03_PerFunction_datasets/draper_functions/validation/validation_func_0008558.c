InitialCheckout(
  std::ostream& ofs, std::string const& sourceDir)
{

  const char* initialCheckoutCommand
    = this->Makefile->GetDefinition("CTEST_CHECKOUT_COMMAND");
  if(!initialCheckoutCommand)
    {
    initialCheckoutCommand =
      this->Makefile->GetDefinition("CTEST_CVS_CHECKOUT");
    }
  if(initialCheckoutCommand)
    {

    cmCTestVC vc(this->CTest, ofs);
    vc.SetSourceDirectory(sourceDir.c_str());
    if(!vc.InitialCheckout(initialCheckoutCommand))
      {
      return false;
      }
    }
  return true;
}
