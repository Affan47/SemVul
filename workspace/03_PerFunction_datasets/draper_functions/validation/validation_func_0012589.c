brw_upload_gs_pull_constants(struct brw_context *brw)
{
   struct brw_stage_state *stage_state = &brw->gs.base;


   struct brw_geometry_program *gp =
      (struct brw_geometry_program *) brw->geometry_program;

   if (!gp)
      return;


   const struct brw_vec4_prog_data *prog_data = &brw->gs.prog_data->base;


   brw_upload_vec4_pull_constants(brw, BRW_NEW_GS_CONSTBUF, &gp->program.Base,
                                  stage_state, prog_data);
}
