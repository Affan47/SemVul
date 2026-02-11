OnLeftButtonDown()
{
  if (!this->Interactor)
    {
    return;
    }

  int X = this->Interactor->GetEventPosition()[0];
  int Y = this->Interactor->GetEventPosition()[1];


  if (!this->CurrentRenderer || !this->CurrentRenderer->IsInViewport(X, Y))
    {
    this->State = vtkSphereWidget::Outside;
    return;
    }


  vtkAssemblyPath *path;
  this->Picker->Pick(X,Y,0.0,this->CurrentRenderer);
  path = this->Picker->GetPath();
  if ( path == NULL )
    {
    this->State = vtkSphereWidget::Outside;
    return;
    }
  else if (path->GetFirstNode()->GetViewProp() == this->SphereActor )
    {
    this->State = vtkSphereWidget::Moving;
    this->HighlightSphere(1);
    }
  else if (path->GetFirstNode()->GetViewProp() == this->HandleActor )
    {
    this->State = vtkSphereWidget::Positioning;
    this->HighlightHandle(1);
    }

  this->EventCallbackCommand->SetAbortFlag(1);
  this->StartInteraction();
  this->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
  this->Interactor->Render();
}
