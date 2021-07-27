#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>


using namespace std;

typedef pair<int, int> Pair;
typedef tuple<double, int, int> Tuple;

class astarClass {
public:

    struct cell {
        Pair position;
        double f, g, h;
        cell() {
            position.first = -1;
            position.second = -1;
            f = -1;
            g = -1;
            h = -1;
        }
    };
    template <size_t ROW, size_t COL>
    vector<tuple<int, int>> tracePath(const array<array<cell, COL>, ROW>& cellDetails, const Pair& dest) {
        stack<Pair> Path;
        vector<tuple<int, int>> result;
        tuple<int, int> temp;

        int row = dest.second;
        int col = dest.second;
        Pair next_node = cellDetails[row][col].position;

        do {
            Path.push(next_node);
            next_node = cellDetails[row][col].position;
            row = next_node.first;
            col = next_node.second;
        } while (cellDetails[row][col].position != next_node);

        Path.emplace(row, col);
        while (!Path.empty()) {
            Pair p = Path.top();
            Path.pop();
            temp= make_tuple(p.first, p.second);
            result.push_back(temp);
            printf("-> (%d,%d) ", p.first, p.second);
        }

        return result;
    }

    Pair dest;
    Pair src;
    int fin = -1;

    array<array<int, 10>, 9> grid{
        { { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
          { { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 } },
          { { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 } },
          { { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 } },
          { { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 } },
          { { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 } },
          { { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 } },
          { { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 } },
          { { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 } } }
    };
    int ROW, COL;

    bool closedList[sizeof(grid[0]) / sizeof(grid[0][0])][sizeof(grid) / sizeof(grid[0])];
    array<array<cell, sizeof(grid[0]) / sizeof(grid[0][0])>, sizeof(grid) / sizeof(grid[0])> cellDetails;
    std::priority_queue<Tuple, std::vector<Tuple>,
        std::greater<Tuple> >
        openList;

#pragma region Helper Functions

    template<size_t ROW, size_t COL>
    bool isValid(const array<array<int, COL>, ROW>& grid, Pair point) {
        if (point.first >= 0 && point.second >= 0 && point.first < ROW && point.second < COL && ROW > 0 && COL > 0) {
            return true;
        }
        return false;
    }

    bool isDestination(const Pair& position, const Pair& dest)
    {
        return position == dest;
    }

    template <size_t ROW, size_t COL>
    bool isUnBlocked(const array<array<int, COL>, ROW>& grid,
        const Pair& point)
    {
        // Returns true if the cell is not blocked else false
        return isValid(grid, point)
            && grid[point.first][point.second] == 1;
    }

    double euDist(const Pair& src, const Pair& dest) {
        return sqrt(pow((src.first - dest.first), 2.0) + pow((src.second - dest.second), 2.0));
    }
#pragma endregion


    int changeState() {
        int i, j;
        const Tuple& p = openList.top();
        i = get<1>(p);
        j = get<2>(p);
        openList.pop();
        closedList[i][j] = true;

        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {
                Pair neighbour(i + add_x, j + add_y);
                if (isValid(grid, neighbour)) {
                    if (isDestination(neighbour, dest)) {
                        cellDetails[neighbour.first][neighbour.second].position = { i,j };
                        printf("Found");
                        tracePath(cellDetails, dest);
                        fin = 2;
                        return 2;
                    }
                    else if (!closedList[neighbour.first][neighbour.second] && isUnBlocked(grid, neighbour)) {
                        double gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + 1.0;
                        hNew = euDist(neighbour, dest);
                        fNew = gNew + hNew;

                        if (cellDetails[neighbour.first][neighbour.second].f == -1 || cellDetails[neighbour.first][neighbour.second].f > fNew) {
                            openList.emplace(fNew, neighbour.first, neighbour.second);
                            cellDetails[neighbour.first][neighbour.second].g = gNew;
                            cellDetails[neighbour.first][neighbour.second].h = hNew;
                            cellDetails[neighbour.first][neighbour.second].f = fNew;
                            cellDetails[neighbour.first][neighbour.second].position = { i, j };
                        }
                    }
                }
            }
        }
        fin = 1;
        return -1;
    }


    astarClass(const Pair& src, const Pair& dest) {
        this->dest = dest;
        this->src = src;

        if (!this->isValid(grid, src) || !this->isValid(grid, dest)) {
            printf("Invalid Grid or Points");
            return;
        }

        this->ROW = sizeof(grid) / sizeof(grid[0]);
        this->COL = sizeof(grid[0]) / sizeof(grid[0][0]);

        memset(closedList, false, sizeof(closedList));
        int i, j;
        i = src.first;
        j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].position = { i, j };
        openList.emplace(0.0, i, j);

    }

    int getRow() {
        return this->ROW;
    }

    int getCol() {
        return this->COL;
    }

    vector<tuple<int, int>> generatePath() {
        return tracePath(cellDetails, dest);
    }    
};