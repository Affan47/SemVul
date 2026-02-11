pform_bind_attributes(map<perm_string,PExpr*>&attributes,
			   svector<named_pexpr_t*>*attr)
{
      if (attr == 0)
	    return;

      for (unsigned idx = 0 ;  idx < attr->count() ;  idx += 1) {
	    named_pexpr_t*tmp = (*attr)[idx];
	    attributes[tmp->name] = tmp->parm;
      }
      delete attr;
}
