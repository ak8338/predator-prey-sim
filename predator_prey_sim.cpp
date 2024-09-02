
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int GRID_SIZE = 20;
const int ANT_BREED_STEPS = 3;
const int DOODLEBUG_BREED_STEPS = 8;
const int DOODLEBUG_STARVE_STEPS = 3;
const int NUM_DIRECTIONS = 4;
const int dx[NUM_DIRECTIONS] = { -1, 1, 0, 0 };
const int dy[NUM_DIRECTIONS] = { 0, 0, -1, 1 };

class Organism {
public:
    Organism(int x, int y) : x(x), y(y), timeSteps(0), moved(false) {}
    virtual ~Organism() {}
    virtual void move(Organism* grid[GRID_SIZE][GRID_SIZE]) = 0;
    virtual void breed(Organism* grid[GRID_SIZE][GRID_SIZE]) = 0;
    virtual bool isPrey() = 0;
    int x, y, timeSteps;
    bool moved;
};

class Ant : public Organism {
public:
    Ant(int x, int y) : Organism(x, y) {}
    virtual void move(Organism* grid[GRID_SIZE][GRID_SIZE]) override;
    virtual void breed(Organism* grid[GRID_SIZE][GRID_SIZE]) override;
    virtual bool isPrey() override { return true; }
};

class Doodlebug : public Organism {
public:
    Doodlebug(int x, int y) : Organism(x, y), timeSinceLastMeal(0) {}
    virtual void move(Organism* grid[GRID_SIZE][GRID_SIZE]) override;
    virtual void breed(Organism* grid[GRID_SIZE][GRID_SIZE]) override;
    virtual bool isPrey() override { return false; }
    int timeSinceLastMeal;
};

void Ant::move(Organism* grid[GRID_SIZE][GRID_SIZE]) {
    int dir = rand() % NUM_DIRECTIONS;
    int newX = x + dx[dir];
    int newY = y + dy[dir];

    if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE && grid[newX][newY] == nullptr) {
        grid[newX][newY] = grid[x][y];
        grid[x][y] = nullptr;
        x = newX;
        y = newY;
    }
    timeSteps++;
    moved = true;
}

void Ant::breed(Organism* grid[GRID_SIZE][GRID_SIZE]) {
    if (timeSteps >= ANT_BREED_STEPS) {
        for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE && grid[newX][newY] == nullptr) {
                grid[newX][newY] = new Ant(newX, newY);
                timeSteps = 0;
                return;
            }
        }
    }
}

void Doodlebug::move(Organism* grid[GRID_SIZE][GRID_SIZE]) {
    for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
        int newX = x + dx[dir];
        int newY = y + dy[dir];

        if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE) {
            Organism* target = grid[newX][newY];
            if (target != nullptr && target->isPrey()) {
                delete target;
                grid[newX][newY] = grid[x][y];
                grid[x][y] = nullptr;
                x = newX;
                y = newY;
                timeSinceLastMeal = 0;
                timeSteps++;
                moved = true;
                return;
            }
        }
    }

    int dir = rand() % NUM_DIRECTIONS;
    int newX = x + dx[dir];
    int newY = y + dy[dir];

    if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE && grid[newX][newY] == nullptr) {
        grid[newX][newY] = grid[x][y];
        grid[x][y] = nullptr;
        x = newX;
        y = newY;
    }
    timeSinceLastMeal++;
    timeSteps++;
    moved = true;
}

void Doodlebug::breed(Organism* grid[GRID_SIZE][GRID_SIZE]) {
    if (timeSteps >= DOODLEBUG_BREED_STEPS) {
        for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {
            int newX = x + dx[dir];
            int newY = y + dy[dir];

            if (newX >= 0 && newX < GRID_SIZE && newY >= 0 && newY < GRID_SIZE && grid[newX][newY] == nullptr) {
                grid[newX][newY] = new Doodlebug(newX, newY);
                timeSteps = 0;
                return;
            }
        }
    }
}

void printGrid(Organism* grid[GRID_SIZE][GRID_SIZE]) {
    for (int i = 0; i < GRID_SIZE; i++) {
        for (int j = 0; j < GRID_SIZE; j++) {
            if (grid[i][j] == nullptr) {
                cout << "-";
            }
            else if (grid[i][j]->isPrey()) {
                cout << "o";
            }
            else {
                cout << "X";
            }
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));
    Organism* grid[GRID_SIZE][GRID_SIZE] = { nullptr };

    for (int i = 0; i < 5; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        while (grid[x][y] != nullptr) {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        }
        grid[x][y] = new Doodlebug(x, y);
    }

    for (int i = 0; i < 100; i++) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        while (grid[x][y] != nullptr) {
            x = rand() % GRID_SIZE;
            y = rand() % GRID_SIZE;
        }
        grid[x][y] = new Ant(x, y);
    }

    while (true) {
        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                Organism* critter = grid[i][j];
                if (critter && !critter->isPrey() && !critter->moved) {
                    critter->move(grid);
                    critter->breed(grid);
                }
            }
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                Organism* critter = grid[i][j];
                if (critter && critter->isPrey() && !critter->moved) {
                    critter->move(grid);
                    critter->breed(grid);
                }
            }
        }

        for (int i = 0; i < GRID_SIZE; i++) {
            for (int j = 0; j < GRID_SIZE; j++) {
                Organism* critter = grid[i][j];
                if (critter) {
                    if (!critter->isPrey() && static_cast<Doodlebug*>(critter)->timeSinceLastMeal >= DOODLEBUG_STARVE_STEPS) {
                        delete critter;
                        grid[i][j] = nullptr;
                    }
                    else {
                        critter->moved = false;
                    }
                }
            }
        }

        printGrid(grid);

        cout << "Press Enter to move to the next time step...";
        cin.get();
    }

    return 0;
}