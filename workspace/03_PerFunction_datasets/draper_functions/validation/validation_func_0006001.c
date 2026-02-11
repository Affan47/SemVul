jswrap_onewire_select(JsVar *parent, JsVar *rom) {
  Pin pin = onewire_getpin(parent);
  if (!jshIsPinValid(pin)) return;
  if (!jsvIsString(rom) || jsvGetStringLength(rom)!=16) {
    jsWarn("Invalid OneWire device address");
    return;
  }


  unsigned long long romdata = 0;
  JsvStringIterator it;
  jsvStringIteratorNew(&it, rom, 0);
  int i;
  for (i=0;i<8;i++) {
    char b[3];
    b[0] = jsvStringIteratorGetChar(&it);
    jsvStringIteratorNext(&it);
    b[1] = jsvStringIteratorGetChar(&it);
    jsvStringIteratorNext(&it);
    b[2] = 0;
    romdata = romdata | (((unsigned long long)stringToIntWithRadix(b,16,0)) << (i*8));

  }
  jsvStringIteratorFree(&it);


  OneWireWrite(pin, 8, 0x55);
  OneWireWrite(pin, 64, romdata);
}
