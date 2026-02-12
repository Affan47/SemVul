int ByteVector::rfind(const ByteVector &pattern, uint offset, int byteAlign) const
{


  ByteVectorMirror v(*this);
  ByteVectorMirror p(pattern);

  return v.find(p, offset, byteAlign);
}
