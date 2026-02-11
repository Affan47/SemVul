start()
{
  nPendingElementsNonEmpty_ = pendingElements_.size();
  specFormatStack_.push_back(specFormat_);
  if (!inSimplePageSequence_)
    pageFormatStack_.push_back(pageFormat_);
}
