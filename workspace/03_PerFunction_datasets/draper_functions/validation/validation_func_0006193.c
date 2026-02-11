_mesa_ClearDepth( GLclampd depth )
{
   GET_CURRENT_CONTEXT(ctx);

   if (MESA_VERBOSE & VERBOSE_API)
      _mesa_debug(ctx, "glClearDepth(%f)\n", depth);

   ctx->Depth.Clear = CLAMP( depth, 0.0, 1.0 );
}
