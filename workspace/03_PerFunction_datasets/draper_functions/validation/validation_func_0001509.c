SetMaterialArrays( int M, const char* volume, const char* normal, const char* ordering )
{
  this->NumberOfDomains = -1;
  if( M<0 )
    {
    vtkErrorMacro(<<"Bad material index "<<M<<"\n");
    return;
    }
  else if( M>=this->GetNumberOfMaterials() )
    {
    this->SetNumberOfMaterials(M+1);
    }
  vtkDebugMacro(<<"Set Material "<<M<<" : "<<volume<<","<<normal<<","<<ordering<<"\n");
  vtkYoungsMaterialInterfaceInternals::MaterialDescription md;
  md.setVolume(volume);
  md.setNormal(normal);
  md.setNormalX("");
  md.setNormalY("");
  md.setNormalZ("");
  md.setOrdering(ordering);
  this->Internals->Materials[M] = md;
  this->Modified();
}
