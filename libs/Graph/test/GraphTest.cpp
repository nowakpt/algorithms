#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <Graph/Graph.hpp>

using ::testing::Contains;
using ::testing::Key;


TEST(GraphTest, CreateEmptyGraph)
{
    Graph<> gr;
    EXPECT_EQ(gr.begin(), gr.end());
}

TEST(GraphTest, AddUniqueVertices)
{
    Graph<> gr;
    gr.addVertice(-5);
    gr.addVertice(0);
    gr.addVertice(5);

    EXPECT_EQ(3, std::distance(gr.begin(), gr.end()));
}

TEST(GraphTest, AddDuplicateVertices)
{
    Graph<> gr;
    gr.addVertice(5);
    gr.addVertice(5);

    EXPECT_EQ(1, std::distance(gr.begin(), gr.end()));
    EXPECT_THAT(gr, Contains(Key(5)));
}

TEST(GraphTest, DeleteVertice)
{
    Graph<> gr;
    gr.addVertice(1);
    gr.addVertice(2);
    gr.addVertice(3);

    EXPECT_EQ(3, std::distance(gr.begin(), gr.end()));
    gr.deleteVertice(2);
    EXPECT_EQ(2, std::distance(gr.begin(), gr.end()));
}

TEST(GraphTest, DeleteNonExistingVertice)
{
    Graph<> gr;
    gr.addVertice(1);
    gr.addVertice(2);
    gr.addVertice(3);

    EXPECT_EQ(3, std::distance(gr.begin(), gr.end()));
    gr.deleteVertice(15);
    EXPECT_EQ(3, std::distance(gr.begin(), gr.end()));
}

TEST(GraphTest, ClearGraph)
{
    Graph<> gr;
    gr.addVertice(1);

    EXPECT_NE(gr.begin(), gr.end());
    gr.clear();
    EXPECT_EQ(gr.begin(), gr.end());
}

