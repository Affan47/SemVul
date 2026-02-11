Match_1_1_display_func(Match *match,
                                   Sequence *query, Sequence *target,
                                   guint query_pos, guint target_pos,
                                   gchar *display_str){
    register Submat *submat = (match->type == Match_Type_DNA2DNA)
                            ? match->mas->dna_submat
                            : match->mas->protein_submat;
    g_assert(Match_pos_pair_is_valid(match, query, target,
                                     query_pos, target_pos));
    display_str[0] = Match_get_display_symbol(submat,
                           Sequence_get_symbol(query, query_pos),
                           Sequence_get_symbol(target, target_pos));
    display_str[1] = '\0';
    return;
    }
