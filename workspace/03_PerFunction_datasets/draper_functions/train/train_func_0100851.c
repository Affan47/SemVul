test_interword_triphone(HTK_HMM_INFO *hmminfo, WORD_INFO *winfo)
{
  WORD_ID w;
  local_hmminfo = hmminfo;
  local_winfo = winfo;
  local_root = hmminfo->basephone.root;
  error_root = NULL;
  error_num = 0;

  printf("Inter-word triphone existence test...\n");
  for(w=0;w<winfo->num;w++) {
    current_w = w;
    if (winfo->wlen[w] > 1) {

      aptree_traverse_and_do(hmminfo->basephone.root, triphone_callback_normal);
    } else {

      aptree_traverse_and_do(hmminfo->basephone.root, triphone_callback_left);
    }
  }
  if (error_root == NULL) {
    printf("passed\n");
  } else {
    printf("following triphones are missing in HMMList:\n");
    aptree_traverse_and_do(error_root, print_error_callback);
    printf("total %d missing inter-word triphones\n", error_num);
  }
}
