SetCursorShape(vtkPolyData *shape)
{
  if ( shape != this->CursorShape )
    {
    if ( this->CursorShape )
      {
      this->CursorShape->Delete();
      }
    this->CursorShape = shape;
    if ( this->CursorShape )
      {
      this->CursorShape->Register(this);
      this->Glypher->SetSource(this->CursorShape);
      }
    this->Modified();
    }
}
