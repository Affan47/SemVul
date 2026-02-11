BeginFileX()
{
  byte line[cchSzDef];

  if (us.fNoWrite)
    return;
#ifndef WIN
  if (gi.szFileOut == NULL && (
#ifdef PS
    gi.fEps ||
#endif
    gs.fMeta || (gs.fBitmap && gs.chBmpMode == 'B'))) {
    sprintf(line, "(It is recommended to specify an extension of '.%s'.)\n",
      gs.fBitmap ? "bmp" :
#ifdef PS
      (gi.fEps ? "eps" : "wmf")
#else
      "wmf"
#endif
      );
    PrintSzScreen(line);
  }
#endif
  loop {
    if (gi.szFileOut == NULL) {
      sprintf(line, "Enter name of file to write %s to",
        gs.fBitmap ? "bitmap" : (gs.fPS ? "PostScript" : "metafile"));
      InputString(line, line);
      gi.szFileOut = line;
    }
    gi.file = fopen(gi.szFileOut, gs.fPS ? "w" : "wb");
    if (gi.file != NULL)
      break;
    else {
      PrintWarning("Couldn't create output file.");
      gi.szFileOut = NULL;
    }
  }
}
