RemovePoint(vtkIdType ptId)
{
  int found = 0;
  vtkIdType pos = this->HashFunction(ptId);


  assert("check: valid range pos" &&
         static_cast<unsigned>(pos) < this->HashPoints->PointVector.size() );


  vtkEdgeTablePoints::VectorPointTableType &vect =
    this->HashPoints->PointVector[pos];


  vtkEdgeTablePoints::VectorPointTableType::iterator it;
  for (it= vect.begin(); it!= vect.end(); )
    {
    PointEntry &ent = *it;

    if( ent.PointId == ptId )
      {
      --ent.Reference;
      found = 1;
      }

    if( ent.PointId == ptId && ent.Reference == 0 )
      {
      it = vect.erase(it);
      }
    else
      {
      ++it;
      }
    }

  if( !found )
    {

    vtkErrorMacro( << "No entry were found in the hash table" );
    }
}
