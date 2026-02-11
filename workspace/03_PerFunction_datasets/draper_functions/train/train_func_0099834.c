gl_mini_preview_finalize (GObject *object)
{
        glMiniPreview *this = GL_MINI_PREVIEW (object);

        gl_debug (DEBUG_MINI_PREVIEW, "START");

        g_return_if_fail (object != NULL);
        g_return_if_fail (GL_IS_MINI_PREVIEW (object));

        if (this->priv->label)
        {
                g_object_unref (this->priv->label);
        }
        lgl_template_free (this->priv->template);
        g_free (this->priv->centers);
        g_free (this->priv);

        G_OBJECT_CLASS (gl_mini_preview_parent_class)->finalize (object);

        gl_debug (DEBUG_MINI_PREVIEW, "END");
}
