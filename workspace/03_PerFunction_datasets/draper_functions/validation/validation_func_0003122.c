evas_gl_string_query(Evas_GL *evas_gl, int name)
{
   MAGIC_CHECK(evas_gl, Evas_GL, MAGIC_EVAS_GL);
   return EINA_FALSE;
   MAGIC_CHECK_END();

   return (const char *)evas_gl->evas->engine.func->gl_string_query(evas_gl->evas->engine.data.output, name);
}
