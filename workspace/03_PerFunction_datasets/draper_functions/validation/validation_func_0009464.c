jswrap_waveform_getBuffer(JsVar *waveform, int bufferNumber, bool *is16Bit) {
  JsVar *buffer = jsvObjectGetChild(waveform, (bufferNumber==0)?"buffer":"buffer2", 0);
  if (!buffer) return 0;
  if (is16Bit) {
    *is16Bit = false;
    if (jsvIsArrayBuffer(buffer) && JSV_ARRAYBUFFER_GET_SIZE(buffer->varData.arraybuffer.type)==2)
      *is16Bit = true;
  }

  JsVar *backingString = jsvGetArrayBufferBackingString(buffer);
  jsvUnLock(buffer);
  return backingString;
}
