RenderOpaqueGeometry(vtkViewport* viewport)
{
  vtkDebugMacro(<< "vtkImageStack::RenderOpaqueGeometry");


  this->Images->Sort();
  this->UpdatePaths();

  if (!this->IsIdentity)
    {
    this->PokeMatrices(this->GetMatrix());
    }

  int rendered = 0;
  vtkImageSlice *image = 0;
  vtkCollectionSimpleIterator pit;
  vtkIdType n = 0;
  this->Images->InitTraversal(pit);
  while ( (image = this->Images->GetNextImage(pit)) != 0)
    {
    n += (image->GetVisibility() != 0);
    }
  double renderTime = this->AllocatedRenderTime/(n + (n == 0));

  if (n == 1)
    {

    this->Images->InitTraversal(pit);
    while ( (image = this->Images->GetNextImage(pit)) != 0)
      {
      if (image->GetVisibility())
        {
        image->SetAllocatedRenderTime(renderTime, viewport);
        rendered = image->RenderOpaqueGeometry(viewport);
        }
      }
    }
  else
    {
    for (int pass = 0; pass < 3; pass++)
      {
      this->Images->InitTraversal(pit);
      while ( (image = this->Images->GetNextImage(pit)) != 0)
        {
        if (image->GetVisibility())
          {
          image->SetAllocatedRenderTime(renderTime, viewport);
          image->SetStackedImagePass(pass);
          rendered |= image->RenderOpaqueGeometry(viewport);
          image->SetStackedImagePass(-1);
          }
        }
      }
    }

  if (!this->IsIdentity)
    {
    this->PokeMatrices(NULL);
    }

  return rendered;
}
