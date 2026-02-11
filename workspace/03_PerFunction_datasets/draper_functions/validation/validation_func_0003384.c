Update()
{
  if (this->BuildTime > this->MTime)
    {
    return;
    }

  vtkDebugMacro("Update");

  if (this->ExtensionsString)
    {
    delete[] this->ExtensionsString;
    this->ExtensionsString = NULL;
    }

  this->ReadOpenGLExtensions();

  this->BuildTime.Modified();
}
