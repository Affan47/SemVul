GetNextComments(vector<StringPiece> *ranges) {


  if (!comments_) {
    return;
  }
  for (vector<StringPiece>::const_iterator it =
         comments_->begin() + comments_offset_;
       it != comments_->end(); ++it) {
    ranges->push_back(*it);
    ++comments_offset_;
  }
}
