set_parameter(int param, string value)
{

  ECA_LOG_MSG(ECA_LOGGER::user_objects,
		"set_parameter " + label() + ".");


  if (param > static_cast<int>(params_rep.size())) params_rep.resize(param);

  if (param > 0) {
    params_rep[param - 1] = value;
  }

  if (param > AUDIO_IO_REVERSE::child_parameter_offset && init_rep == true) {
    child()->set_parameter(param - AUDIO_IO_REVERSE::child_parameter_offset, value);
  }
}
