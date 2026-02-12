node_extended_grapheme_cluster(Node** np, ScanEnv* env)
{
  Node* tmp = NULL;
  Node* np1 = NULL;
  Node* list = NULL;
  Node* list2 = NULL;
  Node* alt = NULL;
  Node* alt2 = NULL;
  BBuf *pbuf1 = NULL;
  int r = 0;
  int num1;
  UChar buf[ONIGENC_CODE_TO_MBC_MAXLEN * 2];
  OnigOptionType option;

#ifdef USE_UNICODE_PROPERTIES
  if (ONIGENC_IS_UNICODE(env->enc)) {

    CClassNode* cc;
    OnigCodePoint sb_out = (ONIGENC_MBC_MINLEN(env->enc) > 1) ? 0x00 : 0x80;
    int extend = propname2ctype(env, "Grapheme_Cluster_Break=Extend");


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, extend, 0, 0, env);
    if (r != 0) goto err;
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=SpacingMark"), 0, 0, env);
    if (r != 0) goto err;
    r = add_code_range(&(cc->mbuf), env, 0x200D, 0x200D);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=Control"), 1, 0, env);
    if (r != 0) goto err;
    if (ONIGENC_MBC_MINLEN(env->enc) > 1) {
      BBuf *pbuf2 = NULL;
      r = add_code_range(&pbuf1, env, 0x0a, 0x0a);
      if (r != 0) goto err;
      r = add_code_range(&pbuf1, env, 0x0d, 0x0d);
      if (r != 0) goto err;
      r = and_code_range_buf(cc->mbuf, 0, pbuf1, 1, &pbuf2, env);
      if (r != 0) {
	bbuf_free(pbuf2);
	goto err;
      }
      bbuf_free(pbuf1);
      pbuf1 = NULL;
      bbuf_free(cc->mbuf);
      cc->mbuf = pbuf2;
    }
    else {
      BITSET_CLEAR_BIT(cc->bs, 0x0a);
      BITSET_CLEAR_BIT(cc->bs, 0x0d);
    }

    tmp = onig_node_new_alt(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=T"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(1, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = onig_node_new_alt(np1, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=L"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(1, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = onig_node_new_alt(np1, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=T"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=LVT"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=L"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=T"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=V"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=LV"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=L"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=T"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=V"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(1, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=L"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Modifier"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, 1, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, extend, 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Base_GAZ"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    alt2 = tmp;
    list2 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, extend, 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    {
      static const OnigCodePoint ranges[] = {
	13,
	0x1F308, 0x1F308,
	0x1F33E, 0x1F33E,
	0x1F373, 0x1F373,
	0x1F393, 0x1F393,
	0x1F3A4, 0x1F3A4,
	0x1F3A8, 0x1F3A8,
	0x1F3EB, 0x1F3EB,
	0x1F3ED, 0x1F3ED,
	0x1F4BB, 0x1F4BC,
	0x1F527, 0x1F527,
	0x1F52C, 0x1F52C,
	0x1F680, 0x1F680,
	0x1F692, 0x1F692,
      };
      r = add_ctype_to_cc_by_range(cc, -1, 0, env, sb_out, ranges);
      if (r != 0) goto err;
    }
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=Glue_After_Zwj"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt2);
    if (IS_NULL(tmp)) goto err;
    alt2 = tmp;
    list2 = NULL;


    r = ONIGENC_CODE_TO_MBC(env->enc, 0xfe0f, buf);
    if (r < 0) goto err;
    np1 = node_new_str_raw(buf, buf + r);
    if (IS_NULL(np1)) goto err;

    tmp = node_new_quantifier(0, 1, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    {
      static const OnigCodePoint ranges[] = {
	4,
	0x2640, 0x2640,
	0x2642, 0x2642,
	0x2695, 0x2696,
	0x2708, 0x2708,
      };
      r = add_ctype_to_cc_by_range(cc, -1, 0, env, sb_out, ranges);
      if (r != 0) goto err;
    }

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt2);
    if (IS_NULL(tmp)) goto err;
    alt2 = tmp;
    list2 = NULL;

    tmp = node_new_list(alt2, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    alt2 = NULL;


    r = ONIGENC_CODE_TO_MBC(env->enc, 0x200D, buf);
    if (r < 0) goto err;
    np1 = node_new_str_raw(buf, buf + r);
    if (IS_NULL(np1)) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = list2;
    np1 = tmp;
    list2 = NULL;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Modifier"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, 1, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, extend, 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    {
      static const OnigCodePoint ranges[] = {
	8,
	0x1F3C2, 0x1F3C2,
	0x1F3C7, 0x1F3C7,
	0x1F3CC, 0x1F3CC,
	0x1F3F3, 0x1F3F3,
	0x1F441, 0x1F441,
	0x1F46F, 0x1F46F,
	0x1F574, 0x1F574,
	0x1F6CC, 0x1F6CC,
      };
      r = add_ctype_to_cc_by_range(cc, -1, 0, env, sb_out, ranges);
      if (r != 0) goto err;
    }
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Base"), 0, 0, env);
    if (r != 0) goto err;
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Base_GAZ"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Modifier"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, 1, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=Glue_After_Zwj"), 0, 0, env);
    if (r != 0) goto err;
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=E_Base_GAZ"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    r = ONIGENC_CODE_TO_MBC(env->enc, 0x200D, buf);
    if (r < 0) goto err;
    np1 = node_new_str_raw(buf, buf + r);
    if (IS_NULL(np1)) goto err;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_code_range(&(cc->mbuf), env, 0x1F1E6, 0x1F1FF);
    if (r != 0) goto err;

    tmp = node_new_quantifier(2, 2, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;

    tmp = node_new_list(alt, list);
    if (IS_NULL(tmp)) goto err;
    list = tmp;
    alt = NULL;


    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=Prepend"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(0, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list);
    if (IS_NULL(tmp)) goto err;
    list = tmp;
    np1 = NULL;


    np1 = node_new_anychar();
    if (IS_NULL(np1)) goto err;

    option = env->option;
    ONOFF(option, ONIG_OPTION_MULTILINE, 0);
    tmp = node_new_option(option);
    if (IS_NULL(tmp)) goto err;
    NENCLOSE(tmp)->target = np1;
    np1 = tmp;

    tmp = onig_node_new_alt(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    np1 = NULL;


    r = ONIGENC_CODE_TO_MBC(env->enc, 0x200D, buf);
    if (r < 0) goto err;
    np1 = node_new_str_raw(buf, buf + r);
    if (IS_NULL(np1)) goto err;

    tmp = node_new_quantifier(0, 1, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, NULL_NODE);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    np1 = node_new_cclass();
    if (IS_NULL(np1)) goto err;
    cc = NCCLASS(np1);
    r = add_ctype_to_cc(cc, propname2ctype(env, "Grapheme_Cluster_Break=Prepend"), 0, 0, env);
    if (r != 0) goto err;

    tmp = node_new_quantifier(1, REPEAT_INFINITE, 0);
    if (IS_NULL(tmp)) goto err;
    NQTFR(tmp)->target = np1;
    np1 = tmp;

    tmp = node_new_list(np1, list2);
    if (IS_NULL(tmp)) goto err;
    list2 = tmp;
    np1 = NULL;

    tmp = onig_node_new_alt(list2, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list2 = NULL;

    tmp = onig_node_new_alt(list, alt);
    if (IS_NULL(tmp)) goto err;
    alt = tmp;
    list = NULL;
  }
  else
#endif
  {

    np1 = node_new_anychar();
    if (IS_NULL(np1)) goto err;

    option = env->option;
    ONOFF(option, ONIG_OPTION_MULTILINE, 0);
    tmp = node_new_option(option);
    if (IS_NULL(tmp)) goto err;
    NENCLOSE(tmp)->target = np1;
    np1 = tmp;

    alt = onig_node_new_alt(np1, NULL_NODE);
    if (IS_NULL(alt)) goto err;
    np1 = NULL;
  }


  r = ONIGENC_CODE_TO_MBC(env->enc, 0x0D, buf);
  if (r < 0) goto err;
  num1 = r;
  r = ONIGENC_CODE_TO_MBC(env->enc, 0x0A, buf + num1);
  if (r < 0) goto err;
  np1 = node_new_str_raw(buf, buf + num1 + r);
  if (IS_NULL(np1)) goto err;

  tmp = onig_node_new_alt(np1, alt);
  if (IS_NULL(tmp)) goto err;
  alt = tmp;
  np1 = NULL;


  tmp = node_new_enclose(ENCLOSE_STOP_BACKTRACK);
  if (IS_NULL(tmp)) goto err;
  NENCLOSE(tmp)->target = alt;
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
  onig_node_free(list);
  onig_node_free(list2);
  onig_node_free(alt);
  onig_node_free(alt2);
  bbuf_free(pbuf1);
  return (r == 0) ? ONIGERR_MEMORY : r;
}
