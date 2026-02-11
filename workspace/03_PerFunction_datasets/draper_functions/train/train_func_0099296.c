gl_label_is_selection_atomic (glLabel       *label)
{
        GList         *p;
        glLabelObject *object;
        gint           n_selected = 0;

        for ( p = label->priv->object_list; p != NULL; p = p->next )
        {
                object = GL_LABEL_OBJECT (p->data);

                if ( gl_label_object_is_selected (object) )
                {
                        n_selected++;

                        if (n_selected > 1)
                        {
                                return FALSE;
                        }
                }
        }

        return (n_selected == 1);
}
