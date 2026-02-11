object_type_get_name(const sge_object_type type)
{
   const char *ret = "unknown";

   DENTER(OBJECT_LAYER, "object_type_get_name");

   if (type >= 0 && type < SGE_TYPE_ALL) {
      ret = object_base[type].type_name;
   } else if (type == SGE_TYPE_ALL) {
      ret = "default";
   } else {
      ERROR((SGE_EVENT, MSG_OBJECT_INVALID_OBJECT_TYPE_SI, SGE_FUNC, type));
   }

   DRETURN(ret);
}
