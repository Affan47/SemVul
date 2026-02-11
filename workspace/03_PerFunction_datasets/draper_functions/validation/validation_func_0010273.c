PatternCopy(struct pattern *old, real transform[6]) {
    struct pattern *pat = chunkalloc(sizeof(struct pattern));

    if ( old==NULL )
return( NULL );

    pat = chunkalloc(sizeof(struct pattern));

    *pat = *old;
    pat->pattern = copy( old->pattern );
    if ( transform!=NULL )
	MatMultiply(pat->transform,transform,pat->transform);
return( pat );
}
