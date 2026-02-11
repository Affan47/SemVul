CopyPathWithXForm(Path)

struct p **Path;
{
    struct p *OldPair,*NewPair;


    OldPair = *Path;
    if ((NewPair = alloc(p)) == NULL) {
        CDStatusInt = CDMALLOCFAILED;
        MallocFailed();
    }
    *Path = NewPair;
    NewPair->pX = OldPair->pX;
    NewPair->pY = OldPair->pY;
    TPoint(&NewPair->pX,&NewPair->pY);
    NewPair->pSucc = NULL;
    OldPair = OldPair->pSucc;
    while(OldPair != NULL) {
        if ((NewPair->pSucc = alloc(p)) == NULL) {
            CDStatusInt = CDMALLOCFAILED;
            MallocFailed();
        }
        NewPair = NewPair->pSucc;
        NewPair->pX = OldPair->pX;
        NewPair->pY = OldPair->pY;
        NewPair->pSucc = NULL;
        TPoint(&NewPair->pX,&NewPair->pY);
        OldPair = OldPair->pSucc;
    }
}
