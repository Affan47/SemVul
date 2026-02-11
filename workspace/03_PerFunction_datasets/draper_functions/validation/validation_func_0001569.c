write_dt_kick_ppcmodule(csbe_context *cx)
{
    csbe_printf(cx, "if( dtu_count[%d][0] >= DTU_MIN_COUNT-1 && "
		    "dtu_count[%d][0] < DTU_MAX_COUNT ){\n",
		get_current_pe_number(),
		get_current_pe_number()
	);
    csbe_printf(cx, "dtu_clock[%d][dtu_count[%d][0]-DTU_MIN_COUNT+1] = "
		    "get_ppc_clock(%d);\n",
		get_current_pe_number(),
		get_current_pe_number(),
		get_current_pe_number()
	);
    csbe_printf(cx, "dtu_count[%d][0]++;\n", get_current_pe_number());
    if (opt_count_checkftime) {
	csbe_printf(cx, "ppc_checkf_skip[%d] = 0;\n",
		    get_current_pe_number()
	    );
    }
    csbe_printf(cx, "}\n");
}
