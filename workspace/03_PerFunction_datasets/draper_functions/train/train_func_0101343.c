Index_Strand_Width_fill(Index_Strand *index_strand){
    register guint64 n;
    for(n = index_strand->header.max_index_length; n; n >>= 1)
        index_strand->width.max_index_len_width++;
    for(n = index_strand->header.total_index_length; n; n >>= 1)
        index_strand->width.total_index_len_width++;
    return;
    }
