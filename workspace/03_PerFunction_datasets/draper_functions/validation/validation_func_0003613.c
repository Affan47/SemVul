create(const char *fileName_, const char *application_, const char *type_, bool isXml_)
{
  fileName=string(fileName_);
  application=string(application_);
  type=string(type_);
  isXml=isXml_;
  if(xmlForced){isXml=true;}
}
