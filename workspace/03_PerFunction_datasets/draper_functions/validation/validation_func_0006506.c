WindowLevel()
{
  vtkRenderWindowInteractor *rwi = this->Interactor;

  this->WindowLevelCurrentPosition[0] = rwi->GetEventPosition()[0];
  this->WindowLevelCurrentPosition[1] = rwi->GetEventPosition()[1];

  if (this->CurrentImageProperty)
    {
    int *size = this->CurrentRenderer->GetSize();

    double window = this->WindowLevelInitial[0];
    double level = this->WindowLevelInitial[1];


    double dx = (this->WindowLevelCurrentPosition[0] -
                 this->WindowLevelStartPosition[0]) * 4.0 / size[0];
    double dy = (this->WindowLevelStartPosition[1] -
                 this->WindowLevelCurrentPosition[1]) * 4.0 / size[1];


    if ( fabs( window ) > 0.01 )
      {
      dx = dx * window;
      }
    else
      {
      dx = dx * ( window < 0 ? -0.01 : 0.01 );
      }
    if ( fabs( level ) > 0.01 )
      {
      dy = dy * level;
      }
    else
      {
      dy = dy * ( level < 0 ? -0.01 : 0.01 );
      }


    if ( window < 0.0 )
      {
      dx = -1 * dx;
      }
    if ( level < 0.0 )
      {
      dy = -1 * dy;
      }


    double newWindow = dx + window;
    double newLevel = level - dy;

    if ( newWindow < 0.01 )
      {
      newWindow = 0.01;
      }

    this->CurrentImageProperty->SetColorWindow(newWindow);
    this->CurrentImageProperty->SetColorLevel(newLevel);

    this->Interactor->Render();
    }
  else
    {
    this->InvokeEvent(vtkCommand::WindowLevelEvent, this);
    }
}
