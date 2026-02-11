lineSizeName(LineSize size)
{
  switch (size)
  {
  case LineSize1:
    return QString("1");
  case LineSize2:
    return QString("2");
  case LineSize3:
    return QString("3");
  case LineSize4:
    return QString("4");
  case LineSize5:
    return QString("5");
  case LineSize6:
    return QString("6");
  case LineSize7:
    return QString("7");
  case LineSize8:
    return QString("8");
  case MaxLineSize:
  default:
    return QString("");
  }
}
