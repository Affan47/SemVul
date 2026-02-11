OnRightButtonUp()
{
  if ( this->State == vtkSphereWidget::Outside )
    {
    return;
    }

  this->State = vtkSphereWidget::Start;
  this->HighlightSphere(0);
  this->HighlightHandle(0);
  this->SizeHandles();

  this->EventCallbackCommand->SetAbortFlag(1);
  this->EndInteraction();
  this->InvokeEvent(vtkCommand::EndInteractionEvent,NULL);
  if (this->Interactor)
    {
    this->Interactor->Render();
    }
}
