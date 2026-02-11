clone(void) const
{
  AUDIO_IO_REVERSE* target = new AUDIO_IO_REVERSE();
  for(int n = 0; n < number_of_params(); n++) {
    target->set_parameter(n + 1, get_parameter(n + 1));
  }
  return target;
}
