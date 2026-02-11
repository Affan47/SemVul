RenderQuery(wn, key)
ChimeraRender wn;
char *key;
{
  if (wn->rh.query != NULL)
  {
    return(CMethodBytePtr(wn->rh.query)(wn->rc, key));
  }
  return(NULL);
}
