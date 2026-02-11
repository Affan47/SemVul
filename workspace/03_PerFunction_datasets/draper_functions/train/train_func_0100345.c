lcdFillRect_JS(struct JsGraphics *gfx, short x1, short y1, short x2, short y2) {
  JsVar *fillRect = jsvObjectGetChild(gfx->graphicsVar, "iFillRect", 0);
  if (fillRect) {
    JsVar *args[5];
    args[0] = jsvNewFromInteger(x1);
    args[1] = jsvNewFromInteger(y1);
    args[2] = jsvNewFromInteger(x2);
    args[3] = jsvNewFromInteger(y2);
    args[4] = jsvNewFromInteger((JsVarInt)gfx->data.fgColor);
    jsvUnLock(jspExecuteFunction(fillRect, gfx->graphicsVar, 5, args));
    jsvUnLockMany(5, args);
    jsvUnLock(fillRect);
  } else
    graphicsFallbackFillRect(gfx, x1,y1,x2,y2);
}
