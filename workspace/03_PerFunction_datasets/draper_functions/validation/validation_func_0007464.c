openMess(std::string filename)
{
  if(filename.empty())return;

  gem::image::load::cancel(m_id);

  m_filename = findFile(filename);

  gem::image::load::callback cb = loadCallback;
  void*userdata=reinterpret_cast<void*>(this);

  m_id = gem::image::load::INVALID;

  bool success=false;
  if(m_wantThread) {
    success=gem::image::load::async(cb, userdata, m_filename, m_id);
  } else {
    success=gem::image::load:: sync(cb, userdata, m_filename, m_id);
  }
  if(gem::image::load::INVALID == m_id)
    success=false;

  std::vector<gem::any>atoms;
  gem::any value;

  if(success) {
    if(gem::image::load::IMMEDIATE!=m_id) {
      verbose(1, "loading image '%s' with ID:%d", m_filename.c_str(), m_id);
      atoms.push_back(value=std::string("defer"));
      atoms.push_back(value=(int)m_id);
    } else {
      atoms.push_back(value=std::string("success"));
    }
  } else {
    error("loading of '%s' failed", m_filename.c_str());
    atoms.push_back(value=std::string("fail"));
  }
  atoms.push_back(value=m_filename);
  m_infoOut.send("load", atoms);
}
