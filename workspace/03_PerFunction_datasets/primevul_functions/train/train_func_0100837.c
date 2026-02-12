static void test_double_free_in_vrend_renderer_blit_int_trigger()
{
   struct virgl_renderer_resource_create_args args;
   args.handle = 1;
   args.target = 2;
   args.format = VIRGL_FORMAT_Z32_UNORM;
   args.bind = VIRGL_BIND_SAMPLER_VIEW;
   args.width = 2;
   args.height = 2;
   args.depth = 1;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 1;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   args.handle = 6;
   args.target = 2;
   args.format = VIRGL_FORMAT_Z32_UNORM;
   args.bind = VIRGL_BIND_SAMPLER_VIEW;
   args.width = 2;
   args.height = 2;
   args.depth = 1;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 0;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   args.handle = 1;
   args.target = 7;
   args.format = VIRGL_FORMAT_Z32_UNORM;
   args.bind = 1;
   args.width = 6;
   args.height = 1;
   args.depth = 1;
   args.array_size = 2;
   args.last_level = 0;
   args.nr_samples = 0;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   uint32_t cmd[VIRGL_CMD_BLIT_SIZE + 1];

   int i = 0;
   cmd[i++] = VIRGL_CMD_BLIT_SIZE << 16 | 0 << 8 | VIRGL_CCMD_BLIT;
   cmd[i++] = 0x30 ;
   cmd[i++] = 1;
   cmd[i++] = 36;
   cmd[i++] = 6;
   cmd[i++] = 0;
   cmd[i++] = VIRGL_FORMAT_Z32_UNORM;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 6;
   cmd[i++] = 1;
   cmd[i++] = 1;
   cmd[i++] = 1;
   cmd[i++] = 0;
   cmd[i++] = VIRGL_FORMAT_Z32_UNORM;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 1;
   cmd[i++] = 2;
   cmd[i++] = 1;

   virgl_renderer_submit_cmd((void *) cmd, ctx_id, VIRGL_CMD_BLIT_SIZE + 1);
}
