RenderOpaqueGeometry(vtkViewport *vp)
{
  int renderedSomething = 0;

  this->UpdateProps();

  renderedSomething += this->XAxisShaft->RenderOpaqueGeometry( vp );
  renderedSomething += this->YAxisShaft->RenderOpaqueGeometry( vp );
  renderedSomething += this->ZAxisShaft->RenderOpaqueGeometry( vp );

  renderedSomething += this->XAxisTip->RenderOpaqueGeometry( vp );
  renderedSomething += this->YAxisTip->RenderOpaqueGeometry( vp );
  renderedSomething += this->ZAxisTip->RenderOpaqueGeometry( vp );

  if ( this->AxisLabels )
    {
    renderedSomething += this->XAxisLabel->RenderOpaqueGeometry( vp );
    renderedSomething += this->YAxisLabel->RenderOpaqueGeometry( vp );
    renderedSomething += this->ZAxisLabel->RenderOpaqueGeometry( vp );
    }

  renderedSomething = (renderedSomething > 0)?(1):(0);
  return renderedSomething;
}
