WriteData()
{
  ostream *fp;
  vtkGraph* const input = this->GetInput();

  vtkDebugMacro(<<"Writing vtk graph data...");

  if( !(fp=this->OpenVTKFile()) || !this->WriteHeader(fp) )
    {
    if(fp)
      {
      if(this->FileName)
        {
        vtkErrorMacro("Ran out of disk space; deleting file: "
                      << this->FileName);
        this->CloseVTKFile(fp);
        unlink(this->FileName);
        }
      else
        {
        this->CloseVTKFile(fp);
        vtkErrorMacro("Could not read memory header. ");
        }
      }
    return;
    }

  if(vtkDirectedGraph::SafeDownCast(input))
    {
    *fp << "DATASET DIRECTED_GRAPH\n";
    }
  else
    {
    *fp << "DATASET UNDIRECTED_GRAPH\n";
    }

  int error_occurred = 0;

  if(!error_occurred && !this->WriteFieldData(fp, input->GetFieldData()))
    {
    error_occurred = 1;
    }
  if(!error_occurred && !this->WritePoints(fp, input->GetPoints()))
    {
    error_occurred = 1;
    }
  if(!error_occurred)
    {
    const vtkIdType vertex_count = input->GetNumberOfVertices();
    *fp << "VERTICES " << vertex_count << "\n";
    const vtkIdType edge_count = input->GetNumberOfEdges();
    *fp << "EDGES " << edge_count << "\n";
    for (vtkIdType e = 0; e < edge_count; ++e)
      {
      *fp << input->GetSourceVertex(e) << " " << input->GetTargetVertex(e) << "\n";
      }
    }
  if(!error_occurred && !this->WriteEdgeData(fp, input))
    {
    error_occurred = 1;
    }
  if(!error_occurred && !this->WriteVertexData(fp, input))
    {
    error_occurred = 1;
    }

  if(error_occurred)
    {
    if(this->FileName)
      {
      vtkErrorMacro("Ran out of disk space; deleting file: " << this->FileName);
      this->CloseVTKFile(fp);
      unlink(this->FileName);
      }
    else
      {
      vtkErrorMacro("Error writing data set to memory");
      this->CloseVTKFile(fp);
      }
    return;
    }
  this->CloseVTKFile(fp);
}
