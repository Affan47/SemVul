_playback_copy_to_current(struct gl_context *ctx,
                          const struct vbo_save_vertex_list *node)
{
   struct vbo_context *vbo = vbo_context(ctx);
   GLfloat vertex[VBO_ATTRIB_MAX * 4];
   GLfloat *data;
   GLuint i, offset;

   if (node->current_size == 0)
      return;

   if (node->current_data) {
      data = node->current_data;
   }
   else {
      data = vertex;

      if (node->count)
         offset = (node->buffer_offset +
                   (node->count-1) * node->vertex_size * sizeof(GLfloat));
      else
         offset = node->buffer_offset;

      ctx->Driver.GetBufferSubData( ctx, offset,
                                    node->vertex_size * sizeof(GLfloat),
                                    data, node->vertex_store->bufferobj );

      data += node->attrsz[0];
   }

   for (i = VBO_ATTRIB_POS+1 ; i < VBO_ATTRIB_MAX ; i++) {
      if (node->attrsz[i]) {
	 GLfloat *current = (GLfloat *)vbo->currval[i].Ptr;
         GLfloat tmp[4];

         COPY_CLEAN_4V_TYPE_AS_FLOAT(tmp,
                                     node->attrsz[i],
                                     data,
                                     node->attrtype[i]);

         if (node->attrtype[i] != vbo->currval[i].Type ||
             memcmp(current, tmp, 4 * sizeof(GLfloat)) != 0) {
            memcpy(current, tmp, 4 * sizeof(GLfloat));

            vbo->currval[i].Size = node->attrsz[i];
            vbo->currval[i]._ElementSize = vbo->currval[i].Size * sizeof(GLfloat);
            vbo->currval[i].Type = node->attrtype[i];
            vbo->currval[i].Integer =
                  vbo_attrtype_to_integer_flag(node->attrtype[i]);

            if (i >= VBO_ATTRIB_FIRST_MATERIAL &&
                i <= VBO_ATTRIB_LAST_MATERIAL)
               ctx->NewState |= _NEW_LIGHT;

            ctx->NewState |= _NEW_CURRENT_ATTRIB;
         }

	 data += node->attrsz[i];
      }
   }


   if (ctx->Light.ColorMaterialEnabled) {
      _mesa_update_color_material(ctx, ctx->Current.Attrib[VBO_ATTRIB_COLOR0]);
   }


   if (node->prim_count) {
      const struct _mesa_prim *prim = &node->prim[node->prim_count - 1];
      if (prim->end)
	 ctx->Driver.CurrentExecPrimitive = PRIM_OUTSIDE_BEGIN_END;
      else
	 ctx->Driver.CurrentExecPrimitive = prim->mode;
   }
}
