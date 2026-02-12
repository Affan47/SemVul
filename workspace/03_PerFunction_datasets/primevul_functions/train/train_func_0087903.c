pass_ipa_cp (gcc::context *ctxt)
    : ipa_opt_pass_d (pass_data_ipa_cp, ctxt,
		      ipcp_generate_summary,
		      ipcp_write_summary,
		      ipcp_read_summary,
		      ipcp_write_transformation_summaries,

		      ipcp_read_transformation_summaries,

		      NULL,
		      0,
		      ipcp_transform_function,
		      NULL)
  {}
