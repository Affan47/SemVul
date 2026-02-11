To_Double(WamWord x)
{
  return (Tag_Is_INT(x)) ? (double) (UnTag_INT(x)) :
    Obtain_Float(UnTag_FLT(x));
}
