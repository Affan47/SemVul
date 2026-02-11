echoListSplit3(echoScene *scene, echoObject *list, int depth) {
  echoObject *ret, *tmp0, *tmp1;

  if (!( echoTypeList == list->type ||
         echoTypeAABBox == list->type ))
    return NULL;

  if (!depth)
    return list;

  ret = echoListSplit(scene, list, 0);

#define DOIT(obj, ax) ((obj) = echoListSplit(scene, (obj), (ax)))
#define MORE(obj) echoTypeSplit == (obj)->type

  if (MORE(ret)) {
    tmp0 = DOIT(SPLIT(ret)->obj0, 1);
    if (MORE(tmp0)) {
      tmp1 = DOIT(SPLIT(tmp0)->obj0, 2);
      if (MORE(tmp1)) {
        SPLIT(tmp1)->obj0 = echoListSplit3(scene, SPLIT(tmp1)->obj0, depth-1);
        SPLIT(tmp1)->obj1 = echoListSplit3(scene, SPLIT(tmp1)->obj1, depth-1);
      }
      tmp1 = DOIT(SPLIT(tmp0)->obj1, 2);
      if (MORE(tmp1)) {
        SPLIT(tmp1)->obj0 = echoListSplit3(scene, SPLIT(tmp1)->obj0, depth-1);
        SPLIT(tmp1)->obj1 = echoListSplit3(scene, SPLIT(tmp1)->obj1, depth-1);
      }
    }
    tmp0 = DOIT(SPLIT(ret)->obj1, 1);
    if (MORE(tmp0)) {
      tmp1 = DOIT(SPLIT(tmp0)->obj0, 2);
      if (MORE(tmp1)) {
        SPLIT(tmp1)->obj0 = echoListSplit3(scene, SPLIT(tmp1)->obj0, depth-1);
        SPLIT(tmp1)->obj1 = echoListSplit3(scene, SPLIT(tmp1)->obj1, depth-1);
      }
      tmp1 = DOIT(SPLIT(tmp0)->obj1, 2);
      if (MORE(tmp1)) {
        SPLIT(tmp1)->obj0 = echoListSplit3(scene, SPLIT(tmp1)->obj0, depth-1);
        SPLIT(tmp1)->obj1 = echoListSplit3(scene, SPLIT(tmp1)->obj1, depth-1);
      }
    }
  }
  return ret;
}
