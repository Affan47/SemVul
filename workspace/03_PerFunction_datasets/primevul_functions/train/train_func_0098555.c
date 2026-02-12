void ImapModelOpenConnectionTest::testPreauthWithStartTlsWanted()
{
    cleanup(); init(true);

    cEmpty();
    cServer("* PREAUTH hi there\r\n");
    QCOMPARE(failedSpy->size(), 1);
    QVERIFY(completedSpy->isEmpty());
    QVERIFY(authSpy->isEmpty());
    QVERIFY(startTlsUpgradeSpy->isEmpty());
}
