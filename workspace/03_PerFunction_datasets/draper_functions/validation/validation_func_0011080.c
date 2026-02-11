make_reserved FCN((p))

scrap_pointer p C1("")
{
sixteen_bits tok_value= first_id(p->trans);

name_pointer pname= name_dir+tok_value-id_flag;

if(!tok_value||tok_value==050)
return;

if(DEFINED_TYPE(pname)==M_MACRO||DEFINED_TYPE(pname)==D_MACRO)
return;


for(;p<=scrp_ptr;p++)
{
if(p->cat==expr)
{
if(**(p->trans)==tok_value)
{
p->cat= int_like;
**(p->trans)+= res_flag-id_flag;
}
}
}

pname->ilk= int_like;
pname->reserved_word|= (boolean)language;

if(mark_defined.typedef_name)
{
pname->defined_in(language)= module_count;
SET_TYPE(pname,TYPEDEF_NAME);
}
}
