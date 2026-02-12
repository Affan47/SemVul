static inline void fpstate_init_xstate(struct xregs_state *xsave)
{


	xsave->header.xcomp_bv = XCOMP_BV_COMPACTED_FORMAT | xfeatures_mask;
}
