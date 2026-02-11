CloseEventHandler( wxCloseEvent &WXUNUSED(event) )
{
  wxConfigBase *config = wxConfigBase::Get();
  if( config )
  {
    int width, height;
    GetSize( &width, &height );
    config->Write( wxT("/BasicColors/WIDTH"), static_cast<long>(width) );
    config->Write( wxT("/BasicColors/HEIGHT"), static_cast<long>(height) );
  }


  Destroy();
}
