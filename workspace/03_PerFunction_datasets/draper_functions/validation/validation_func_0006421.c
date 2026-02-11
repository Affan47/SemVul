set_history( const std::vector<String>& history )
{
  std::vector<String> histnew;
  histnew.insert( histnew.end(), history.begin() , history.end()  );
  histnew.insert( histnew.end(), history_.begin(), history_.end() );
  history_ = histnew;
}
