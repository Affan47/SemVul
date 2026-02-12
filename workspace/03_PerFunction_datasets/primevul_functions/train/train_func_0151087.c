CelValue Produce(ProtobufWkt::Arena* arena) override {

    arena_ = arena;
    return CelValue::CreateMap(this);
  }
