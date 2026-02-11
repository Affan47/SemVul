SetConfigName()
{

  if(const char* config =
       this->GetMakefile()->GetDefinition("CMAKE_BUILD_TYPE"))
    {

    this->ConfigName = config;
    }
  else
    {

    this->ConfigName = "";
    }
}
