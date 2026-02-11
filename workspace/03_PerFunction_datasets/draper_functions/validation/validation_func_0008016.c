elm_transit_effect_blend_add(Elm_Transit *transit)
{
   ELM_TRANSIT_CHECK_OR_RETURN(transit, NULL);
   Elm_Transit_Effect *effect = _transit_effect_blend_context_new();

   if (!effect)
     {
        ERR("Failed to allocate blend effect! : transit=%p", transit);
        return NULL;
     }
   elm_transit_effect_add(transit,
                          _transit_effect_blend_op, effect,
                          _transit_effect_blend_context_free);
   return effect;
}
