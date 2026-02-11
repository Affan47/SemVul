read_entry_variables(struct emf_ObjectData_X* od,
                                int var_alloc_count, int var_size)
{

  int old_var_buffer_size, new_var_buffer_size;


  int var_alloc_size;


  int var_read_count;

  var_alloc_size = var_alloc_count * var_size;
  old_var_buffer_size = variableBufferSize;
  new_var_buffer_size = variableBufferSize + var_alloc_size;

  allocate_variable_buffer(old_var_buffer_size, new_var_buffer_size);

  currentBuffer = variableBuffer;
  currentBufferSize = variableBufferSize;
  currentBufferType = variableBufferType;


  int* read_sizes = new int[var_alloc_count];

  if ( !read_entry_variable_values(old_var_buffer_size, new_var_buffer_size,
                                   var_alloc_count, read_sizes, var_read_count)
     ) {


    sendMessage("\n");
    sendMessage("*** ERROR ***: When reading variable data for:");

    {
      strstream strm;
      strm << "OBJECT: " << od->object_name;

      if (od->object_id != -1) {
        strm << " " << od->object_id;
      }
      strm << "   FIELD:  " << od->field_name;
      strm << ends;
      sendMessage(strm.str());
    }

    {
      strstream strm;
      strm << "Expected size: " << var_alloc_size;
      strm << "      Actual size: " << var_read_count;
      strm << ends;
      sendMessage(strm.str());
    }
    sendMessage("\n");

    return false;

  } else {
#if 0

    cerr << endl;
    cerr << "Object: " << od->object_name;
    if (od->object_id != -1)
      cerr << " " << od->object_id;
    cerr << endl;
    cerr << "Field:  " << od->field_name << endl;
    cerr << "Datatype: " << od->data_type << endl;
    cerr << "Data: ";
    output_data(cerr, od->data_type, od->data);
    cerr << "Buffer: " << readBuffer << endl;
    cerr << "Hanging sep string: " << hangingSeparatedString << endl;
    cerr << "Contains sep string: " << containsSeparatedStrings << endl;
#endif
  }

  nofVariableValues += var_read_count;

  int var_read_size = 0;

  for (int i = 0; i < var_read_count; i++)
    var_read_size += read_sizes[i];


  if ( var_read_size < var_alloc_size ) {
    new_var_buffer_size += var_read_size - var_alloc_size;
    allocate_variable_buffer(new_var_buffer_size, new_var_buffer_size);
  }
  update_variable_lengths(var_read_count, read_sizes);


  return true;
}
