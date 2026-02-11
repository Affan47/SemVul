nxt_color(int* FC, int FC_size, int* color_use_record){
  int i = 0;
  int nxt_color = 0;
  int max_use = 0;

  while (i<=FC_size){
    if (FC[i]==1 && color_use_record[i] >= max_use){
      nxt_color=i;
      max_use = color_use_record[i];
    }
    ++i;
  }

  return nxt_color;
}
