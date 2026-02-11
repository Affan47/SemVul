ShallowCopy(vtkProp *prop)
{
  vtkAxesActor *a = vtkAxesActor::SafeDownCast(prop);
  if ( a != NULL )
    {
    this->SetAxisLabels( a->GetAxisLabels() );
    this->SetXAxisLabelText( a->GetXAxisLabelText() );
    this->SetYAxisLabelText( a->GetYAxisLabelText() );
    this->SetZAxisLabelText( a->GetZAxisLabelText() );
    this->SetTotalLength( a->GetTotalLength() );
    this->SetNormalizedShaftLength( a->GetNormalizedShaftLength() );
    this->SetNormalizedTipLength( a->GetNormalizedTipLength() );
    this->SetNormalizedLabelPosition( a->GetNormalizedLabelPosition() );
    this->SetConeResolution( a->GetConeResolution() );
    this->SetSphereResolution( a->GetSphereResolution() );
    this->SetCylinderResolution( a->GetCylinderResolution() );
    this->SetConeRadius( a->GetConeRadius() );
    this->SetSphereRadius( a->GetSphereRadius() );
    this->SetCylinderRadius( a->GetCylinderRadius() );
    this->SetTipType( a->GetTipType() );
    this->SetShaftType( a->GetShaftType() );
    this->SetUserDefinedTip( a->GetUserDefinedTip() );
    this->SetUserDefinedShaft( a->GetUserDefinedShaft() );
    }


  this->vtkProp3D::ShallowCopy(prop);
}
