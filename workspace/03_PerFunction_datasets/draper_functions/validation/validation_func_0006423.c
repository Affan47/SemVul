Begin( vtkIdTypeArray* lastPlaced )
{

  this->PreviousLabels = lastPlaced;
  this->PreviousLabelIter = 0;
  this->AtEnd = -1;
  if ( ! this->PreviousLabels->GetNumberOfTuples() )
    {

    this->BeginOctreeTraversal();
    }
}
