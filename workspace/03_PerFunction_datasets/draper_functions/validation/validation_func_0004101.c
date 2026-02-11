pform_set_attrib(perm_string name, perm_string key, char*value)
{
      if (PWire*cur = lexical_scope->wires_find(name)) {
	    cur->attributes[key] = new PEString(value);

      } else if (PGate*curg = pform_cur_module->get_gate(name)) {
	    curg->attributes[key] = new PEString(value);

      } else {
	    delete[] value;
	    VLerror("Unable to match name for setting attribute.");

      }
}
