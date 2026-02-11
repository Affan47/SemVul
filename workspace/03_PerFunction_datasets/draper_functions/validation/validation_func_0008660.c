getOptionHelpName(const OptTable &Opts, OptSpecifier Id) {
  const Option O = Opts.getOption(Id);
  std::string Name = O.getPrefixedName();


  switch (O.getKind()) {
  case Option::GroupClass: case Option::InputClass: case Option::UnknownClass:
    llvm_unreachable("Invalid option with help text.");

  case Option::MultiArgClass:
    if (const char *MetaVarName = Opts.getOptionMetaVar(Id)) {

      Name += ' ';
      Name += MetaVarName;
    }
    else {

      for (unsigned i=0, e=O.getNumArgs(); i< e; ++i) {
        Name += " <value>";
      }
    }
    break;

  case Option::FlagClass:
    break;

  case Option::SeparateClass: case Option::JoinedOrSeparateClass:
  case Option::RemainingArgsClass:
    Name += ' ';

  case Option::JoinedClass: case Option::CommaJoinedClass:
  case Option::JoinedAndSeparateClass:
    if (const char *MetaVarName = Opts.getOptionMetaVar(Id))
      Name += MetaVarName;
    else
      Name += "<value>";
    break;
  }

  return Name;
}
