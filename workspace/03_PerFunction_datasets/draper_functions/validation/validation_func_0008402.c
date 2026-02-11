evaluate(const char * expression) {
  Struct * s = (Struct *)(p);
  if (s->theExpression != 0) { delete[] s->theExpression; }
  s->theExpression = 0;
  s->thePosition   = 0;
  s->theStatus     = WARNING_BLANK_STRING;
  s->theResult     = 0.0;
  if (expression != 0) {
    s->theExpression = new char[strlen(expression)+1];
    strcpy(s->theExpression, expression);
    s->theStatus = engine(s->theExpression,
			  s->theExpression+strlen(expression)-1,
			  s->theResult,
			  s->thePosition,
			  s->theDictionary);
  }
  return s->theResult;
}
