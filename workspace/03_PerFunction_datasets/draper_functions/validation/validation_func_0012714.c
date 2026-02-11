Init(const StringPiece& pattern, const Options& options) {
  mutex_ = new Mutex;
  pattern_ = pattern.as_string();
  options_.Copy(options);
  InitEmpty();
  error_ = empty_string;
  error_code_ = NoError;
  suffix_regexp_ = NULL;
  entire_regexp_ = NULL;
  prog_ = NULL;
  rprog_ = NULL;
  named_groups_ = NULL;
  group_names_ = NULL;
  num_captures_ = -1;

  RegexpStatus status;
  entire_regexp_ = Regexp::Parse(
    pattern_,
    static_cast<Regexp::ParseFlags>(options_.ParseFlags()),
    &status);
  if (entire_regexp_ == NULL) {
    if (error_ == empty_string)
      error_ = new string(status.Text());
    if (options_.log_errors()) {
      LOG(ERROR) << "Error parsing '" << trunc(pattern_) << "': "
                 << status.Text();
    }
    error_arg_ = status.error_arg().as_string();
    error_code_ = RegexpErrorToRE2(status.code());
    return;
  }

  prefix_.clear();
  prefix_foldcase_ = false;
  re2::Regexp* suffix;
  if (entire_regexp_->RequiredPrefix(&prefix_, &prefix_foldcase_, &suffix))
    suffix_regexp_ = suffix;
  else
    suffix_regexp_ = entire_regexp_->Incref();


  prog_ = suffix_regexp_->CompileToProg(options_.max_mem()*2/3);
  if (prog_ == NULL) {
    if (options_.log_errors())
      LOG(ERROR) << "Error compiling '" << trunc(pattern_) << "'";
    error_ = new string("pattern too large - compile failed");
    error_code_ = RE2::ErrorPatternTooLarge;
    return;
  }


  is_one_pass_ = prog_->IsOnePass();
}
