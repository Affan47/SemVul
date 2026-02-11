S_visit(pTHX_ SVFUNC_t f, const U32 flags, const U32 mask)
{
    dVAR;
    SV* sva;
    I32 visited = 0;

    PERL_ARGS_ASSERT_VISIT;

    for (sva = PL_sv_arenaroot; sva; sva = MUTABLE_SV(SvANY(sva))) {
	const SV * const svend = &sva[SvREFCNT(sva)];
	SV* sv;
	for (sv = sva + 1; sv < svend; ++sv) {
	    if (SvTYPE(sv) != (svtype)SVTYPEMASK
		    && (sv->sv_flags & mask) == flags
		    && SvREFCNT(sv))
	    {
		(FCALL)(aTHX_ sv);
		++visited;
	    }
	}
    }
    return visited;
}
