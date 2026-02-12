static void test_blit_info_format_check_null_format()
{
   struct virgl_renderer_resource_create_args args;
   args.handle = 10;
   args.target = 3;
   args.format = 10;
   args.bind = 10;
   args.width = 2;
   args.height = 1;
   args.depth = 1;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 0;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   uint32_t cmd[VIRGL_CMD_BLIT_SIZE + 1];

   int i = 0;
   cmd[i++] = VIRGL_CMD_BLIT_SIZE << 16 | 0 << 8 | VIRGL_CCMD_BLIT;
   cmd[i++] = 0x8000001;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 10;
   cmd[i++] = 0;
   cmd[i++] = 1;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 10;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;

   virgl_renderer_submit_cmd((void *) cmd, ctx_id, VIRGL_CMD_BLIT_SIZE + 1);
}
