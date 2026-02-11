ComputeInteractionState(int X, int Y, int vtkNotUsed(modify))
{
  double pos[3], xyz[3];
  this->FocalPoint->GetPoint(0,pos);
  xyz[0] = static_cast<double>(X);
  xyz[1] = static_cast<double>(Y);
  xyz[2] = pos[2];

  this->VisibilityOn();
  double tol2 = this->Tolerance * this->Tolerance;
  if ( vtkMath::Distance2BetweenPoints(xyz,pos) <= tol2 )
    {
    this->InteractionState = vtkHandleRepresentation::Nearby;
    }
  else
    {
    this->InteractionState = vtkHandleRepresentation::Outside;
    if ( this->ActiveRepresentation )
      {
      this->VisibilityOff();
      }
    }

  return this->InteractionState;
}
