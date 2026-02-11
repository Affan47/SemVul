optimize_specialization_lookup_p (tree tmpl)
{
  return (DECL_FUNCTION_TEMPLATE_P (tmpl)
	  && DECL_CLASS_SCOPE_P (tmpl)


	  && CLASS_TYPE_P (DECL_CONTEXT (tmpl))


	  && !CLASSTYPE_TEMPLATE_SPECIALIZATION (DECL_CONTEXT (tmpl))
	  && !DECL_MEMBER_TEMPLATE_P (tmpl)
	  && !DECL_CONV_FN_P (tmpl)


	  && !DECL_FRIEND_P (DECL_TEMPLATE_RESULT (tmpl)));
}
