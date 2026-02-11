GetMaterial(const char* name)
{
  if (!name || !*name)
    {
    return 0;
    }


  vtkMaterialLibraryMacro(name)
  return 0;
}
