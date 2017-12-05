#include "queue.h"

#include <library/unittest/registar.h>

#include <util/generic/set.h>

namespace NThreading {

////////////////////////////////////////////////////////////////////////////////

SIMPLE_UNIT_TEST_SUITE(TOneOneQueueTest) {
    SIMPLE_UNIT_TEST(ShouldBeEmptyAtStart)
    {
        TOneOneQueue<int> queue;

        int result = 0;
        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }

    SIMPLE_UNIT_TEST(ShouldReturnEntries)
    {
        TOneOneQueue<int> queue;
        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);

        int result = 0;
        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 1);

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 2);

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 3);

        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }

    SIMPLE_UNIT_TEST(ShouldStoreMultipleChunks)
    {
        TOneOneQueue<int, 100> queue;
        for (int i = 0; i < 1000; ++i) {
            queue.Enqueue(i);
        }

        for (int i = 0; i < 1000; ++i) {
            int result = 0;
            UNIT_ASSERT(!queue.IsEmpty());
            UNIT_ASSERT(queue.Dequeue(result));
            UNIT_ASSERT_EQUAL(result, i);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////

SIMPLE_UNIT_TEST_SUITE(TManyOneQueueTest) {
    SIMPLE_UNIT_TEST(ShouldBeEmptyAtStart)
    {
        TManyOneQueue<int> queue;

        int result;
        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }

    SIMPLE_UNIT_TEST(ShouldReturnEntries)
    {
        TManyOneQueue<int> queue;
        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);

        int result = 0;
        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 1);

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 2);

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 3);

        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }
};

////////////////////////////////////////////////////////////////////////////////

SIMPLE_UNIT_TEST_SUITE(TManyManyQueueTest) {
    SIMPLE_UNIT_TEST(ShouldBeEmptyAtStart)
    {
        TManyManyQueue<int> queue;

        int result = 0;
        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }

    SIMPLE_UNIT_TEST(ShouldReturnEntries)
    {
        TManyManyQueue<int> queue;
        queue.Enqueue(1);
        queue.Enqueue(2);
        queue.Enqueue(3);

        int result = 0;
        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 1);

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 2);

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT_EQUAL(result, 3);

        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }
};

////////////////////////////////////////////////////////////////////////////////

SIMPLE_UNIT_TEST_SUITE(TRelaxedManyOneQueueTest) {
    SIMPLE_UNIT_TEST(ShouldBeEmptyAtStart)
    {
        TRelaxedManyOneQueue<int> queue;

        int result;
        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }

    SIMPLE_UNIT_TEST(ShouldReturnEntries)
    {
        TSet<int> items = { 1, 2, 3};

        TRelaxedManyOneQueue<int> queue;
        for (int item: items) {
            queue.Enqueue(item);
        }

        int result = 0;
        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT(items.erase(result));

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT(items.erase(result));

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT(items.erase(result));

        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }
};

////////////////////////////////////////////////////////////////////////////////

SIMPLE_UNIT_TEST_SUITE(TRelaxedManyManyQueueTest) {
    SIMPLE_UNIT_TEST(ShouldBeEmptyAtStart)
    {
        TRelaxedManyManyQueue<int> queue;

        int result = 0;
        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }

    SIMPLE_UNIT_TEST(ShouldReturnEntries)
    {
        TSet<int> items = { 1, 2, 3};

        TRelaxedManyManyQueue<int> queue;
        for (int item: items) {
            queue.Enqueue(item);
        }

        int result = 0;
        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT(items.erase(result));

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT(items.erase(result));

        UNIT_ASSERT(!queue.IsEmpty());
        UNIT_ASSERT(queue.Dequeue(result));
        UNIT_ASSERT(items.erase(result));

        UNIT_ASSERT(queue.IsEmpty());
        UNIT_ASSERT(!queue.Dequeue(result));
    }
};

}   // namespace NThreading
