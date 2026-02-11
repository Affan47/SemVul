InstantiatePrinter(Printer*& p, SystemServices* pSS)


{


    FAMILY_HANDLE familyHandle = pPFI->FindDevIdMatch(ModelName[device]);
    if (familyHandle == NULL)
    {
        ASSERT(familyHandle);
        DBG1("DR::InstantiatePrinter - no family match\n");
        return UNSUPPORTED_PRINTER;
    }
    p = pPFI->CreatePrinter(pSS, familyHandle);
    NEWCHECK(p);
    return p->constructor_error;
}
