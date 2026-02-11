gl_normal_io(GetLine *gl)
{
  sigset_t oldset;
  int status;


  if(!gl) {
    errno = EINVAL;
    return 1;
  };


  if(gl_mask_signals(gl, &oldset))
    return 1;


  status = _gl_normal_io(gl);


  gl_unmask_signals(gl, &oldset);
  return status;
}
