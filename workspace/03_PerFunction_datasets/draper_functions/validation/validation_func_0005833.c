f_ID_of_direct_decl(ac_direct_declarator d)
{{
	ac_direct_declarator kc_selvar_0_1 = phylum_cast<ac_direct_declarator>(d);
	if ((kc_selvar_0_1->prod_sel() == sel_AcQualifiedDeclProto)) {
	    const ac_direct_declarator a_d = phylum_cast<const impl_ac_direct_declarator_AcQualifiedDeclProto*>(kc_selvar_0_1)->ac_direct_declarator_1;
	    return f_ID_of_direct_decl( a_d );
	    	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_AcDirectDeclProto)) {
	    const ac_direct_declarator a_d = phylum_cast<const impl_ac_direct_declarator_AcDirectDeclProto*>(kc_selvar_0_1)->ac_direct_declarator_1;
	    return f_ID_of_direct_decl( a_d );
	    	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_AcDirectDeclArray)) {
	    const ac_direct_declarator a_d = phylum_cast<const impl_ac_direct_declarator_AcDirectDeclArray*>(kc_selvar_0_1)->ac_direct_declarator_1;
	    return f_ID_of_direct_decl( a_d );
	    	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_AcDirectDeclPack)) {
	    const ac_declarator a_d = phylum_cast<const impl_ac_direct_declarator_AcDirectDeclPack*>(kc_selvar_0_1)->ac_declarator_1;
	    return f_ID_of_declarator( a_d );
	    	} else
	    if ((kc_selvar_0_1->prod_sel() == sel_AcDirectDeclId)) {
	    const ID i = phylum_cast<const impl_ac_direct_declarator_AcDirectDeclId*>(kc_selvar_0_1)->ID_1;
	    return i;
	    	} else
	{
	    return f_emptyId();
	}
    }

}
