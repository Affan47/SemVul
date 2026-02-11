C4_Shadow_create(gchar *name,
                    C4_State *src, C4_Transition *dst,
                    C4_StartFunc start_func, gchar *start_macro,
                    C4_EndFunc end_func, gchar *end_macro){
    register C4_Shadow *shadow = g_new0(C4_Shadow, 1);
    g_assert(name);
    g_assert(start_macro?(start_func?TRUE:FALSE):TRUE);
    g_assert(end_macro?(end_func?TRUE:FALSE):TRUE);
    if(start_func && (!start_macro))
        g_warning("Missing start_macro for Shadow: [%s]", name);
    if(end_func && (!end_macro))
        g_warning("Missing end_macro for Shadow: [%s]", name);
    shadow->name = g_strdup(name);
    g_assert(src);
    g_assert(dst);
    shadow->src_state_list = g_ptr_array_new();
    shadow->dst_transition_list = g_ptr_array_new();
    g_ptr_array_add(shadow->src_state_list, src);
    g_ptr_array_add(shadow->dst_transition_list, dst);
    shadow->start_func = start_func;
    if(start_macro)
        shadow->start_macro = g_strdup(start_macro);
    shadow->end_func = end_func;
    if(end_macro)
        shadow->end_macro = g_strdup(end_macro);
    g_ptr_array_add(src->src_shadow_list, shadow);
    g_ptr_array_add(dst->dst_shadow_list, shadow);
    return shadow;
    }
