TEST_F(QueryPlannerTest, TagAccordingToCacheFailsOnBadInput) {
    const NamespaceString nss("test.collection");

    auto qr = stdx::make_unique<QueryRequest>(nss);
    qr->setFilter(BSON("a" << 3));
    auto statusWithCQ = CanonicalQuery::canonicalize(opCtx.get(), std::move(qr));
    ASSERT_OK(statusWithCQ.getStatus());
    std::unique_ptr<CanonicalQuery> scopedCq = std::move(statusWithCQ.getValue());

    std::unique_ptr<PlanCacheIndexTree> indexTree(new PlanCacheIndexTree());
    indexTree->setIndexEntry(IndexEntry(BSON("a" << 1), "a_1"));

    std::map<StringData, size_t> indexMap;


    Status s = QueryPlanner::tagAccordingToCache(NULL, indexTree.get(), indexMap);
    ASSERT_NOT_OK(s);


    s = QueryPlanner::tagAccordingToCache(scopedCq->root(), NULL, indexMap);
    ASSERT_NOT_OK(s);


    s = QueryPlanner::tagAccordingToCache(scopedCq->root(), indexTree.get(), indexMap);
    ASSERT_NOT_OK(s);


    indexMap["a_1"_sd] = 0;
    s = QueryPlanner::tagAccordingToCache(scopedCq->root(), indexTree.get(), indexMap);
    ASSERT_OK(s);


    auto newQR = stdx::make_unique<QueryRequest>(nss);
    newQR->setFilter(BSON("a" << 3));
    statusWithCQ = CanonicalQuery::canonicalize(opCtx.get(), std::move(newQR));
    ASSERT_OK(statusWithCQ.getStatus());
    scopedCq = std::move(statusWithCQ.getValue());


    PlanCacheIndexTree* child = new PlanCacheIndexTree();
    child->setIndexEntry(IndexEntry(BSON("a" << 1)));
    indexTree->children.push_back(child);
    s = QueryPlanner::tagAccordingToCache(scopedCq->root(), indexTree.get(), indexMap);
    ASSERT_NOT_OK(s);
}
