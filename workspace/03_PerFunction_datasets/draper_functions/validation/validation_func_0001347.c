startlf(des,lf,vfun,nopc)
design *des;
lfit *lf;
INT (*vfun)(), nopc;
{
    INT i, *mi;
    des->vfun = vfun;
    mi = lf->mi;
    mi[MP] = calcp(mi,mi[MDEG]);
    des->pref = 0;
    cvi = -1;
    deschk(des,mi[MN],mi[MP]);
    if (mi[MDEB]>0) printf("preprocess\n");
        preproc(des,lf,nopc);
        if (mi[MDEB]>0) printf("preprocess ok\n");
            if (lf_error) return;
    lf->ord = 0;
    makecfn(des,lf);
    if ((mi[MDIM]==1) && (lf->sty[0]!=STANGL))
    { i = 1;
        while ((i<mi[MN]) && (datum(lf,0,i)>=datum(lf,0,i-1))) i++;
        lf->ord = (i==mi[MN]);
    }

    if (mi[MDEB]>0) printf("call eval structure\n");
        switch(mi[MEV])
    { case EPHULL: triang_start(des,lf); break;
        case EDATA:  dataf(des,lf); break;
        case ECROS:  crossf(des,lf); break;
        case EGRID:  gridf(des,lf); break;
        case ETREE:  atree_start(des,lf); break;
        case EKDCE:  mi[MKT] = KCE;
        case EKDTR:  kdtre_start(des,lf); break;
        case EPRES:  preset(des,lf); break;
        case EXBAR:  xbarf(des,lf); break;
        case ENONE:  lf->nv = lf->nce = 0;
            return;
#ifdef CVERSION
        case 100: do_scbsim(des,lf); break;
#endif
        default: ERROR(("startlf: Invalid evaluation structure"));
    }


    if ((mi[MREN]) && (mi[MTG]==TDEN)) dens_renorm(lf,des);
        }
