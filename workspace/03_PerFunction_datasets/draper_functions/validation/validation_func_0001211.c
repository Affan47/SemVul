reslimit_get_registered_attributes()
{

	int 		i;
	char 		**attrs=NULL;


        slapi_rwlock_rdlock( reslimit_map_rwlock );

        for ( i = 0; i < reslimit_map_count; ++i ) {
                if ( reslimit_map[ i ].rlmap_at != NULL ) {
			charray_add(&attrs, slapi_ch_strdup(reslimit_map[ i ].rlmap_at));
                }
        }

        slapi_rwlock_unlock( reslimit_map_rwlock );

	return attrs;
}
