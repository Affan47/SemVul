demand_type(class_id type)
  {
      type_index_t::iterator p = type_position(type);

      if (p != type_index().end() && tuples::get<ksrc_static_t>(*p) == type)
          return p;

      vertex_t v = add_vertex(full_graph().topology());
      vertex_t v2 = add_vertex(up_graph().topology());
      unused_variable(v2);
      assert(v == v2);
      return type_index().insert(p, boost::make_tuple(type, v, dynamic_id_function(0)));
  }
