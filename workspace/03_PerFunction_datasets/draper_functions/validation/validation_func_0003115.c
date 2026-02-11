soap_code(const struct soap_code_map *code_map, const char *str)
{ if (code_map && str)
  { while (code_map->string)
    { if (!strcmp(str, code_map->string))
        return code_map;
      code_map++;
    }
  }
  return NULL;
}
