Statement_Ptr Expand::operator()(Comment_Ptr c)
  {
    if (ctx.output_style() == COMPRESSED) {


      if (!c->is_important()) return NULL;
    }
    eval.is_in_comment = true;
    Comment_Ptr rv = SASS_MEMORY_NEW(Comment, c->pstate(), Cast<String>(c->text()->perform(&eval)), c->is_important());
    eval.is_in_comment = false;

    return rv;
  }
