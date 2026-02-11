ShallowCopy(vtkGenericAttributeCollection *other)
{
  assert("pre: other_exists" && other!=0);
  assert("pre: not_self" && other!=this);

  this->AttributeInternalVector->Vector =
    other->AttributeInternalVector->Vector;
  this->AttributeIndices->Vector = other->AttributeIndices->Vector;
  int c = static_cast<int>(this->AttributeInternalVector->Vector.size());
  for (int i=0; i<c; ++i)
    {
    if (this->AttributeInternalVector->Vector[i] != 0)
      {
      this->AttributeInternalVector->Vector[i]->Register( this );
      }
    }
  this->Modified();

  assert("post: same_size" && this->GetNumberOfAttributes()==other->GetNumberOfAttributes());
}
