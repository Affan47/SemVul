_e_imc_file_name_new_get(void)
{
   char path[PATH_MAX];
   int i;

   for (i = 0; i < 32; i++)
     {
        snprintf(path, sizeof(path), "%s/new_input_method-%02d.imc",
                 e_intl_imc_personal_path_get(), i);
        if (!ecore_file_exists(path))
          return eina_stringshare_add(path);
     }

   return NULL;
}
