prepend(const char* str) {
  this->str = _rope_t(str) + this->str;
}
