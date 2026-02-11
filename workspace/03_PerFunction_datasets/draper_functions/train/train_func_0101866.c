fbh_delfbfig (listfbfig, ptfbfig, mode)

struct fbfig *listfbfig;
struct fbfig *ptfbfig;
char          mode;

{
struct fbfig  headfig;
struct fbfig *ptlastfig;
struct ptype *ptptype;

if ((listfbfig != 0) && (ptfbfig != 0))
  {


  headfig.NEXT = listfbfig;
  ptlastfig    = &headfig;
  while ((ptlastfig != 0) && (ptlastfig->NEXT != ptfbfig))
    ptlastfig = ptlastfig->NEXT;

  if (ptlastfig != 0)
    {


    if (mode == 'N')
      {
      if ((ptfbfig->BEREG != 0) || (ptfbfig->BEMSG != 0) ||
          (ptfbfig->BERIN != 0) || (ptfbfig->BEOUT != 0) ||
          (ptfbfig->BEBUS != 0) || (ptfbfig->BEAUX != 0) ||
          (ptfbfig->BEDLY != 0) || (ptfbfig->BEBUX != 0) ||
      (ptfbfig->BEPOR != 0) || (ptfbfig->USER  != 0))

        (void) fprintf (stderr,"FBH_warning : fbfig `%s` not empty\n",
                        ptfbfig->NAME);
      }
    else
      {
      fbh_frefbreg (ptfbfig->BEREG);
      fbh_frefbmsg (ptfbfig->BEMSG);
      fbh_frefbrin (ptfbfig->BERIN);
      fbh_frefbout (ptfbfig->BEOUT);
      fbh_frefbbus (ptfbfig->BEBUS);
      fbh_frefbaux (ptfbfig->BEAUX);
      fbh_frefbaux (ptfbfig->BEDLY);
      fbh_frefbbux (ptfbfig->BEBUX);
      fbh_frefbpor (ptfbfig->BEPOR);
      if ((ptptype = getptype (ptfbfig->USER,FBH_GENERIC)) != 0)
        fbh_frefbgen (ptptype->DATA);
      }

    ptlastfig->NEXT = ptfbfig->NEXT;
    mbkfree (ptfbfig);
    }

  listfbfig = headfig.NEXT;
  }

return(listfbfig);
}
