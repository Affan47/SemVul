jswrap_pipe_drain_listener(JsVar *destination) {
  if (!jsvIsObject(destination)) return;

  JsVar *arr = pipeGetArray(false);
  if (arr) {
    JsvObjectIterator it;
    jsvObjectIteratorNew(&it, arr);
    while (jsvObjectIteratorHasValue(&it)) {
      JsVar *pipe = jsvObjectIteratorGetValue(&it);
      JsVar *dst = jsvObjectGetChild(pipe,"destination",0);
      if (dst == destination) {

        jsvUnLock(jsvObjectSetChild(pipe,"drainWait",jsvNewFromBool(false)));
      }
      jsvUnLock(dst);
      jsvUnLock(pipe);
      jsvObjectIteratorNext(&it);
    }
    jsvObjectIteratorFree(&it);
    jsvUnLock(arr);
  }
}
