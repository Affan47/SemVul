def_intrins_name(Token *id)
#else
def_intrins_name(id)
	Token *id;
#endif
{
	int h=id->value.integer;
	Lsymtab *symt;

	if( (symt = hashtab[h].loc_symtab) == NULL){
	   symt = install_local(h,type_UNDECL,class_SUBPROGRAM);
	   symt->line_declared = id->line_num;
	   symt->file_declared = inctable_index;
	   symt->info.toklist = NULL;
        }
	else {

	  if(storage_class_of(symt->type) == class_VAR) {
	    symt->info.toklist = NULL;
	  }

	  symt->type = type_byte(class_SUBPROGRAM,datatype_of(symt->type));
	}


	if(symt->external){
	    syntax_error(id->line_num,id->col_num,
	       "Cannot declare same subprogram both intrinsic and external:");
	    msg_tail(symt->name);
	}
	else{
	  IntrinsInfo *defn;
	  symt->declared_intrinsic = TRUE;
	  if( (defn=find_intrinsic(symt->name)) == NULL ) {
	     if(misc_warn) {
	       warning(id->line_num,id->col_num,
			"Unknown intrinsic function: ");
	       msg_tail(symt->name);
	       msg_tail("Treated as if user-defined");
	     }

	     def_ext_name(id);
	     return;
	   }
	   else {


	     symt->intrinsic = TRUE;
	     symt->info.intrins_info = defn;
	   }
	}
	symt->declared_external = TRUE;
}
