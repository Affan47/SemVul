syck_seq_style_set(VALUE self, VALUE style)
{
    SyckNode *node;
    Data_Get_Struct( self, SyckNode, node );

    if ( style == sym_inline )
    {
        node->data.list->style = seq_inline;
    }
    else
    {
        node->data.list->style = seq_none;
    }

    rb_iv_set( self, "@style", style );
    return self;
}
