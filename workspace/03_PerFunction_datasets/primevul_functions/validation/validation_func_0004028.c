void createUpstreams() override {
    HttpProtocolIntegrationTest::createUpstreams();

    addFakeUpstream(GetParam().upstream_protocol);
  }
