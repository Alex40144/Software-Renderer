#ifndef polygon_h
#define polygon_h

#include <vec2.h>
#include <vec3.h>
#include <vector>

class polygon
{
private:
    std::vector<std::vector<int>> EdgeTable;
    std::vector<Vec3<int>> PointTable;
    std::vector<Vec2<int>> ProjectedPointTable;

    Vec3<double> Rotation;

public:
    void addPoint(Vec3<int> point)
    {
        PointTable.push_back(point);
    }

    void addEdge(Vec3<int> point1, Vec3<int> point2)
    {
        int point1index = std::distance(PointTable.begin(), std::find(PointTable.begin(), PointTable.end(), point1));
        int point2index = std::distance(PointTable.begin(), std::find(PointTable.begin(), PointTable.end(), point2));
        EdgeTable.push_back(std::vector<int>{point1index, point2index});
    }

    void setRotation(Vec3<double> rot)
    {
        Rotation = rot;
    }

    Vec3<double> getRotation()
    {
        return Rotation;
    }

    std::vector<Vec3<int>> getPointTable()
    {
        return PointTable;
    }

    std::vector<Vec2<int>> getProjectedPointTable()
    {
        return ProjectedPointTable;
    }

    std::vector<std::vector<int>> getEdgeTable()
    {
        return EdgeTable;
    }

    void setProjectedPoint(std::vector<Vec2<int>> projected)
    {
        ProjectedPointTable = projected;
    }
};

#endif