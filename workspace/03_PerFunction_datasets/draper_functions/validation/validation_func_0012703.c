generate_code(state *start) {
  printf("#include \"crest.h\"\n\n");
  for(int i = 0; i < routes_count; i++)
    printf("extern void %s(crest_connection *connection);\n", end_states[i]->function_name);
  printf("\nint match_url(char *url, crest_connection *connection) {\n");
  switch_for_state(start);
  printf("}\n");
}
