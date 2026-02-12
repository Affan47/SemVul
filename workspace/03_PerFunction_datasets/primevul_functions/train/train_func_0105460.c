STATIC void
S_reginsert(pTHX_ RExC_state_t *pRExC_state, const U8 op,
                  const regnode_offset operand, const U32 depth)
{
    regnode *src;
    regnode *dst;
    regnode *place;
    const int offset = regarglen[(U8)op];
    const int size = NODE_STEP_REGNODE + offset;
    GET_RE_DEBUG_FLAGS_DECL;

    PERL_ARGS_ASSERT_REGINSERT;
    PERL_UNUSED_CONTEXT;
    PERL_UNUSED_ARG(depth);

    DEBUG_PARSE_FMT("inst"," - %s", PL_reg_name[op]);
    assert(!RExC_study_started);


    change_engine_size(pRExC_state, (Ptrdiff_t) size);
    src = REGNODE_p(RExC_emit);
    RExC_emit += size;
    dst = REGNODE_p(RExC_emit);


    if (! IN_PARENS_PASS && RExC_open_parens) {
        int paren;


        for ( paren=0 ; paren < RExC_npar ; paren++ ) {


            if ( paren && RExC_open_parens[paren] >= operand ) {

                RExC_open_parens[paren] += size;
            } else {

            }
            if ( RExC_close_parens[paren] >= operand ) {

                RExC_close_parens[paren] += size;
            } else {

            }
        }
    }
    if (RExC_end_op)
        RExC_end_op += size;

    while (src > REGNODE_p(operand)) {
	StructCopy(--src, --dst, regnode);
#ifdef RE_TRACK_PATTERN_OFFSETS
        if (RExC_offsets) {
	    MJD_OFFSET_DEBUG(
                 ("%s(%d): (op %s) %s copy %" UVuf " -> %" UVuf " (max %" UVuf ").\n",
                  "reginsert",
		  __LINE__,
		  PL_reg_name[op],
                  (UV)(REGNODE_OFFSET(dst)) > RExC_offsets[0]
		    ? "Overwriting end of array!\n" : "OK",
                  (UV)REGNODE_OFFSET(src),
                  (UV)REGNODE_OFFSET(dst),
                  (UV)RExC_offsets[0]));
	    Set_Node_Offset_To_R(REGNODE_OFFSET(dst), Node_Offset(src));
	    Set_Node_Length_To_R(REGNODE_OFFSET(dst), Node_Length(src));
        }
#endif
    }

    place = REGNODE_p(operand);
#ifdef RE_TRACK_PATTERN_OFFSETS
    if (RExC_offsets) {
	MJD_OFFSET_DEBUG(
              ("%s(%d): (op %s) %s %" UVuf " <- %" UVuf " (max %" UVuf ").\n",
              "reginsert",
	      __LINE__,
	      PL_reg_name[op],
              (UV)REGNODE_OFFSET(place) > RExC_offsets[0]
              ? "Overwriting end of array!\n" : "OK",
              (UV)REGNODE_OFFSET(place),
              (UV)(RExC_parse - RExC_start),
              (UV)RExC_offsets[0]));
	Set_Node_Offset(place, RExC_parse);
	Set_Node_Length(place, 1);
    }
#endif
    src = NEXTOPER(place);
    FLAGS(place) = 0;
    FILL_NODE(operand, op);


    Zero(src, offset, regnode);
}
