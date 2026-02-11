render(render_guts_t* guts, int indentation) const {
  return rope_t("switch(") + this->_childNodes.front()->render(guts, indentation) + ")" +

    this->_childNodes.back()->renderBlock(true, guts, indentation + 1);
}
