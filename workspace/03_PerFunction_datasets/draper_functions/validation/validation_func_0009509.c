TruncateFaceOwner()
{
  const int boundaryStartFace =
      this->BoundaryDict.size() > 0 ? this->BoundaryDict[0].StartFace
          : this->FaceOwner->GetNumberOfTuples();

  const int nBoundaryFaces = this->FaceOwner->GetNumberOfTuples()
      - boundaryStartFace;
  memmove(this->FaceOwner->GetPointer(0),
      this->FaceOwner->GetPointer(boundaryStartFace), sizeof(int)
          * nBoundaryFaces);
  this->FaceOwner->Resize(nBoundaryFaces);
}
