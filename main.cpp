#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <map>

using namespace std;

// Размер сетки
const int GRID_WIDTH = 10;
const int GRID_HEIGHT = 10;

// Возможные тайлы
enum Tile {
    EMPTY,
    GRASS,
    WATER,
    SAND,
    MOUNTAIN
};

// Правила соседства тайлов (какие тайлы могут быть соседями)
std::map<Tile, std::vector<Tile>> adjacencyRules = {
    {GRASS, {GRASS, SAND, WATER}},
    {WATER, {WATER, GRASS}},
    {SAND, {SAND, GRASS, MOUNTAIN}},
    {MOUNTAIN, {SAND, MOUNTAIN}},
    {EMPTY, {GRASS, WATER, SAND, MOUNTAIN}}
};

// Структура клетки сетки
struct Cell {
    bool collapsed = false;  // Состояние: коллапсировала ли клетка
    Tile tile = EMPTY;       // Выбранный тайл
    std::vector<Tile> possibleTiles = {GRASS, WATER, SAND, MOUNTAIN};  // Возможные тайлы
};

// Инициализация сетки
void initializeGrid(std::vector<std::vector<Cell>>& grid) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            grid[y][x] = Cell();
        }
    }
}

// Функция выбора тайла на основе вероятностей
Tile chooseRandomTile(const std::vector<Tile>& possibleTiles) {
    int randomIndex = rand() % possibleTiles.size();
    return possibleTiles[randomIndex];
}

// Обновление возможных состояний для клетки
void updateCellPossibilities(std::vector<std::vector<Cell>>& grid, int x, int y) {
    if (grid[y][x].collapsed) return;

    std::vector<Tile> newPossibilities;
    for (Tile tile : grid[y][x].possibleTiles) {
        bool valid = true;

        // Проверка соседей
        if (x > 0 && grid[y][x-1].collapsed) {  // Сосед слева
            if (std::find(adjacencyRules[grid[y][x-1].tile].begin(),
                          adjacencyRules[grid[y][x-1].tile].end(), tile) == adjacencyRules[grid[y][x-1].tile].end()) {
                valid = false;
            }
        }
        if (x < GRID_WIDTH - 1 && grid[y][x+1].collapsed) {  // Сосед справа
            if (std::find(adjacencyRules[grid[y][x+1].tile].begin(),
                          adjacencyRules[grid[y][x+1].tile].end(), tile) == adjacencyRules[grid[y][x+1].tile].end()) {
                valid = false;
            }
        }
        if (y > 0 && grid[y-1][x].collapsed) {  // Сосед сверху
            if (std::find(adjacencyRules[grid[y-1][x].tile].begin(),
                          adjacencyRules[grid[y-1][x].tile].end(), tile) == adjacencyRules[grid[y-1][x].tile].end()) {
                valid = false;
            }
        }
        if (y < GRID_HEIGHT - 1 && grid[y+1][x].collapsed) {  // Сосед снизу
            if (std::find(adjacencyRules[grid[y+1][x].tile].begin(),
                          adjacencyRules[grid[y+1][x].tile].end(), tile) == adjacencyRules[grid[y+1][x].tile].end()) {
                valid = false;
            }
        }

        if (valid) {
            newPossibilities.push_back(tile);
        }
    }

    grid[y][x].possibleTiles = newPossibilities;

    if (newPossibilities.size() == 1) {
        grid[y][x].tile = newPossibilities[0];
        grid[y][x].collapsed = true;
    }
}

// Алгоритм коллапса волновой функции
void collapseWaveFunction(std::vector<std::vector<Cell>>& grid) {
    bool collapsed = false;
    while (!collapsed) {
        collapsed = true;
        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                if (!grid[y][x].collapsed) {
                    updateCellPossibilities(grid, x, y);
                    if (!grid[y][x].collapsed) {
                        collapsed = false;
                    }
                }
            }
        }

        // Поиск клетки с минимальной неопределенностью
        int minOptions = 5;  // Больше всех возможных тайлов
        int minX = -1, minY = -1;

        for (int y = 0; y < GRID_HEIGHT; ++y) {
            for (int x = 0; x < GRID_WIDTH; ++x) {
                if (!grid[y][x].collapsed && grid[y][x].possibleTiles.size() < minOptions) {
                    minOptions = grid[y][x].possibleTiles.size();
                    minX = x;
                    minY = y;
                }
            }
        }

        if (minX != -1 && minY != -1) {
            grid[minY][minX].tile = chooseRandomTile(grid[minY][minX].possibleTiles);
            grid[minY][minX].collapsed = true;
        }
    }
}

// Отображение сетки
void printGrid(const std::vector<std::vector<Cell>>& grid) {
    for (int y = 0; y < GRID_HEIGHT; ++y) {
        for (int x = 0; x < GRID_WIDTH; ++x) {
            switch (grid[y][x].tile) {
                case GRASS: std::cout << "G "; break;
                case WATER: std::cout << "W "; break;
                case SAND: std::cout << "S "; break;
                case MOUNTAIN: std::cout << "M "; break;
                default: std::cout << ". "; break;
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    std::srand(std::time(0));

    // Инициализация сетки
    std::vector<std::vector<Cell>> grid(GRID_HEIGHT, std::vector<Cell>(GRID_WIDTH));

    initializeGrid(grid);
    collapseWaveFunction(grid);
    printGrid(grid);

    return 0;
}
