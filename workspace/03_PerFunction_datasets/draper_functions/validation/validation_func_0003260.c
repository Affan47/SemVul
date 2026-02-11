getCppName(Type* Ty) {
  switch (Ty->getTypeID()) {
  default:
    break;
  case Type::VoidTyID:
    return "Type::getVoidTy(mod->getContext())";
  case Type::IntegerTyID: {
    unsigned BitWidth = cast<IntegerType>(Ty)->getBitWidth();
    return "IntegerType::get(mod->getContext(), " + utostr(BitWidth) + ")";
  }
  case Type::X86_FP80TyID:
    return "Type::getX86_FP80Ty(mod->getContext())";
  case Type::FloatTyID:
    return "Type::getFloatTy(mod->getContext())";
  case Type::DoubleTyID:
    return "Type::getDoubleTy(mod->getContext())";
  case Type::LabelTyID:
    return "Type::getLabelTy(mod->getContext())";
  case Type::X86_MMXTyID:
    return "Type::getX86_MMXTy(mod->getContext())";
  }


  TypeMap::iterator I = TypeNames.find(Ty);
  if (I != TypeNames.end())
    return I->second;


  const char* prefix = nullptr;
  switch (Ty->getTypeID()) {
  case Type::FunctionTyID:    prefix = "FuncTy_"; break;
  case Type::StructTyID:      prefix = "StructTy_"; break;
  case Type::ArrayTyID:       prefix = "ArrayTy_"; break;
  case Type::PointerTyID:     prefix = "PointerTy_"; break;
  case Type::VectorTyID:      prefix = "VectorTy_"; break;
  default:                    prefix = "OtherTy_"; break;
  }


  std::string name;
  if (StructType *STy = dyn_cast<StructType>(Ty))
    if (STy->hasName())
      name = STy->getName();

  if (name.empty())
    name = utostr(uniqueNum++);

  name = std::string(prefix) + name;
  sanitize(name);


  return TypeNames[Ty] = name;
}
