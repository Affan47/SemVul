explicit MatrixDiagOp(OpKernelConstruction* context) : OpKernel(context) {

    if (context->HasAttr("align")) {
      functor::ReadAlignment(context, &left_align_superdiagonal_,
                             &left_align_subdiagonal_);
    }
  }
