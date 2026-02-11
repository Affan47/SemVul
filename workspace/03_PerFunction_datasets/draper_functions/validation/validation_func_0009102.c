FindCellsWithinBounds(double *bbox, vtkIdList *cells)
{
  this->BuildLocatorIfNeeded();

  cells->Reset();


  double p1[3], p2[3], *p[2];
  p1[0] = bbox[0];
  p1[1] = bbox[2];
  p1[2] = bbox[4];
  p2[0] = bbox[1];
  p2[1] = bbox[3];
  p2[2] = bbox[5];
  p[0] = p1;
  p[1] = p2;
  int ijk[2][3];


  int i, j, k;
  for (i=0; i<2; i++)
    {
    for (j=0; j<3; j++)
      {
      ijk[i][j] = static_cast<int>((p[i][j] - this->Bounds[2*j]) / this->H[j]);

      if (ijk[i][j] < 0)
        {
        ijk[i][j] = 0;
        }
      else if (ijk[i][j] >= this->NumberOfDivisions)
        {
        ijk[i][j] = this->NumberOfDivisions-1;
        }
      }
    }


  int leafStart = this->NumberOfOctants
    - this->NumberOfDivisions*this->NumberOfDivisions*this->NumberOfDivisions;
  vtkIdList *cellIds;
  vtkIdType idx;
  for (k=ijk[0][2]; k <= ijk[1][2]; k++)
    {
    for (j=ijk[0][1]; j <= ijk[1][1]; j++)
      {
      for (i=ijk[0][0]; i <= ijk[1][0]; i++)
        {
        if ( (cellIds = this->Tree[leafStart + i + j*this->NumberOfDivisions +
                                  k*this->NumberOfDivisions*this->NumberOfDivisions]) != NULL )
          {
          for ( idx=0; idx < cellIds->GetNumberOfIds(); idx++)
            {
            cells->InsertUniqueId( cellIds->GetId(idx) );
            }
          }
        }
      }
    }
}
