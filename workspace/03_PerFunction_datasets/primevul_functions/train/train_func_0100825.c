static void  test_format_is_plain_nullptr_deref_trigger()
{
   struct virgl_renderer_resource_create_args args;
   args.handle = 10;
   args.target = 0;
   args.format = 126;
   args.bind = 2;
   args.width = 10;
   args.height = 10;
   args.depth = 10;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 0;
   args.flags = 0;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   uint32_t cmd[VIRGL_CMD_BLIT_SIZE + 1];

   int i = 0;
   cmd[i++] = VIRGL_CMD_BLIT_SIZE << 16 | 0 << 8 | VIRGL_CCMD_BLIT;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 10;
   cmd[i++] = 0;
   cmd[i++] = 445382656;
   cmd[i++] = 3;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 10;
   cmd[i++] = 0;
   cmd[i++] = 126;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 3;
   cmd[i++] = 0;

   virgl_renderer_submit_cmd((void *) cmd, ctx_id, VIRGL_CMD_BLIT_SIZE + 1);
}
