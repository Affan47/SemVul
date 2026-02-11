SelectAction(vtkAbstractWidget *w)
{
  vtkHandleWidget *self = reinterpret_cast<vtkHandleWidget*>(w);

  int X = self->Interactor->GetEventPosition()[0];
  int Y = self->Interactor->GetEventPosition()[1];

  self->WidgetRep->ComputeInteractionState(X, Y);
  if ( self->WidgetRep->GetInteractionState() == vtkHandleRepresentation::Outside )
    {
    return;
    }


  if ( ! self->Parent )
    {
    self->GrabFocus(self->EventCallbackCommand);
    }
  double eventPos[2];
  eventPos[0] = static_cast<double>(X);
  eventPos[1] = static_cast<double>(Y);
  self->WidgetRep->StartWidgetInteraction(eventPos);

  self->WidgetState = vtkHandleWidget::Active;
  reinterpret_cast<vtkHandleRepresentation*>(self->WidgetRep)->
    SetInteractionState(vtkHandleRepresentation::Selecting);

  self->GenericAction(self);
}
