ReadCells(vtkPolyData *data, vtkIdType numCells,
                                  int cellType)
{
  vtkIntArray *endIndices = vtkIntArray::New();
  vtkIntArray *cellIndices = vtkIntArray::New();
  vtkCellArray *cellArray = vtkCellArray::New();


  int status = this->ParseValues(endIndices, numCells);


  vtkIdType numIndices = 0;
  if (status != 0)
    {
    if (numCells > 0)
      {
      numIndices = endIndices->GetValue(numCells - 1);
      }
    status = this->ParseValues(cellIndices, numIndices);
    }


  if (status != 0)
    {
    cellArray->GetData()->Allocate(
      numCells + endIndices->GetValue(numCells - 1));

    vtkPoints *points = data->GetPoints();
    vtkIdType numPoints = points->GetNumberOfPoints();
    vtkIdType lastEndIndex = 0;
    for (vtkIdType i = 0; i < numCells; i++)
      {
      vtkIdType endIndex = endIndices->GetValue(i);
      numIndices = endIndex - lastEndIndex;

      cellArray->InsertNextCell(numIndices);


      for (vtkIdType j = 0; j < numIndices; j++)
        {
        vtkIdType idx = cellIndices->GetValue(lastEndIndex + j);
        if (idx > numPoints)
          {
          vtkErrorMacro("Index " << idx << " is greater than the"
                        << " total number of points " << numPoints << " "
                        << this->FileName);
          return 0;
          }
        cellArray->InsertCellPoint(idx);
        }

      lastEndIndex = endIndex;
      }

    if (cellType == VTK_POLYGON)
      {
      data->SetPolys(cellArray);
      }
    else if (cellType == VTK_POLY_LINE)
      {
      data->SetLines(cellArray);
      }
    }

  endIndices->Delete();
  cellIndices->Delete();
  cellArray->Delete();

  return status;
}
