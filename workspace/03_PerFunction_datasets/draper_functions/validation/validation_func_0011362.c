keyPress(const XEvent *pEvent_,KeySym k_,unsigned int s_,const char *b_)
{
  MSKeyPress keyPress(k_,s_);
  if (isProtected()==MSFalse&&keyTranslate(keyPress)==MSFalse) key(k_,s_,b_); }
