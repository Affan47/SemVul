GetParallelopipedBoundingPlanes( vtkPlaneCollection * pc )
{
  vtkPlaneCollection * pc2 = vtkPlaneCollection::New();
  this->GetBoundingPlanes( pc2 );
  vtkPlane *p;
  int i = 0;
  for (pc2->InitTraversal(); ((p = pc2->GetNextItem()) && i < 6); ++i )
    {
    pc->AddItem(p);
    }
  pc2->Delete();
}
