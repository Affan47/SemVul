_reader_next_line(bcf_srs_t *files)
{
    int i, min_pos = INT_MAX;


    while ( 1 )
    {

        if ( files->regions && _readers_next_region(files)<0 ) break;


        for (i=0; i<files->nreaders; i++)
        {
            _reader_fill_buffer(files, &files->readers[i]);


            if ( !files->readers[i].nbuffer ) continue;
            if ( min_pos > files->readers[i].buffer[1]->pos ) min_pos = files->readers[i].buffer[1]->pos;
        }
        if ( min_pos==INT_MAX )
        {
            if ( !files->regions ) break;
            continue;
        }


        if ( files->targets )
        {
            if  ( files->regions )
            {
                if ( !files->cseq || files->cseq!=files->regions->seq )
                {
                    bcf_sr_regions_seek(files->targets, files->regions->seq);
                    files->cseq = files->regions->seq;
                }
            }
            else
            {


                int rid = files->readers[0].buffer[1]->rid;
                if ( files->crid<0 || files->crid!=rid )
                {
                    bcf_sr_regions_seek(files->targets, files->readers[0].header->id[BCF_DT_CTG][rid].key);
                    files->crid = rid;
                }
            }
            if ( bcf_sr_regions_query(files->targets, min_pos, min_pos)<0 )
            {

                for (i=0; i<files->nreaders; i++)
                    if ( files->readers[i].nbuffer && files->readers[i].buffer[1]->pos==min_pos )
                        _reader_shift_buffer(&files->readers[i]);
                min_pos = INT_MAX;
                continue;
            }
        }

        break;
    }


    int nret = 0;
    bcf1_t *first = NULL;
    for (i=0; i<files->nreaders; i++)
    {
        files->has_line[i] = 0;


        if ( !files->readers[i].nbuffer || files->readers[i].buffer[1]->pos!=min_pos ) continue;


        if ( _reader_match_alleles(files, &files->readers[i], first) < 0 ) continue;
        if ( !first ) first = files->readers[i].buffer[0];

        nret++;
        files->has_line[i] = 1;
    }
    return nret;
}
