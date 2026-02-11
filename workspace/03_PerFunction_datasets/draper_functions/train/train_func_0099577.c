CDReflect(SymbolDesc)

struct s *SymbolDesc;
{


    int Int1;
    int L,B,R,T;
    struct bu *Bucket;
    struct m *MasterListDesc;


#ifdef DEBUGREFLECT
printf("Begin Reflect(%s).\n",SymbolDesc->sName);
printf("    Old BB is %d %d %d %d.\n",SymbolDesc->sLeft,SymbolDesc->sBottom,
    SymbolDesc->sRight,SymbolDesc->sTop);
#endif


    if (Not CDBB(SymbolDesc,(struct o *)NULL,&L,&B,&R,&T))
        return (False);

#ifdef DEBUGREFLECT
printf("    New BB is %d %d %d %d.\n",SymbolDesc->sLeft,SymbolDesc->sBottom,
    SymbolDesc->sRight,SymbolDesc->sTop);
#endif

    for (Int1 = 0;Int1 < CDNUMLAYERS;++Int1) {
        Bucket = CDSymbolTable[Int1];
        loop
            if (Bucket == NULL)
                break;


            elif (strcmp(Bucket->buSymbolDesc->sName,SymbolDesc->sName) == 0)
                Bucket = Bucket->buSucc;
            else {

#ifdef DEBUGREFLECT
printf("    Begin traversing master list of %s.\n",Bucket->buSymbolDesc->sName);
#endif

                MasterListDesc = Bucket->buSymbolDesc->sMasterList;
                loop
                    if (MasterListDesc == NULL) {

#ifdef DEBUGREFLECT
printf("    End traversing master list of %s.\n",Bucket->buSymbolDesc->sName);
#endif

                        break;
                    }
                    else {


#ifdef DEBUGREFLECT
printf("Considering %s.\n",MasterListDesc->mName);
printf("BB is %d %d %d %d.\n",MasterListDesc->mLeft,MasterListDesc->mBottom,
    MasterListDesc->mRight,MasterListDesc->mTop);
#endif

                        if (strcmp(MasterListDesc->mName,SymbolDesc->sName) == 0
                            And (MasterListDesc->mLeft != SymbolDesc->sLeft Or
                            MasterListDesc->mBottom != SymbolDesc->sBottom Or
                            MasterListDesc->mRight != SymbolDesc->sRight Or
                            MasterListDesc->mTop != SymbolDesc->sTop)) {

#ifdef DEBUGREFLECT
printf("BB conflict.\n");
#endif

                            MasterListDesc->mLeft = SymbolDesc->sLeft;
                            MasterListDesc->mBottom = SymbolDesc->sBottom;
                            MasterListDesc->mRight = SymbolDesc->sRight;
                            MasterListDesc->mTop = SymbolDesc->sTop;


                            if (Not CDPatchInstances(Bucket->buSymbolDesc,
                                MasterListDesc->mName)) return (False);


                            Bucket->buSymbolDesc->sBBValid = False;
                            if (Not CDBB(Bucket->buSymbolDesc,(struct o *)NULL,
                                &L,&B,&R,&T)) return (False);


                            if (Not CDReflect(Bucket->buSymbolDesc))
                                return (False);
                        }
                        MasterListDesc = MasterListDesc->mSucc;
                    };
                Bucket = Bucket->buSucc;
             };
    }

#ifdef DEBUGREFLECT
printf("End Reflect(%s).\n",SymbolDesc->sName);
#endif

    return (True);
}
