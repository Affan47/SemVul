Allocate3D(unsigned int width,unsigned int height,
                                  unsigned int depth, int numComps,
                                  int vtkType)
{
  this->Target=vtkgl::TEXTURE_3D;

  if(this->Context==0)
    {
    vtkErrorMacro("No context specified. Cannot create texture.");
    return false;
    }
  GLenum internalFormat = this->GetInternalFormat(vtkType, numComps,
                                                  false);


  GLenum format = this->GetFormat(vtkType, numComps,false);

  GLenum type = ::vtkGetType(vtkType);

  this->Format = format;
  this->Type = type;
  this->Components = numComps;
  this->Width = width;
  this->Height = height;
  this->Depth =depth;
  this->NumberOfDimensions=3;

  this->CreateTexture();
  this->Bind();
  vtkgl::TexImage3D(this->Target, 0, static_cast<GLint>(internalFormat),
                    static_cast<GLsizei>(width), static_cast<GLsizei>(height),
                    static_cast<GLsizei>(depth), 0, format, type,0);
  this->UnBind();
  return true;
}
