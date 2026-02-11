handleDefFile( void* userData, uint32_t stream,
           uint32_t token, const char *name,
           uint32_t group, OTF_KeyValueList* kvlist )
{
        Control* c= (Control*) userData;

        if( c->records[OTF_DEFFILE_RECORD] ) {

                ++c->num;
                if( c->num >= c->minNum && c->num <= c->maxNum && ! c->silent_mode ) {

                        fprintf( c->outfile, "(#%llu) \tDefFile: %s, stream %llu, "
                                             "token %llu, group %llu",
                                (long long unsigned) c->num, name, (long long unsigned) stream,
                                (long long unsigned) token, (long long unsigned) group );

			            printKeyValueList(c, kvlist);
                }
        }
        return OTF_RETURN_OK;
}
