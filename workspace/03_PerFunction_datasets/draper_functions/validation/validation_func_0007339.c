adjustRowForViewVector(unsigned viewRow_) const
{
  if (viewVector().length()==0) return viewRow_;
  else if (viewRow_<viewVector().length()) return viewVector()(viewRow_);
  else return viewVector().length();
}
