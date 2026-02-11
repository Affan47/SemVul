HTTPInit(ws, wr, class_closure)
ChimeraSource ws;
ChimeraRequest *wr;
void *class_closure;
{
  HTTPClass *hc = (HTTPClass *)class_closure;
  HTTPInfo **hip;

  hip = (HTTPInfo **)alloc_mem(sizeof(HTTPInfo **));

  if (HTTPCreateInfo(hip, ws, wr, hc, wr->up, wr->pup, NULL) == -1)
  {
    free_mem(hip);
    return(NULL);
  }

  return(hip);
}
