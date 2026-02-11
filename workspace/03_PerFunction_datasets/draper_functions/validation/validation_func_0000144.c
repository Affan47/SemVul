InsertPoint(vtkIdType vtkNotUsed(ptId),
                                                     double pt[3],
                                                     double pcoords[3],
                                                     int ijk[3])
{
  if(this->Locator->InsertUniquePoint(pcoords,this->LastPtId))
    {
    double value=this->Filter->ComputePointValue(ijk);
    this->Filter->PointScalars->InsertValue(this->LastPtId,value);
    }
  this->Triangulator->InsertPoint(this->LastPtId,pt,pcoords,0);
}
