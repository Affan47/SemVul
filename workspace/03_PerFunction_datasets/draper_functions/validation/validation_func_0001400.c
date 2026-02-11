event_bar(type, replist)

int type;
char* replist;
{
  int newtype;
  int depth;
  int voiceno, indexno;

  depth = splitdepth;

  newtype = type;
  if ((type == THIN_THICK) || (type == THICK_THIN)) {
    newtype = DOUBLE_BAR;
  };
  addfeature(newtype, 0, 0, 0);
  copymap(v);
  zerobar();
  if (strlen(replist) > 0) {
    event_playonrep(replist);
  };

if (splitdepth > 0) {


  if (type != SINGLE_BAR)  recurse_back_and_change_bar (type);
  else recurse_back_to_original_voice();
  }


else
 {
 voiceno = v->voiceno;
 indexno = v->indexno;
 while (v->tosplitno != -1)
     {
      v = getvoicecontext(v->tosplitno);
      splitdepth++;
      addfeature(VOICE, v->indexno, 0, 0);
      sync_voice (v,0,0);

      if (strlen(replist) > 0) event_playonrep(replist);
     }
 if (v->fromsplitno != -1 || splitdepth >0) recurse_back_to_original_voice();
 }
}
