GetScalarRange(double range[2])
{
  vtkDataArray *ptScalars = this->PointData->GetScalars();
  vtkDataArray *cellScalars = this->CellData->GetScalars();
  double ptRange[2];
  double cellRange[2];
  double s;
  int id, num;

  ptRange[0] =  VTK_DOUBLE_MAX;
  ptRange[1] =  VTK_DOUBLE_MIN;
  if ( ptScalars )
    {
    num = this->GetNumberOfPoints();
    for (id=0; id < num; id++)
      {
      if ( this->IsPointVisible(id) )
        {
        s = ptScalars->GetComponent(id,0);
        if ( s < ptRange[0] )
          {
          ptRange[0] = s;
          }
        if ( s > ptRange[1] )
          {
          ptRange[1] = s;
          }
        }
      }
    }

  cellRange[0] =  ptRange[0];
  cellRange[1] =  ptRange[1];
  if ( cellScalars )
    {
    num = this->GetNumberOfCells();
    for (id=0; id < num; id++)
      {
      if ( this->IsCellVisible(id) )
        {
        s = cellScalars->GetComponent(id,0);
        if ( s < cellRange[0] )
          {
          cellRange[0] = s;
          }
        if ( s > cellRange[1] )
          {
          cellRange[1] = s;
          }
        }
      }
    }

  range[0] = (cellRange[0] >= VTK_DOUBLE_MAX ? 0.0 : cellRange[0]);
  range[1] = (cellRange[1] <= VTK_DOUBLE_MIN ? 1.0 : cellRange[1]);

  this->ComputeTime.Modified();
}
