ContainsSpring(vtkSpring * spring)
{
  for(vtkIdType i = 0; i < this->Springs->GetNumberOfItems(); i++)
  {
    vtkSpring * local = this->GetSpring(i);
    vtkParticle * p0 = spring->GetParticle(0);
    vtkParticle * p1 = spring->GetParticle(1);
    if(local && local->ContainsParticle(p0) && local->ContainsParticle(p1)){
      return 1;
    }
  }
  return 0;
}
