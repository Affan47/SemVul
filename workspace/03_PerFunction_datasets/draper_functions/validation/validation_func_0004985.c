mdb_index_recset(
	struct mdb_info *mdb,
	Attribute *a,
	AttributeType *type,
	struct berval *tags,
	IndexRec *ir )
{
	int rc, slot;
	AttrList *al;

	if( type->sat_sup ) {

		rc = mdb_index_recset( mdb, a, type->sat_sup, tags, ir );
		if( rc ) return rc;
	}

	if( type->sat_ad ) {
		slot = mdb_attr_slot( mdb, type->sat_ad, NULL );
		if ( slot >= 0 ) {
			ir[slot].ir_ai = mdb->mi_attrs[slot];
			al = ch_malloc( sizeof( AttrList ));
			al->attr = a;
			al->next = ir[slot].ir_attrs;
			ir[slot].ir_attrs = al;
		}
	}
	if( tags->bv_len ) {
		AttributeDescription *desc;

		desc = ad_find_tags( type, tags );
		if( desc ) {
			slot = mdb_attr_slot( mdb, desc, NULL );
			if ( slot >= 0 ) {
				ir[slot].ir_ai = mdb->mi_attrs[slot];
				al = ch_malloc( sizeof( AttrList ));
				al->attr = a;
				al->next = ir[slot].ir_attrs;
				ir[slot].ir_attrs = al;
			}
		}
	}
	return LDAP_SUCCESS;
}
