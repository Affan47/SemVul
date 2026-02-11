try_vbo_merge(struct vbo_exec_context *exec)
{
   struct _mesa_prim *cur =  &exec->vtx.prim[exec->vtx.prim_count - 1];

   assert(exec->vtx.prim_count >= 1);

   vbo_try_prim_conversion(cur);

   if (exec->vtx.prim_count >= 2) {
      struct _mesa_prim *prev = &exec->vtx.prim[exec->vtx.prim_count - 2];
      assert(prev == cur - 1);

      if (vbo_can_merge_prims(prev, cur)) {
         assert(cur->begin);
         assert(cur->end);
         assert(prev->begin);
         assert(prev->end);
         vbo_merge_prims(prev, cur);
         exec->vtx.prim_count--;
      }
   }
}
