MakeUnstructuredGrid4(vtkDataSet *ids)
{

  vtkUnstructuredGrid *ds = vtkUnstructuredGrid::SafeDownCast(ids);
  if (!ds)
    {
    return;
    }
  ds->Initialize();
  vtkPoints *pts = vtkPoints::New();
  const double &XO = this->XOffset;
  const double &YO = this->YOffset;
  const double &ZO = this->ZOffset;
  pts->InsertNextPoint(XO+0.0, YO+0.0, ZO+0.0);
  pts->InsertNextPoint(XO+0.0, YO+1.0, ZO+0.0);
  pts->InsertNextPoint(XO+1.0, YO+0.0, ZO+0.0);
  pts->InsertNextPoint(XO+1.0, YO+1.0, ZO+0.0);
  pts->InsertNextPoint(XO+0.0, YO+0.0, ZO+1.0);
  pts->InsertNextPoint(XO+0.0, YO+1.0, ZO+1.0);
  pts->InsertNextPoint(XO+1.0, YO+0.0, ZO+1.0);
  pts->InsertNextPoint(XO+0.5, YO+0.5, ZO+2.0);
  ds->SetPoints(pts);
  pts->Delete();
  ds->Allocate();

  vtkIdType verts[10] = {0,1,2,  2,1,3, 4,5,6,7};
  ds->InsertNextCell(VTK_TRIANGLE, 3, &verts[0]);
  ds->InsertNextCell(VTK_TRIANGLE, 3, &verts[3]);
  ds->InsertNextCell(VTK_TETRA, 4, &verts[6]);

  this->MakeValues(ds);
}
