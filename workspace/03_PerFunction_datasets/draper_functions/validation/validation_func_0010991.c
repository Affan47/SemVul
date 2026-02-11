TranslateAction(vtkAbstractWidget *w)
{
  vtkLineWidget2 *self = reinterpret_cast<vtkLineWidget2*>(w);
  if ( self->WidgetRep->GetInteractionState() == vtkLineRepresentation::Outside )
    {
    return;
    }


  int state = self->WidgetRep->GetInteractionState();
  if ( state == vtkLineRepresentation::OnP1 )
    {
    reinterpret_cast<vtkLineRepresentation*>(self->WidgetRep)->
      SetInteractionState(vtkLineRepresentation::TranslatingP1);
    }
  else if ( state == vtkLineRepresentation::OnP2 )
    {
    reinterpret_cast<vtkLineRepresentation*>(self->WidgetRep)->
      SetInteractionState(vtkLineRepresentation::TranslatingP2);
    }
  else
    {
    reinterpret_cast<vtkLineRepresentation*>(self->WidgetRep)->
      SetInteractionState(vtkLineRepresentation::OnLine);
    }


  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];


  self->WidgetState = vtkLineWidget2::Active;
  self->GrabFocus(self->EventCallbackCommand);
  double eventPos[2];
  eventPos[0] = static_cast<double>(X);
  eventPos[1] = static_cast<double>(Y);
  reinterpret_cast<vtkLineRepresentation*>(self->WidgetRep)->
    StartWidgetInteraction(eventPos);
  self->InvokeEvent(vtkCommand::LeftButtonPressEvent,NULL);
  self->EventCallbackCommand->SetAbortFlag(1);
  self->StartInteraction();
  self->InvokeEvent(vtkCommand::StartInteractionEvent,NULL);
}
