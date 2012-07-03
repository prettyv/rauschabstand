//|||||||||||||||||||||||||||||||||||||||||||||||

#include "MapGenerator.hpp"

//|||||||||||||||||||||||||||||||||||||||||||||||

MapGenerator::MapGenerator(std::string mapname, SceneManager* sceneMgr,
                           unsigned int length, unsigned int width)
{
    m_map = new Map(mapname, sceneMgr, length, width);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void trippleBump(Map* map, unsigned int t)
{
    map->setTimeQuaternion(t - 7, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(t, Quaternion(Degree(3), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 7, Quaternion(Degree(-6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 16, Quaternion(Degree(6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 23, Quaternion(Degree(-6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 32, Quaternion(Degree(6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 39, Quaternion(Degree(-6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 46, Quaternion(1, 0, 0, 0));

    map->setCubes(t, 1, 3, 7, OBSTACLE);
    map->setCubes(t + 16, 1, 0, 7, OBSTACLE);
    map->setCubes(t + 32, 1, 3, 7, OBSTACLE);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void bigTrippleBump(Map* map, unsigned int t)
{
    map->setTimeQuaternion(t - 10, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(t, Quaternion(Degree(7), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 7, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 6, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 6, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 6, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 6, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 16, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 16, 3, 2, 1, HOLE);
    map->setCubes(t + 16, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 23, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 22, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 22, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 22, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 22, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 32, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 32, 3, 2, 1, HOLE);
    map->setCubes(t + 32, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 39, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 38, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 38, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 38, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 38, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 47, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 47, 3, 2, 1, HOLE);
    map->setCubes(t + 47, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 56, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 55, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 55, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 55, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 55, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 65, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 65, 3, 2, 1, HOLE);
    map->setCubes(t + 65, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 73, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 72, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 72, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 72, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 72, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 81, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 81, 3, 2, 1, HOLE);
    map->setCubes(t + 81, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 89, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 88, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 88, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 88, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 88, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 98, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 98, 3, 2, 1, HOLE);
    map->setCubes(t + 98, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 107, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 106, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 106, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 106, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 106, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 115, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 115, 3, 2, 1, HOLE);
    map->setCubes(t + 115, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 123, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 122, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 122, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 122, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 122, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 132, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 132, 3, 2, 1, HOLE);
    map->setCubes(t + 132, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 140, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 139, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 139, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 139, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 139, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 148, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 148, 3, 2, 1, HOLE);
    map->setCubes(t + 148, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 157, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 156, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 156, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 156, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 156, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 166, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 166, 3, 2, 1, HOLE);
    map->setCubes(t + 166, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 174, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 173, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 173, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 173, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 173, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 182, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 182, 3, 2, 1, HOLE);
    map->setCubes(t + 182, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 190, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 189, 3, 0, 1, OBSTACLE);
    map->setCubes(t + 189, 3, 4, 1, OBSTACLE);
    map->setCubes(t + 189, 3, 8, 1, OBSTACLE);
    map->setCubes(t + 189, 3, 10, 1, OBSTACLE);
    map->setTimeQuaternion(t + 198, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 198, 3, 2, 1, HOLE);
    map->setCubes(t + 198, 3, 6, 1, HOLE);
    map->setTimeQuaternion(t + 207, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 217, Quaternion(1, 0, 0, 0));
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void bigTrippleBump2(Map* map, unsigned int t)
{
    map->setTimeQuaternion(t - 10, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(t, Quaternion(Degree(7), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 7, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 7, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 7, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 7, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 16, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 15, 3, 2, 2, HOLE);
    map->setCubes(t + 15, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 23, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 23, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 23, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 23, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 32, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 32, 3, 2, 2, HOLE);
    map->setCubes(t + 32, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 39, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 39, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 39, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 39, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 48, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 48, 3, 2, 2, HOLE);
    map->setCubes(t + 48, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 57, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 57, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 57, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 57, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 66, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 66, 3, 2, 2, HOLE);
    map->setCubes(t + 66, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 75, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 75, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 75, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 75, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 83, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 83, 3, 2, 2, HOLE);
    map->setCubes(t + 83, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 92, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 92, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 92, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 92, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 100, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 100, 3, 2, 2, HOLE);
    map->setCubes(t + 100, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 109, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 109, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 109, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 109, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 118, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 118, 3, 2, 2, HOLE);
    map->setCubes(t + 118, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 125, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 125, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 125, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 125, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 134, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 134, 3, 2, 2, HOLE);
    map->setCubes(t + 134, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 143, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 143, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 143, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 143, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 151, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 151, 3, 2, 2, HOLE);
    map->setCubes(t + 151, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 160, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 160, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 160, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 160, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 169, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 168, 3, 2, 2, HOLE);
    map->setCubes(t + 168, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 177, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 177, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 177, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 177, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 184, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 184, 3, 2, 2, HOLE);
    map->setCubes(t + 184, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 190, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 190, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 190, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 190, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 198, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 198, 3, 2, 2, HOLE);
    map->setCubes(t + 198, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 207, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 207, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 207, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 207, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 215, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 215, 3, 2, 2, HOLE);
    map->setCubes(t + 215, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 224, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 224, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 224, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 224, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 232, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 232, 3, 2, 2, HOLE);
    map->setCubes(t + 232, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 240, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 240, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 240, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 240, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 249, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 249, 3, 2, 2, HOLE);
    map->setCubes(t + 249, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 257, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 257, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 257, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 257, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 265, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 265, 3, 2, 2, HOLE);
    map->setCubes(t + 265, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 272, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 272, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 272, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 272, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 280, Quaternion(Degree(14), Vector3(1, 0, 0)));
    map->setCubes(t + 280, 3, 2, 2, HOLE);
    map->setCubes(t + 280, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 289, Quaternion(Degree(-14), Vector3(1, 0, 0)));
    map->setCubes(t + 289, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 289, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 289, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 296, Quaternion(Degree(12), Vector3(1, 0, 0)));
    map->setCubes(t + 296, 3, 2, 2, HOLE);
    map->setCubes(t + 296, 3, 6, 2, HOLE);
    map->setTimeQuaternion(t + 305, Quaternion(Degree(-12), Vector3(1, 0, 0)));
    map->setCubes(t + 305, 1, 0, 2, OBSTACLE);
    map->setCubes(t + 305, 1, 4, 2, OBSTACLE);
    map->setCubes(t + 305, 1, 8, 2, OBSTACLE);
    map->setTimeQuaternion(t + 313, Quaternion(Degree(10), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 321, Quaternion(Degree(-10), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 329, Quaternion(Degree(8), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 338, Quaternion(Degree(-8), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 346, Quaternion(Degree(6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 354, Quaternion(Degree(-6), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 362, Quaternion(Degree(4), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 370, Quaternion(Degree(-4), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 378, Quaternion(Degree(2), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 386, Quaternion(Degree(-2), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 396, Quaternion(1, 0, 0, 0));
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void raise(Map* map, unsigned int t)
{
    map->setTimeQuaternion(t - 5, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(t, Quaternion(Degree(20), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 5, Quaternion(Degree(-10), Vector3(1, 0, 0)));

    map->setCubesRadius(t, 0, 4, HOLE);
    map->setCubesRadius(t, 10, 4, HOLE);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void spin(Map* map, unsigned int t)
{
    map->setTimeQuaternion(t - 10, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(t + 30, Quaternion(Degree(50), Vector3(0, -1, 0)));
    map->setTimeQuaternion(t + 50, Quaternion(1, 0, 0, 0));

    unsigned int tmp = t;
    tmp = t - 9;
    map->setCubes(tmp, 1, 0, 1, OBSTACLE);
    map->setCubes(tmp, 1, 2, 1, OBSTACLE);
    map->setCubes(tmp, 1, 4, 1, OBSTACLE);
    map->setCubes(tmp, 1, 6, 1, OBSTACLE);
    map->setCubes(tmp, 1, 8, 1, OBSTACLE);
    map->setCubes(tmp, 1, 10, 1, OBSTACLE);
    tmp = t;
    map->setCubes(tmp, 1, 1, 1, OBSTACLE);
    map->setCubes(tmp, 1, 3, 1, OBSTACLE);
    map->setCubes(tmp, 1, 5, 1, OBSTACLE);
    map->setCubes(tmp, 1, 7, 1, OBSTACLE);
    map->setCubes(tmp, 1, 9, 1, OBSTACLE);
    tmp = t + 10;
    map->setCubes(tmp, 1, 0, 1, OBSTACLE);
    map->setCubes(tmp, 1, 2, 1, OBSTACLE);
    map->setCubes(tmp, 1, 4, 1, OBSTACLE);
    map->setCubes(tmp, 1, 6, 1, OBSTACLE);
    map->setCubes(tmp, 1, 8, 1, OBSTACLE);
    map->setCubes(tmp, 1, 10, 1, OBSTACLE);
    tmp = t + 20;
    map->setCubes(tmp, 1, 1, 1, OBSTACLE);
    map->setCubes(tmp, 1, 3, 1, OBSTACLE);
    map->setCubes(tmp, 1, 5, 1, OBSTACLE);
    map->setCubes(tmp, 1, 7, 1, OBSTACLE);
    map->setCubes(tmp, 1, 9, 1, OBSTACLE);
    tmp = t + 30;
    map->setCubes(tmp, 1, 0, 1, OBSTACLE);
    map->setCubes(tmp, 1, 2, 1, OBSTACLE);
    map->setCubes(tmp, 1, 4, 1, OBSTACLE);
    map->setCubes(tmp, 1, 6, 1, OBSTACLE);
    map->setCubes(tmp, 1, 8, 1, OBSTACLE);
    map->setCubes(tmp, 1, 10, 1, OBSTACLE);
    tmp = t + 40;
    map->setCubes(tmp, 1, 1, 1, OBSTACLE);
    map->setCubes(tmp, 1, 3, 1, OBSTACLE);
    map->setCubes(tmp, 1, 5, 1, OBSTACLE);
    map->setCubes(tmp, 1, 7, 1, OBSTACLE);
    map->setCubes(tmp, 1, 9, 1, OBSTACLE);
    tmp = t + 48;
    map->setCubes(tmp, 1, 0, 1, OBSTACLE);
    map->setCubes(tmp, 1, 2, 1, OBSTACLE);
    map->setCubes(tmp, 1, 4, 1, OBSTACLE);
    map->setCubes(tmp, 1, 6, 1, OBSTACLE);
    map->setCubes(tmp, 1, 8, 1, OBSTACLE);
    map->setCubes(tmp, 1, 10, 1, OBSTACLE);

}

//|||||||||||||||||||||||||||||||||||||||||||||||

void gap(Map* map, unsigned int t)
{
    map->setTimeQuaternion(t - 3, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(t, Quaternion(Degree(-20), Vector3(1, 0, 0)));
    map->setTimeQuaternion(t + 3, Quaternion(Degree(10), Vector3(1, 0, 0)));

    map->setCubes(t - 1, 3, 0, 10, HOLE);
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void createMap(Map* map)
{
    map->setTimeQuaternion(170, Quaternion(Degree(60), Vector3(-1, 0, 0)));
    trippleBump(map, 180);
    raise(map, 239);
    trippleBump(map, 254);
    raise(map, 310);
    trippleBump(map, 326);
    raise(map, 379);
    spin(map, 397);
    gap(map, 450);

    trippleBump(map, 465);
    raise(map, 524);
    trippleBump(map, 538);
    raise(map, 594);
    trippleBump(map, 609);
    raise(map, 662);
    spin(map, 680);

    map->setTimeQuaternion(736 - 6, Quaternion(1, 0, 0, 0));
    map->setTimeQuaternion(736, Quaternion(Degree(20), Vector3(1, 0, 0)));
    map->setTimeQuaternion(736 + 6, Quaternion(Degree(-10), Vector3(1, 0, 0)));

    trippleBump(map, 748);
    raise(map, 807);
    trippleBump(map, 821);
    raise(map, 877);
    trippleBump(map, 892);
    raise(map, 945);
    spin(map, 963);

    bigTrippleBump(map, 1025);

    map->setTimeQuaternion(1285, Quaternion(Degree(-20), Vector3(1, 1, 0)));

    bigTrippleBump2(map, 1300);

    map->setTimeQuaternion(map->getLength(), Quaternion(Degree(-40), Vector3(1, 0, 0)));
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MapGenerator::generateMap()
{
    //setCubes
    //TODO code more functions to modify Cubes
    m_map->resetCubes();
    //parseAudioForHoles();

    /*
    m_map->setCubes(350, 1, 5, 1, OBSTACLE);
    m_map->setCubes(400, 1, 5, 1, OBSTACLE);
    m_map->setCubes(450, 1, 5, 1, OBSTACLE);
    m_map->setCubes(500, 1, 5, 1, OBSTACLE);
    m_map->setCubes(550, 1, 5, 1, OBSTACLE);
    m_map->setCubes(600, 1, 5, 1, OBSTACLE);
    m_map->setCubes(650, 1, 5, 1, OBSTACLE);

    m_map->setCubesRadius(300, 10, 3, HOLE);
    m_map->setCubesRadius(400, 10, 3, HOLE);
    m_map->setCubesRadius(500, 10, 3, HOLE);
    m_map->setCubesRadius(600, 10, 3, HOLE);
    m_map->setCubesRadius(700, 10, 3, HOLE);
    m_map->setCubesRadius(800, 10, 3, HOLE);

    //use these last
    m_map->setCubesRow(0, 10, NORMAL);      //start is normal
    m_map->setCubesRow(-5, 5, HOLE);        //cuts of end
    */

    //setTimeQuaternions
    //TODO: move setTimeQuaternions here
    //TODO: make setTimeQuaternions work with audio data
    //m_map->setTimeQuaternions();
    m_map->setTimeQuaternion(0, Quaternion(1, 0, 0, 0));
    //parseAudioForOrientation();
    createMap(m_map);
    m_map->setTimeQuaternion(m_map->getLength(), Quaternion(1, 0, 0, 0));

    m_map->addUpTimeQuaternions();
    m_map->interpolateTimeQuaternions();

    //TODO: seperate into: Obsticales and Map, outside Border and Map, choose material here.
    m_map->generateMesh("Examples/Rockwall");
    m_map->generateMeshObstacles("obstacleMaterial");
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MapGenerator::parseAudioForOrientation()
{
    unsigned int countLinenumbers = 0;
    unsigned int samples = 0;
    double audioData = 0.0;
    std::stringstream sstr;
    unsigned int lastT = 0;

    std::string line;
    std::ifstream myfile ("spectralAnalysis_4096_samples.txt");

    // EINGABEGROESSE (BARCOUNT, CUBECOUNT) ABHAENGIG!
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline (myfile, line);

            if (line.size() > 0) {
                sstr.str(line);
                std::string tmpstr = sstr.str();

                sstr >> audioData;


                // TODO automate range determination
                // get the data in range 0-7
                if (audioData != 0) {
                    audioData -= 1;
                    audioData *= 100000;
                }

                // 12 bands, 16384 samples buffer ~= 0,37s window -> / 370ms || 4096 samples = 92.5ms
                unsigned int t = Real(92.5) * m_blockMs * samples + 10000 * m_blockMs;

                if (t - lastT > 10 && countLinenumbers % 12 < 4) {
                    if (audioData > 500) {
                        m_map->setTimeQuaternion(t - 2, Quaternion(Degree(audioData / 300), Vector3(1, 0, 0)));
                        m_map->setTimeQuaternion(t, Quaternion(Degree(-audioData / 300), Vector3(1, 0, 0)));
                        m_map->setTimeQuaternion(t + 2, Quaternion(Degree(-audioData / 300), Vector3(1, 0, 0)));
                        m_map->setTimeQuaternion(t + 4, Quaternion(Degree(audioData / 300), Vector3(1, 0, 0)));

                        lastT = t;
                    }
                }

                sstr.clear();
                line.clear();
                tmpstr.clear();
                audioData = 0.0;
            }

            ++countLinenumbers;

            if (countLinenumbers % 12 == 0) {
                ++samples;
            }
        }

        myfile.close();
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void MapGenerator::parseAudioForHoles()
{
    unsigned int countLinenumbers = 0;
    unsigned int samples = 0;
    double audioData = 0.0;
    std::stringstream sstr;
    unsigned int lastT = 0;

    std::string line;
    std::ifstream myfile ("spectralAnalysis_4096_samples.txt");

    // EINGABEGROESSE (BARCOUNT, CUBECOUNT) ABHAENGIG!
    if (myfile.is_open()) {
        while (myfile.good()) {
            getline (myfile, line);

            if (line.size() > 0) {
                sstr.str(line);
                std::string tmpstr = sstr.str();

                sstr >> audioData;


                // TODO automate range determination
                // get the data in range 0-7
                if (audioData != 0) {
                    audioData -= 1;
                    audioData *= 100000;
                }

                // 12 bands, 16384 samples buffer ~= 0,37s window -> / 370ms || 4096 samples = 92.5ms
                unsigned int t = Real(92.5) * m_blockMs * samples + 10000 * m_blockMs;

                if (t - lastT > 5 && countLinenumbers % 12 > 4) {
                    if (audioData > 500) {
                        int radius = 0;

                        if (audioData < 800) {
                            radius = 1;
                        } else if (audioData < 1200) {
                            radius = 2;
                        } else {
                            radius = 3;
                        }

                        //int y = ((countLinenumbers % 12) - 5) * 2;
                        int y = (int) audioData % 10;
                        m_map->setCubesRadius(t, y, radius, HOLE);

                        lastT = t;
                    }
                }

                sstr.clear();
                line.clear();
                tmpstr.clear();
                audioData = 0.0;
            }

            ++countLinenumbers;

            if (countLinenumbers % 12 == 0) {
                ++samples;
            }
        }

        myfile.close();
    }
}

//|||||||||||||||||||||||||||||||||||||||||||||||

