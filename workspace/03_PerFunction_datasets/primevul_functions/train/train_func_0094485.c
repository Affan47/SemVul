TEST(Random, SecureFork) {
  unsigned char buffer = 0;

  folly::Random::secureRandom(&buffer, 1);

  auto pid = fork();
  EXPECT_NE(pid, -1);
  if (pid) {

    int status = 0;
    folly::Random::secureRandom(&buffer, 1);
    auto pid2 = wait(&status);
    EXPECT_NE(WEXITSTATUS(status), buffer);
    EXPECT_EQ(pid, pid2);
  } else {

    folly::Random::secureRandom(&buffer, 1);
    exit(buffer);
  }
}
