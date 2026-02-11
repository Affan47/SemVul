Render(vtkRenderer *ren, vtkVolume *vol)
{
  ren->GetRenderWindow()->MakeCurrent();

  if ( !this->Initialized )
    {
    this->Initialize(ren);
    }

  if ( this->RenderMethod == vtkVolumeTextureMapper3D::NO_METHOD )
    {
    vtkErrorMacro( "required extensions not supported" );
    return;
    }


  vtkMatrix4x4       *matrix;
  double             matrixForGL[16];
  int                numClipPlanes = 0;
  double             planeEquation[4];


  matrix = vol->GetMatrix();
  vtkMatrix4x4::Transpose(*matrix->Element, matrixForGL);

  glPushAttrib(GL_ENABLE_BIT   |
               GL_COLOR_BUFFER_BIT   |
               GL_STENCIL_BUFFER_BIT |
               GL_DEPTH_BUFFER_BIT   |
               GL_POLYGON_BIT        |
               GL_TEXTURE_BIT);

  int i;


  glMatrixMode( GL_MODELVIEW );
  glPushMatrix();
  glMultMatrixd(matrixForGL);


  numClipPlanes = this->GetNumberOfClippingPlanes();
  if (numClipPlanes > 6)
    {
    vtkErrorMacro(<< "OpenGL has a limit of 6 clipping planes");
    numClipPlanes = 6;
    }

  for (i = 0; i < numClipPlanes; i++)
    {
    glEnable(static_cast<GLenum>(GL_CLIP_PLANE0+i));
    this->GetClippingPlaneInDataCoords(matrix, i, planeEquation);
    glClipPlane(static_cast<GLenum>(GL_CLIP_PLANE0+i), planeEquation);
    }


  glDisable (GL_CULL_FACE);

  glColor4f( 1.0, 1.0, 1.0, 1.0 );


  glDisable( GL_LIGHTING );

  if(this->UseCompressedTexture && SupportsCompressedTexture)
    {
    this->InternalAlpha=vtkgl::COMPRESSED_ALPHA;
    this->InternalLA=vtkgl::COMPRESSED_LUMINANCE_ALPHA;
    this->InternalRGB=vtkgl::COMPRESSED_RGB;
    this->InternalRGBA=vtkgl::COMPRESSED_RGBA;
    }
  else
    {
    this->InternalAlpha=GL_ALPHA8;
    this->InternalLA=GL_LUMINANCE8_ALPHA8;
    this->InternalRGB=GL_RGB8;
    this->InternalRGBA=GL_RGBA8;
    }

  vtkGraphicErrorMacro(ren->GetRenderWindow(),"Before actual render method");
  switch ( this->RenderMethod )
    {
    case vtkVolumeTextureMapper3D::NVIDIA_METHOD:
      this->RenderNV(ren,vol);
      break;
    case vtkVolumeTextureMapper3D::FRAGMENT_PROGRAM_METHOD:
      this->RenderFP(ren,vol);
      break;
    }


  glMatrixMode( GL_MODELVIEW );
  glPopMatrix();

  glPopAttrib();


  glFlush();
  glFinish();


  this->Timer->StopTimer();

  this->TimeToDraw = static_cast<float>(this->Timer->GetElapsedTime());


  if ( this->TimeToDraw == 0.0 )
    {
    this->TimeToDraw = 0.0001;
    }
}
