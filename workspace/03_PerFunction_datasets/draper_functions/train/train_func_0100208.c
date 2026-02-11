CreateLogOp(OpRcPtrVec & ops,
                     const float * k,
                     const float * m,
                     const float * b,
                     const float * base,
                     const float * kb,
                     TransformDirection direction)
    {
        ops.push_back( LogOpRcPtr(new LogOp(k, m, b, base, kb, direction)) );
    }
