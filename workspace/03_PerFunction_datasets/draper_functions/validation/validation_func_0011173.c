validate(const char *pString_,unsigned row_,unsigned)
{ return (MSView::model()!=0)?((array().set(row_,pString_)==MSError::MSSuccess)?MSTrue:MSFalse):MSTrue; }
