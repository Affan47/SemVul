updateBackground(unsigned long oldbg_)
{
  MSLayout::updateBackground(oldbg_);
  for (unsigned i=0;i<sashList().length();i++) _sashList(i)->background(background());
}
