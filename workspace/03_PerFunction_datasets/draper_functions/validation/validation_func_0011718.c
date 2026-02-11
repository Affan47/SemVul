FDK_DRC_Generator_Open(
        HDRC_COMP                      *phDrcComp
        )
{
    INT err = 0;
    HDRC_COMP hDcComp = NULL;

    if (phDrcComp == NULL) {
      err = -1;
      goto bail;
    }


    hDcComp = (HDRC_COMP)FDKcalloc(1, sizeof(DRC_COMP));

    if (hDcComp == NULL) {
      err = -1;
      goto bail;
    }

    FDKmemclear(hDcComp, sizeof(DRC_COMP));


    *phDrcComp = hDcComp;
    return err;
bail:
    FDK_DRC_Generator_Close(&hDcComp);
    return err;
}
