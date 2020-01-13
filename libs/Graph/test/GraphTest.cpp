#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include <Graph/Graph.hpp>

using ::testing::BeginEndDistanceIs;
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
    EXPECT_THAT(gr, Contains(5));
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

TEST(GraphTest, AddEdges)
{
    Graph<> gr;
    gr.addVertice(1);
    gr.addVertice(2);
    gr.addVertice(3);
    gr.addEdge(1, 2, 10); // bidirectional
    gr.addEdge(2, 1, 11); // bidirectional
    gr.addEdge(2, 2, 12); // should be ignored
    gr.addEdge(1, 3, 13); // unidirectional

    int visitedVertices = 0;
    for (const auto& vertice : gr)
    {
        const auto& edges = vertice.edges();

        if (vertice.value() == 1)
        {
            EXPECT_THAT(edges, BeginEndDistanceIs(2));
            ++visitedVertices;
        }
        else if (vertice.value() == 2)
        {
            EXPECT_THAT(edges, BeginEndDistanceIs(1));
            ++visitedVertices;
        }
        else if (vertice.value() == 3)
        {
            EXPECT_THAT(edges, BeginEndDistanceIs(0));
            ++visitedVertices;
        }
        else
        {
            FAIL() << "Graph contains invalid vertice";
        }
    }

    EXPECT_EQ(3, visitedVertices);
}

TEST(GraphTest, DeleteEdges)
{
    Graph<> gr;

    gr.addVertice(1);
    gr.addVertice(2);
    gr.addVertice(3);

    gr.addEdge(1, 2, 10);
    gr.addEdge(1, 3, 11);

    auto& edges = gr.find(1)->edges();
    auto addressOfVertice2 = &*gr.find(2);
    auto addressOfVertice3 = &*gr.find(3);

    EXPECT_THAT(edges, BeginEndDistanceIs(2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice3));

    gr.deleteEdge(1, 2);

    EXPECT_THAT(edges, BeginEndDistanceIs(1));
    EXPECT_EQ(edges.end(), edges.find(addressOfVertice2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice3));
}

TEST(GraphTest, DeleteNonExistingEdges)
{
    Graph<> gr;

    gr.addVertice(1);
    gr.addVertice(2);
    gr.addVertice(3);

    gr.addEdge(1, 2, 10);
    gr.addEdge(1, 3, 11);

    auto& edges = gr.find(1)->edges();
    auto addressOfVertice2 = &*gr.find(2);
    auto addressOfVertice3 = &*gr.find(3);

    EXPECT_THAT(edges, BeginEndDistanceIs(2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice3));

    gr.deleteEdge(1, 4);
    gr.deleteEdge(2, 1);
    gr.deleteEdge(1, 1);

    EXPECT_THAT(edges, BeginEndDistanceIs(2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice2));
    EXPECT_NE(edges.end(), edges.find(addressOfVertice3));
}

TEST(GraphTest, OverwriteEdge)
{
    Graph<> gr;

    gr.addVertice(1);
    gr.addVertice(2);

    auto addressOfVertice2 = &*gr.find(2);
    auto& edges = gr.find(1)->edges();

    gr.addEdge(1, 2, 10);

    {
        Graph<>::Edge e = *edges.find(addressOfVertice2);
        EXPECT_EQ(10, e.value());
    }

    gr.addEdge(1, 2, 15);

    {
        Graph<>::Edge e = *edges.find(addressOfVertice2);
        EXPECT_EQ(10, e.value()); // value should not change if an edge already exists
    }
}

