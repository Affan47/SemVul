operator=(cmTargetInternalPointer const& r)
{
  if(this == &r) { return *this; }


  cmTargetInternals* oldPointer = this->Pointer;
  this->Pointer = new cmTargetInternals(*r.Pointer);
  delete oldPointer;
  return *this;
}
