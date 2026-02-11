i_silence_test(root_block *root){
  int16_t *vec=rv(root);
  long end=re(root)-rb(root)-1;
  long j;


  for(j=end-1;j>=0;j--)if(vec[j]!=0)break;


  if(j<0 || end-j>MIN_SILENCE_BOUNDARY){
    root->silenceflag=1;
    root->silencebegin=rb(root)+j+1;
    if(root->silencebegin<root->returnedlimit)
      root->silencebegin=root->returnedlimit;
  }
}
