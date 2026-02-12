static void test_heap_overflow_vrend_renderer_transfer_write_iov_compressed_tex()
{
   struct virgl_renderer_resource_create_args args;
   args.handle = 1;
   args.target = 5;
   args.format = 203;
   args.bind = 1;
   args.width = 100;
   args.height = 1;
   args.depth = 1;
   args.array_size = 0;
   args.last_level = 0;
   args.nr_samples = 0;
   args.flags = 1;

   virgl_renderer_resource_create(&args, NULL, 0);
   virgl_renderer_ctx_attach_resource(ctx_id, args.handle);

   char data[16];
   memset(data, 'A', 16);
   uint32_t cmd[11 + 4 +1];

   int i = 0;
   cmd[i++] = (11+4) << 16 | 0 << 8 | VIRGL_CCMD_RESOURCE_INLINE_WRITE;
   cmd[i++] = 1;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 135168;
   cmd[i++] = 655361;
   cmd[i++] = 1;
   cmd[i++] = 0;
   cmd[i++] = 0;
   cmd[i++] = 5;
   cmd[i++] = 1;
   cmd[i++] = 0;
   memcpy(&cmd[i], data, 16);

   virgl_renderer_submit_cmd((void *) cmd, ctx_id, 11 + 4 + 1);
}
