EncodeLine(std::vector<std::string>& tokens)
{
  std::string scoresString = tokens.back();
  std::stringstream scoresStream;

  std::vector<float> scores;
  Tokenize<float>(scores, scoresString);

  if(!m_numScoreComponent) {
    m_numScoreComponent = scores.size();
    m_scoreCounters.resize(m_multipleScoreTrees ? m_numScoreComponent : 1);
    for(std::vector<ScoreCounter*>::iterator it = m_scoreCounters.begin();
        it != m_scoreCounters.end(); it++)
        *it = new ScoreCounter();
    m_scoreTrees.resize(m_multipleScoreTrees ? m_numScoreComponent : 1);
  }

  if(m_numScoreComponent != scores.size()) {
    std::cerr << "Error: Wrong number of scores detected ("
      << scores.size() << " != " << m_numScoreComponent << ") :" << std::endl;
    std::cerr << "Line: " << tokens[0] << " ||| ... ||| " << scoresString << std::endl;
    abort();
  }

  size_t c = 0;
  float score;
  while(c < m_numScoreComponent)
  {
    score = scores[c];
    score = FloorScore(TransformScore(score));
    scoresStream.write((char*)&score, sizeof(score));

    m_scoreCounters[m_multipleScoreTrees ? c : 0]->Increase(score);
    c++;
  }

  return scoresStream.str();
}
