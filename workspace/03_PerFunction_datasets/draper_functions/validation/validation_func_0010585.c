startTest( Test *test )
{
  stdCOut() << test->getName();
  stdCOut().flush();

  m_lastTestFailed = false;
}
