loadKeymap(Bit32u stringToSymbol(const char*), const char* filename)
{
  FILE   *keymapFile;
  char baseSym[256], modSym[256], hostSym[256];
  Bit32s ascii = 0;
  Bit32u baseKey, modKey, hostKey;
  struct stat status;

  if (stat(filename, &status)) {
    BX_PANIC(("Can not stat keymap file '%s'.",filename));
  }

  if (!(S_ISREG(status.st_mode))) {
    BX_PANIC(("Keymap file '%s' is not a file",filename));
  }

  if((keymapFile = fopen(filename,"r"))==NULL) {
    BX_PANIC(("Can not open keymap file '%s'.",filename));
  }

  BX_INFO(("Loading keymap from '%s'",filename));
  init_parse();


  while(1) {
    if (get_next_keymap_line (keymapFile,
          baseSym, modSym, &ascii, hostSym) < 0) { break; }


    baseKey = convertStringToBXKey(baseSym);
    modKey = convertStringToBXKey(modSym);
    hostKey = 0;
    if (stringToSymbol != NULL)
      hostKey = stringToSymbol(hostSym);

    BX_DEBUG(("baseKey='%s' (%d), modSym='%s' (%d), ascii=%d, guisym='%s' (%d)", baseSym, baseKey, modSym, modKey, ascii, hostSym, hostKey));


    if (baseKey==BX_KEYMAP_UNKNOWN) {
      BX_PANIC (("line %d: unknown BX_KEY constant '%s'",lineCount,baseSym));
      continue;
    }

    if (hostKey==BX_KEYMAP_UNKNOWN) {
      BX_PANIC (("line %d: unknown host key name '%s' (wrong keymap ?)",lineCount,hostSym));
      continue;
    }

    keymapTable=(BXKeyEntry*)realloc(keymapTable,(keymapCount+1) * sizeof(BXKeyEntry));

    if (keymapTable==NULL)
      BX_PANIC(("Can not allocate memory for keymap table."));

    keymapTable[keymapCount].baseKey=baseKey;
    keymapTable[keymapCount].modKey=modKey;
    keymapTable[keymapCount].ascii=ascii;
    keymapTable[keymapCount].hostKey=hostKey;

    keymapCount++;
  }

  BX_INFO(("Loaded %d symbols",keymapCount));

  fclose(keymapFile);
}
