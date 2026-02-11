keyPressNotify(MSWidget *pWidget_,const XEvent *pEvent_,
                               KeySym keysym_,unsigned int state_,const char *pString_)
{ if (pWidget_!=0) pWidget_->keyPress(pEvent_,keysym_,state_,pString_); }
