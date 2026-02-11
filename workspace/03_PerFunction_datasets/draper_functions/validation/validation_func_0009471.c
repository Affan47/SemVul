Triangulate(int vtkNotUsed(index), vtkIdList *ptIds,
                             vtkPoints *pts)
{
  pts->Reset();
  ptIds->Reset();

  for ( int i=0; i < 3; i++ )
    {
    ptIds->InsertId(i,this->PointIds->GetId(i));
    pts->InsertPoint(i,this->Points->GetPoint(i));
    }

  return 1;
}
