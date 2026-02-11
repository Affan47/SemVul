mergeCallSuper(Loc loc, unsigned cs)
{


    if (cs != callSuper)
    {
        int aAll = (cs        & (CSXthis_ctor | CSXsuper_ctor)) != 0;
        int bAll = (callSuper & (CSXthis_ctor | CSXsuper_ctor)) != 0;


        bool aAny = (cs        & CSXany_ctor) != 0;
        bool bAny = (callSuper & CSXany_ctor) != 0;


        bool aRet = (cs        & CSXreturn) != 0;
        bool bRet = (callSuper & CSXreturn) != 0;

        bool ok = true;


        if ( (aRet && !aAny && bAny) ||
             (bRet && !bAny && aAny))
        {   ok = false;
        }


        else if (aRet && aAll)
        {
            callSuper |= cs & (CSXany_ctor | CSXlabel);
        }
        else if (bRet && bAll)
        {
            callSuper = cs | (callSuper & (CSXany_ctor | CSXlabel));
        }
        else
        {
            ok = (aAll == bAll);


            if (ok && aRet && !aAny)
                callSuper |= CSXreturn;
            callSuper |= cs & (CSXany_ctor | CSXlabel);
        }
        if (!ok)
            error(loc, "one path skips constructor");
    }
}
