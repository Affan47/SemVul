BoundarySeparator(vtkPolyData* appendedBoundaries, vtkPolyDataCollection* boundaries)
{
  appendedBoundaries->BuildLinks();
  appendedBoundaries->Update();

  vtkIdType i;
  for (i=0; i<appendedBoundaries->GetNumberOfCells(); i++)
    {
    vtkPoints* boundaryPoints = vtkPoints::New();
    vtkCellArray* boundaryCellArray = vtkCellArray::New();
    vtkIdType npts, *pts;
    appendedBoundaries->GetCellPoints(i,npts,pts);
    boundaryCellArray->InsertNextCell(npts+1);
    vtkIdType j;
    for (j=0; j<npts; j++)
      {
      boundaryPoints->InsertNextPoint(appendedBoundaries->GetPoint(pts[j]));
      boundaryCellArray->InsertCellPoint(j);
      }
    boundaryCellArray->InsertCellPoint(0);
    vtkPolyData* boundary = vtkPolyData::New();
    boundary->SetPoints(boundaryPoints);
    boundary->SetLines(boundaryCellArray);
    boundary->Update();
    boundaries->AddItem(boundary);
    boundary->Delete();
    boundaryPoints->Delete();
    boundaryCellArray->Delete();
    }
}
