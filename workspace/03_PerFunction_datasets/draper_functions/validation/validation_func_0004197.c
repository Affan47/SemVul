expandToRange(const Range& range)
{
  if (!Range::expandToRange(range))

    return false;

  if (parentRange())
    parentRange()->expandToRange(*this);

  return true;
}
