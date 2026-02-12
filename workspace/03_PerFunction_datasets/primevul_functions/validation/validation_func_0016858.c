void SFD_AssignLookups(SplineFont1 *sf) {
    PST1 *pst, *pst2;
    int isv;
    KernPair1 *kp, *kp2;
    KernClass1 *kc, *kc2;
    FPST1 *fpst;
    ASM1 *sm;
    AnchorClass1 *ac, *ac2;
    int gid, gid2, cnt, i, k, isgpos;
    SplineFont1 *subsf;
    SplineChar *sc, *sc2;
    OTLookup *otl, **all;
    struct lookup_subtable *sub;


    SFDCleanupAnchorClasses(&sf->sf);
    if ( sf->sf.uni_interp==ui_unset && sf->sf.map!=NULL )
	sf->sf.uni_interp = interp_from_encoding(sf->sf.map->enc,ui_none);


    if ( sf->sf.pfminfo.os2_winascent < sf->sf.ascent/4 && !sf->sf.pfminfo.winascent_add ) {
	sf->sf.pfminfo.winascent_add = true;
	sf->sf.pfminfo.os2_winascent = 0;
	sf->sf.pfminfo.windescent_add = true;
	sf->sf.pfminfo.os2_windescent = 0;
    }


    k=0;
    do {
	subsf = sf->sf.subfontcnt==0 ? sf : (SplineFont1 *) (sf->sf.subfonts[k]);
	for ( gid=0; gid<subsf->sf.glyphcnt; ++gid ) if ( (sc=subsf->sf.glyphs[gid])!=NULL ) {
	    for ( pst = (PST1 *) (sc->possub); pst!=NULL; pst = (PST1*) (pst->pst.next) ) {
		if ( pst->pst.type == pst_lcaret || pst->pst.subtable!=NULL )
	    continue;
		otl = CreateLookup(sf,pst->tag,pst->script_lang_index,pst->flags,pst->pst.type);
		sub = CreateSubtable(otl,sf);


		for ( pst2=pst ; pst2!=NULL; pst2 = (PST1 *) (pst2->pst.next) ) {
		    if ( pst2->tag==pst->tag &&
			    pst2->script_lang_index==pst->script_lang_index &&
			    pst2->flags==pst->flags &&
			    pst2->pst.type==pst->pst.type )
			pst2->pst.subtable = sub;
		}
		for ( gid2=gid+1; gid2<subsf->sf.glyphcnt; ++gid2 ) if ( (sc2=subsf->sf.glyphs[gid2])!=NULL ) {
		    for ( pst2 = (PST1 *) (sc2->possub); pst2!=NULL; pst2 = (PST1 *) (pst2->pst.next) ) {
			if ( pst2->tag==pst->tag &&
				pst2->script_lang_index==pst->script_lang_index &&
				pst2->flags==pst->flags &&
				pst2->pst.type==pst->pst.type )
			    pst2->pst.subtable = sub;
		    }
		}
	    }
	}
	++k;
    } while ( k<sf->sf.subfontcnt );


    for ( isv=0; isv<2; ++isv ) {
	k=0;
	do {
	    subsf = sf->sf.subfontcnt==0 ? sf : (SplineFont1 *) (sf->sf.subfonts[k]);
	    for ( gid=0; gid<subsf->sf.glyphcnt; ++gid ) if ( (sc=subsf->sf.glyphs[gid])!=NULL ) {
		for ( kp = (KernPair1 *) (isv ? sc->vkerns : sc->kerns); kp!=NULL; kp = (KernPair1 *) (kp->kp.next) ) {
		    if ( kp->kp.subtable!=NULL )
		continue;
		    otl = CreateLookup(sf,isv ? CHR('v','k','r','n') : CHR('k','e','r','n'),
			    kp->sli,kp->flags,pst_pair);
		    sub = CreateSubtable(otl,sf);


		    for ( kp2=kp ; kp2!=NULL; kp2 = (KernPair1 *) (kp2->kp.next) ) {
			if ( kp2->sli==kp->sli && kp2->flags==kp->flags )
			    kp2->kp.subtable = sub;
		    }
		    for ( gid2=gid+1; gid2<subsf->sf.glyphcnt; ++gid2 ) if ( (sc2=subsf->sf.glyphs[gid2])!=NULL ) {
			for ( kp2 = (KernPair1 *) (isv ? sc2->vkerns : sc2->kerns); kp2!=NULL; kp2 = (KernPair1 *) (kp2->kp.next) ) {
			    if ( kp2->sli==kp->sli && kp2->flags==kp->flags )
				kp2->kp.subtable = sub;
			}
		    }

		    for ( kc=(KernClass1 *) (isv ? sf->sf.vkerns : sf->sf.kerns); kc!=NULL;
			    kc = (KernClass1 *) (kc->kc.next) ) {
			if ( kc->sli == kp->sli && kc->flags == kp->flags && kc->kc.subtable==NULL) {
			    sub = CreateSubtable(otl,sf);
			    sub->per_glyph_pst_or_kern = false;
			    sub->kc = &kc->kc;
			    kc->kc.subtable = sub;
			}
		    }
		}
	    }
	    ++k;
	} while ( k<sf->sf.subfontcnt );

	for ( kc=(KernClass1 *) (isv ? sf->sf.vkerns : sf->sf.kerns); kc!=NULL;
		kc = (KernClass1 *) (kc->kc.next) ) {
	    if ( kc->kc.subtable==NULL) {
		otl = CreateLookup(sf,isv ? CHR('v','k','r','n') : CHR('k','e','r','n'),
			kc->sli,kc->flags,pst_pair);
		for ( kc2=kc; kc2!=NULL; kc2=(KernClass1 *) (kc2->kc.next) ) {
		    if ( kc->sli == kc2->sli && kc->flags == kc2->flags && kc2->kc.subtable==NULL) {
			sub = CreateSubtable(otl,sf);
			sub->per_glyph_pst_or_kern = false;
			sub->kc = &kc2->kc;
			kc2->kc.subtable = sub;
		    }
		}
	    }
	}
    }


    for ( fpst=(FPST1 *) sf->sf.possub; fpst!=NULL; fpst=((FPST1 *) fpst->fpst.next) ) {
	otl = CreateLookup(sf,fpst->tag, fpst->script_lang_index,
		fpst->flags,fpst->fpst.type);
	sub = CreateSubtable(otl,sf);
	sub->per_glyph_pst_or_kern = false;
	sub->fpst = &fpst->fpst;
	fpst->fpst.subtable = sub;
	FPSTReplaceTagsWithLookups(&fpst->fpst,sf);
    }
    for ( sm=(ASM1 *) sf->sf.sm; sm!=NULL; sm=((ASM1 *) sm->sm.next) ) {
	otl = CreateMacLookup(sf,sm);
	sub = CreateSubtable(otl,sf);
	sub->per_glyph_pst_or_kern = false;
	sub->sm = &sm->sm;
	sm->sm.subtable = sub;
	if ( sm->sm.type==asm_context )
	    ASMReplaceTagsWithLookups(&sm->sm,sf);
    }


    for ( isgpos=0; isgpos<2; ++isgpos ) {
	for ( otl = isgpos ? sf->sf.gpos_lookups : sf->sf.gsub_lookups ;
		otl != NULL; otl=otl->next ) {
	    if ( otl->features!=NULL && otl->features->scripts==NULL ) {
		chunkfree(otl->features,sizeof(FeatureScriptLangList));
		otl->features = NULL;
	    }
	}
    }


    for ( ac=(AnchorClass1 *) (sf->sf.anchor); ac!=NULL; ac=(AnchorClass1 *) ac->ac.next ) {
	ACHasBaseLig(sf,ac);
	if ( ac->has_ligatures && !ac->has_bases )
	    ac->ac.type = act_mklg;
	else if ( ac->has_ligatures && ac->has_bases )
	    ACDisassociateLigatures(sf,ac);
    }
    for ( ac=(AnchorClass1 *) (sf->sf.anchor); ac!=NULL; ac=(AnchorClass1 *) ac->ac.next ) {
	if ( ac->ac.subtable==NULL ) {
	    otl = CreateACLookup(sf,ac);
	    sub = CreateSubtable(otl,sf);
	    for ( ac2=ac; ac2!=NULL; ac2 = (AnchorClass1 *) ac2->ac.next ) {
		if ( ac2->feature_tag == ac->feature_tag &&
			ac2->script_lang_index == ac->script_lang_index &&
			ac2->flags == ac->flags &&
			ac2->ac.type == ac->ac.type &&
			ac2->merge_with == ac->merge_with )
		    ac2->ac.subtable = sub;
	    }
	}
    }


    for ( otl=sf->sf.gsub_lookups, cnt=0; otl!=NULL; otl=otl->next, ++cnt );
    if ( cnt!=0 ) {
	all = malloc(cnt*sizeof(OTLookup *));
	for ( otl=sf->sf.gsub_lookups, cnt=0; otl!=NULL; otl=otl->next, ++cnt ) {
	    all[cnt] = otl;
	    otl->lookup_index = GSubOrder(sf,otl->features);
	}
	qsort(all,cnt,sizeof(OTLookup *),order_lookups);
	sf->sf.gsub_lookups = all[0];
	for ( i=1; i<cnt; ++i )
	    all[i-1]->next = all[i];
	all[cnt-1]->next = NULL;
	free( all );
    }

    for ( isgpos=0; isgpos<2; ++isgpos ) {
	for ( otl = isgpos ? sf->sf.gpos_lookups : sf->sf.gsub_lookups , cnt=0;
		otl!=NULL; otl = otl->next ) {
	    otl->lookup_index = cnt++;
	    NameOTLookup(otl,&sf->sf);
	}
    }
}
