MoveAction(vtkAbstractWidget *w)
{
  vtkLineWidget2 *self = reinterpret_cast<vtkLineWidget2*>(w);

  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  if ( self->WidgetState == vtkLineWidget2::Start )
    {
    self->Interactor->Disable();
    self->Point1Widget->SetEnabled(0);
    self->Point2Widget->SetEnabled(0);
    self->LineHandle->SetEnabled(0);

    int oldState = self->WidgetRep->GetInteractionState();
    int state = self->WidgetRep->ComputeInteractionState(X,Y);
    int changed;

    if ( state == vtkLineRepresentation::Outside )
      {
      changed = self->RequestCursorShape(VTK_CURSOR_DEFAULT);
      }
    else
      {
      changed = self->RequestCursorShape(VTK_CURSOR_HAND);
      if ( state == vtkLineRepresentation::OnP1 )
        {
        self->Point1Widget->SetEnabled(1);
        }
      else if ( state == vtkLineRepresentation::OnP2 )
        {
        self->Point2Widget->SetEnabled(1);
        }
      else
        {
        self->LineHandle->SetEnabled(1);
        changed = 1;
        }
      }
    self->Interactor->Enable();
    if ( changed || oldState != state )
      {
      self->Render();
      }
    }
  else
    {

    double e[2];
    e[0] = static_cast<double>(X);
    e[1] = static_cast<double>(Y);
    self->InvokeEvent(vtkCommand::MouseMoveEvent,NULL);
    reinterpret_cast<vtkLineRepresentation*>(self->WidgetRep)->
      WidgetInteraction(e);
    self->InvokeEvent(vtkCommand::InteractionEvent,NULL);
    self->EventCallbackCommand->SetAbortFlag(1);
    self->Render();
    }
}
