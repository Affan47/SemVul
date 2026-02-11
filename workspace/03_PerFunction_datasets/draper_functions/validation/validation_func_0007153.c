syck_seq_initialize(VALUE self, VALUE type_id, VALUE val, VALUE style)
{
    SyckNode *node;
    Data_Get_Struct( self, SyckNode, node );

    rb_iv_set( self, "@kind", sym_seq );
    rb_funcall( self, s_type_id_set, 1, type_id );
    rb_funcall( self, s_value_set, 1, val );
    rb_funcall( self, s_style_set, 1, style );
    return self;
}
