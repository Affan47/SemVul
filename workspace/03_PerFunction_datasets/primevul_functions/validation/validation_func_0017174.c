TEST_F(QueryPlannerTest, CacheDataFromTaggedTreeFailsOnBadInput) {

    std::vector<IndexEntry> relevantIndices;
    ASSERT_NOT_OK(QueryPlanner::cacheDataFromTaggedTree(NULL, relevantIndices).getStatus());


    relevantIndices.push_back(IndexEntry(BSON("a" << 1)));

    auto qr = stdx::make_unique<QueryRequest>(NamespaceString("test.collection"));
    qr->setFilter(BSON("a" << 3));
    auto statusWithCQ = CanonicalQuery::canonicalize(opCtx.get(), std::move(qr));
    ASSERT_OK(statusWithCQ.getStatus());
    std::unique_ptr<CanonicalQuery> scopedCq = std::move(statusWithCQ.getValue());
    scopedCq->root()->setTag(new IndexTag(1));

    ASSERT_NOT_OK(
        QueryPlanner::cacheDataFromTaggedTree(scopedCq->root(), relevantIndices).getStatus());
}
