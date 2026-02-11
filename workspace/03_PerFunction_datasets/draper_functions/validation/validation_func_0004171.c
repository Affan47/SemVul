bvl_select (result, pt_str, pt_bdd, pt_ablstr)

bvl_ablstr   *result;
struct chain *pt_str;
pNode        *pt_bdd;
bvl_ablstr    pt_ablstr;

  {
  char             binstr[256];
  long              i;
  struct chain    *pt_auxabl;
  pNode            pt_bddres;
  pNode            pt_bddnew;
  pNode            pt_bddtmp;
  pNode            pt_bddaux;
  char             nomvar[10];
  struct chain    *pt_newabl;
  struct chain    *pt_newabl2;
  static long       oth_flg=0;
  static long       last_width=0;
  static pCircuit  pC = NULL;

  result->LIST_ABL = NULL;
  result->IDENT    = NULL;

  pt_bddtmp = zero;

  if (pC == NULL)
    pC = initializeCct ("-select-",200,0);

  if (*pt_bdd == NULL)
    {
    if (last_width < pt_ablstr.WIDTH)
      {
      for (; last_width<pt_ablstr.WIDTH ; last_width++)
        {
        sprintf (nomvar,"(%d)",last_width);
        createNodeTermBdd (addInputCct(pC,nomvar));
        }
      }
    *pt_bdd = zero;
    oth_flg = 0;
    }

  while (pt_str != NULL)
    {
    tobin (binstr, (char *)pt_str->DATA, -1, -1);
    if (oth_flg != 0)
      {
      bvl_error(30,NULL);
      }

    if (strcmp("others", (char *)pt_str->DATA))
      {
      pt_bddres = one;

      if (strlen (binstr) != pt_ablstr.WIDTH)
        {
        bvl_error(38,NULL);
        }
      for (i=0 ; binstr[i]!='\0' ; i++)
        {
        pt_bddaux = createNodeTermBdd (i+2);
        if (binstr[i] == '0')
          pt_bddaux = notBdd (pt_bddaux);
        pt_bddres = applyBinBdd (AND, pt_bddaux, pt_bddres);
        }
      pt_bddnew = applyBinBdd (OR,*pt_bdd,pt_bddres);

      if (*pt_bdd == pt_bddnew)
         {
         bvl_error(28,NULL);
         }

      *pt_bdd = pt_bddnew;
      }
    else
      {
      oth_flg   = 1;
      pt_bddres = notBdd (*pt_bdd);
      *pt_bdd   = one;
      }
    pt_bddtmp = applyBinBdd (OR,pt_bddtmp,pt_bddres);
    pt_str = pt_str->NEXT;
    }

  pt_newabl = bddToAbl (pt_bddtmp, pC->pNameI);

  pt_auxabl = pt_ablstr.LIST_ABL;
  i         = pt_ablstr.WIDTH - 1;
  while (pt_auxabl != NULL)
    {
    sprintf (nomvar,"(%i)",i);


    pt_newabl2 = substExpr (pt_newabl,namealloc(nomvar),
                            (struct chain *)pt_auxabl->DATA);
    freeExpr (pt_newabl);
    pt_newabl = pt_newabl2;

    i--;
    pt_auxabl = pt_auxabl->NEXT;
    }
  result->LIST_ABL = addchain (NULL, pt_newabl);
  result->WIDTH    = 1;

  }
