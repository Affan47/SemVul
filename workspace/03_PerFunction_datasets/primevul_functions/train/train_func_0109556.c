static WhereLoop **whereLoopFindLesser(
  WhereLoop **ppPrev,
  const WhereLoop *pTemplate
){
  WhereLoop *p;
  for(p=(*ppPrev); p; ppPrev=&p->pNextLoop, p=*ppPrev){
    if( p->iTab!=pTemplate->iTab || p->iSortIdx!=pTemplate->iSortIdx ){


      continue;
    }


    assert( p->rSetup==0 || pTemplate->rSetup==0
                 || p->rSetup==pTemplate->rSetup );


    assert( p->rSetup>=pTemplate->rSetup );


    if( (p->wsFlags & WHERE_AUTO_INDEX)!=0
     && (pTemplate->nSkip)==0
     && (pTemplate->wsFlags & WHERE_INDEXED)!=0
     && (pTemplate->wsFlags & WHERE_COLUMN_EQ)!=0
     && (p->prereq & pTemplate->prereq)==pTemplate->prereq
    ){
      break;
    }


    if( (p->prereq & pTemplate->prereq)==p->prereq
     && p->rSetup<=pTemplate->rSetup
     && p->rRun<=pTemplate->rRun
     && p->nOut<=pTemplate->nOut
    ){
      return 0;
    }


    if( (p->prereq & pTemplate->prereq)==pTemplate->prereq
     && p->rRun>=pTemplate->rRun
     && p->nOut>=pTemplate->nOut
    ){
      assert( p->rSetup>=pTemplate->rSetup );
      break;
    }
  }
  return ppPrev;
}
