SetDepth(double depth)
{
  if(depth != this->Depth)
  {
    double step = this->Depth - depth;
    Superclass::Translate(0, 0, step);
    this->Depth = depth;
  }
}
