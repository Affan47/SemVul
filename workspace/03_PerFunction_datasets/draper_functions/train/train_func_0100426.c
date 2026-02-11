WriteGeometryFile(FILE *geomFile, int numPts)
{
  int numPolys, numEdges;
  int i;
  double *x;
  vtkIdType npts = 0;
  vtkIdType *pts = 0;
  vtkPoints *inPts;
  vtkCellArray *inPolys;
  vtkPolyData *input= this->GetInput();


  inPolys=input->GetPolys();
  if ( (inPts=input->GetPoints()) == NULL || inPolys == NULL )
    {
    vtkErrorMacro(<<"No data to write!");
    return;
    }


  numPolys = input->GetPolys()->GetNumberOfCells();
  for (numEdges=0, inPolys->InitTraversal(); inPolys->GetNextCell(npts,pts); )
    {
    numEdges += npts;
    }

  if (fprintf (geomFile, "%d %d %d %d\n", 1, numPts, numPolys, numEdges) < 0)
    {
    this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
    return;
    }
  if (fprintf (geomFile, "%d %d\n", 1, numPolys) < 0)
    {
    this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
    return;
    }


  for (i=0; i < numPts; i++)
    {
    x = inPts->GetPoint(i);
    if (fprintf(geomFile, "%e %e %e ", x[0], x[1], x[2]) < 0)
      {
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      return;
      }
    if ( (i % 2) )
      {
      if (fprintf(geomFile, "\n") < 0)
        {
        this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
        return;
        }
      }
    }
  if ( (numPts % 2) )
    {
    if (fprintf(geomFile, "\n") < 0)
      {
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      return;
      }
    }


  for (inPolys->InitTraversal(); inPolys->GetNextCell(npts,pts); )
    {


    for (i=0; i < (npts-1); i++)
      {
      if (fprintf (geomFile, "%d ", static_cast<int>(pts[i]+1)) < 0)
        {
        this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
        return;
        }
      }
    if (fprintf (geomFile, "%d\n", static_cast<int>(-(pts[npts-1]+1))) < 0)
      {
      this->SetErrorCode(vtkErrorCode::OutOfDiskSpaceError);
      return;
      }
    }

  vtkDebugMacro(<<"Wrote " << numPts << " points, " << numPolys << " polygons");
}
