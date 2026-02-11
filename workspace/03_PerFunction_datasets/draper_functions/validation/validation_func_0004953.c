FindPokedRenderer(int x,int y)
{
  vtkRendererCollection *rc;
  vtkRenderer *aren;
  vtkRenderer *currentRenderer=NULL, *interactiveren=NULL, *viewportren=NULL;
  int numRens, i;

  rc = this->RenderWindow->GetRenderers();
  numRens = rc->GetNumberOfItems();

  for (i = numRens -1; (i >= 0) && !currentRenderer; i--)
    {
    aren = static_cast<vtkRenderer *>(rc->GetItemAsObject(i));
    if (aren->IsInViewport(x,y) && aren->GetInteractive())
      {
      currentRenderer = aren;
      }

    if (interactiveren == NULL && aren->GetInteractive())
      {


      interactiveren = aren;
      }
    if (viewportren == NULL && aren->IsInViewport(x, y))
      {


      viewportren = aren;
      }
    }


  if ( currentRenderer == NULL )
    {
    currentRenderer = interactiveren;
    }


  if ( currentRenderer == NULL )
    {
    currentRenderer = viewportren;
    }


  if ( currentRenderer == NULL)
    {
    aren = rc->GetFirstRenderer();
    currentRenderer = aren;
    }

  return currentRenderer;
}
