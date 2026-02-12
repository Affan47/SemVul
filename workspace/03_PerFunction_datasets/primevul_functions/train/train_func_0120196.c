Block_Ptr Expand::operator()(Block_Ptr b)
  {


    Env env(environment());

    Block_Obj bb = SASS_MEMORY_NEW(Block,
                                b->pstate(),
                                b->length(),
                                b->is_root());

    this->block_stack.push_back(bb);
    this->env_stack.push_back(&env);


    this->append_block(b);

    this->block_stack.pop_back();
    this->env_stack.pop_back();

    return bb.detach();
  }
