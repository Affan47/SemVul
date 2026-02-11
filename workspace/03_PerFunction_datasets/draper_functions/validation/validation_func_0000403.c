ToDirectedGraph(vtkDirectedGraph* g)
{


  if(this->IsA("vtkDirectedGraph"))
    {

    return g->CheckedShallowCopy(this);
    }
  else if(this->IsA("vtkUndirectedGraph"))
    {
    vtkSmartPointer<vtkMutableDirectedGraph> m =
      vtkSmartPointer<vtkMutableDirectedGraph>::New();
    for(vtkIdType i = 0; i < this->GetNumberOfVertices(); i++)
      {
      m->AddVertex();
      }


    for(vtkIdType i = 0; i < this->GetNumberOfEdges(); i++)
      {
      m->AddEdge(this->GetSourceVertex(i), this->GetTargetVertex(i));
      }

    if(g->IsStructureValid(m))
      {

      g->CopyInternal(this, false);


      g->SetInternals(m->Internals);
      return true;
      }
    else
      {
      return false;
      }
    }
  else
    {
    g = NULL;
    return false;
    }
}
