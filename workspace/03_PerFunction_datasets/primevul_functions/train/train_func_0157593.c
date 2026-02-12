S_ssc_cp_and(pTHX_ regnode_ssc *ssc, const UV cp)
{


    SV* cp_list = _new_invlist(2);

    PERL_ARGS_ASSERT_SSC_CP_AND;

    assert(is_ANYOF_SYNTHETIC(ssc));

    cp_list = add_cp_to_invlist(cp_list, cp);
    ssc_intersection(ssc, cp_list,
                     FALSE
                     );
    SvREFCNT_dec_NN(cp_list);
}
