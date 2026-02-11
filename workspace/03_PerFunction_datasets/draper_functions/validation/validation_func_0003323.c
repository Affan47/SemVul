RenderOverlay(vtkViewport *viewport)
{

  if (this->Texture && this->Input)
    {
    vtkRenderer* ren = vtkRenderer::SafeDownCast(viewport);
    if (ren)
      {
      this->Texture->Render(ren);
      }
    }


  return this->vtkActor2D::RenderOverlay(viewport);
}
