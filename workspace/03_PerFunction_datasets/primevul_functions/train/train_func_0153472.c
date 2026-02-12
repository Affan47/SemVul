node_extended_grapheme_cluster(Node** np, ScanEnv* env)
{
  Node* tmp = NULL;
  Node* np1 = NULL;
  Node* top_alt = NULL;
  int r = 0;
  int num1;
  int i;
  int any_target_position;
  UChar buf[ONIGENC_CODE_TO_MBC_MAXLEN * 2];
  OnigOptionType option;


  Node *node_common[NODE_COMMON_SIZE];
  Node **alts = node_common+0;

  for (i=0; i<NODE_COMMON_SIZE; i++)
    node_common[i] = NULL_NODE;


  r = ONIGENC_CODE_TO_MBC(env->enc, 0x0D, buf);
  if (r < 0) goto err;
  num1 = r;
  r = ONIGENC_CODE_TO_MBC(env->enc, 0x0A, buf + num1);
  if (r < 0) goto err;
  alts[0] = node_new_str_raw(buf, buf + num1 + r);
  if (IS_NULL(alts[0])) goto err;

#ifdef USE_UNICODE_PROPERTIES
  if (ONIGENC_IS_UNICODE(env->enc)) {
    CClassNode* cc;

    if (propname2ctype(env, "Grapheme_Cluster_Break=Extend") < 0) goto err;


    alts[1] = node_new_cclass();
    if (IS_NULL(alts[1])) goto err;
    cc = NCCLASS(alts[1]);
    R_ERR(add_property_to_cc(cc, "Grapheme_Cluster_Break=Control", 0, env));
    if (ONIGENC_MBC_MINLEN(env->enc) > 1) {
      R_ERR(add_code_range(&(cc->mbuf), env, 0x000A, 0x000A));
      R_ERR(add_code_range(&(cc->mbuf), env, 0x000D, 0x000D));
    }
    else {
      BITSET_SET_BIT(cc->bs, 0x0a);
      BITSET_SET_BIT(cc->bs, 0x0d);
    }


    {
      Node **list = alts + 3;


      R_ERR(quantify_property_node(list+0, env, "Grapheme_Cluster_Break=Prepend", '*'));


      {
        Node **core_alts = list + 2;


        {
          Node **H_list = core_alts + 1;
          R_ERR(quantify_property_node(H_list+0, env, "Grapheme_Cluster_Break=L", '*'));


          {
            Node **H_alt2 = H_list + 2;
            R_ERR(quantify_property_node(H_alt2+0, env, "Grapheme_Cluster_Break=V", '+'));


            {
              Node **H_list2 = H_alt2 + 2;

              R_ERR(create_property_node(H_list2+0, env, "Grapheme_Cluster_Break=LV"));
              R_ERR(quantify_property_node(H_list2+1, env, "Grapheme_Cluster_Break=V", '*'));
              R_ERR(create_node_from_array(LIST, H_alt2+1, H_list2));
            }

            R_ERR(create_property_node(H_alt2+2, env, "Grapheme_Cluster_Break=LVT"));
            R_ERR(create_node_from_array(ALT, H_list+1, H_alt2));
          }

          R_ERR(quantify_property_node(H_list+2, env, "Grapheme_Cluster_Break=T", '*'));
          R_ERR(create_node_from_array(LIST, core_alts+0, H_list));
        }

        R_ERR(quantify_property_node(core_alts+1, env, "Grapheme_Cluster_Break=L", '+'));
        R_ERR(quantify_property_node(core_alts+2, env, "Grapheme_Cluster_Break=T", '+'));


        R_ERR(quantify_property_node(core_alts+3, env, "Regional_Indicator", '2'));


        {
          Node **XP_list = core_alts + 5;
          R_ERR(create_property_node(XP_list+0, env, "Extended_Pictographic"));


          {
            Node **Ex_list = XP_list + 2;

            R_ERR(quantify_property_node(Ex_list+0, env, "Grapheme_Cluster_Break=Extend", '*'));


            r = ONIGENC_CODE_TO_MBC(env->enc, 0x200D, buf);
            if (r < 0) goto err;
            Ex_list[1] = node_new_str_raw(buf, buf + r);
            if (IS_NULL(Ex_list[1])) goto err;

            R_ERR(create_property_node(Ex_list+2, env, "Extended_Pictographic"));
            R_ERR(create_node_from_array(LIST, XP_list+1, Ex_list));
          }
          R_ERR(quantify_node(XP_list+1, 0, REPEAT_INFINITE));

          R_ERR(create_node_from_array(LIST, core_alts+4, XP_list));
        }


        core_alts[5] = node_new_cclass();
        if (IS_NULL(core_alts[5])) goto err;
        cc = NCCLASS(core_alts[5]);
        if (ONIGENC_MBC_MINLEN(env->enc) > 1) {
          BBuf *inverted_buf = NULL;


          R_ERR(add_property_to_cc(cc, "Grapheme_Cluster_Break=Control", 0, env));
          R_ERR(add_code_range(&(cc->mbuf), env, 0x000A, 0x000A));
          R_ERR(add_code_range(&(cc->mbuf), env, 0x000D, 0x000D));
          R_ERR(not_code_range_buf(env->enc, cc->mbuf, &inverted_buf, env));
          cc->mbuf = inverted_buf;
        }
        else {
          R_ERR(add_property_to_cc(cc, "Grapheme_Cluster_Break=Control", 1, env));
          BITSET_CLEAR_BIT(cc->bs, 0x0a);
          BITSET_CLEAR_BIT(cc->bs, 0x0d);
        }

        R_ERR(create_node_from_array(ALT, list+1, core_alts));
      }


      R_ERR(create_property_node(list+2, env, "Grapheme_Cluster_Break=Extend"));
      cc = NCCLASS(list[2]);
      R_ERR(add_property_to_cc(cc, "Grapheme_Cluster_Break=SpacingMark", 0, env));
      R_ERR(add_code_range(&(cc->mbuf), env, 0x200D, 0x200D));
      R_ERR(quantify_node(list+2, 0, REPEAT_INFINITE));

      R_ERR(create_node_from_array(LIST, alts+2, list));
    }

    any_target_position = 3;
  }
  else
#endif
  {
    any_target_position = 1;
  }


  np1 = node_new_anychar();
  if (IS_NULL(np1)) goto err;

  option = env->option;
  ONOFF(option, ONIG_OPTION_MULTILINE, 0);
  tmp = node_new_option(option);
  if (IS_NULL(tmp)) goto err;
  NENCLOSE(tmp)->target = np1;
  alts[any_target_position] = tmp;
  np1 = NULL;

  R_ERR(create_node_from_array(ALT, &top_alt, alts));


  tmp = node_new_enclose(ENCLOSE_STOP_BACKTRACK);
  if (IS_NULL(tmp)) goto err;
  NENCLOSE(tmp)->target = top_alt;
  np1 = tmp;

#ifdef USE_UNICODE_PROPERTIES
  if (ONIGENC_IS_UNICODE(env->enc)) {

    option = env->option;
    ONOFF(option, ONIG_OPTION_IGNORECASE, 1);
    *np = node_new_option(option);
    if (IS_NULL(*np)) goto err;
    NENCLOSE(*np)->target = np1;
  }
  else
#endif
  {
    *np = np1;
  }
  return ONIG_NORMAL;

 err:
  onig_node_free(np1);
  for (i=0; i<NODE_COMMON_SIZE; i++)
    onig_node_free(node_common[i]);
  return (r == 0) ? ONIGERR_MEMORY : r;
}
