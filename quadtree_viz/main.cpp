#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

struct Point {
    double x, y;
};

struct Rectangle {
    double x, y, w, h;

    bool contains(const Point& point) const {
        return point.x >= x - w && point.x <= x + w &&
               point.y >= y - h && point.y <= y + h;
    }

    bool intersects(const Rectangle& range) const {
        return !(range.x - range.w > x + w ||
                 range.x + range.w < x - w ||
                 range.y - range.h > y + h ||
                 range.y + range.h < y - h);
    }
};

class Quadtree {
public:
    Quadtree(Rectangle boundary, int capacity)
        : boundary(boundary), capacity(capacity), divided(false) {}

    bool insert(const Point& point) {
        if (!boundary.contains(point)) {
            return false;
        }

        if (points.size() < capacity) {
            points.push_back(point);
            return true;
        } else {
            if (!divided) {
                subdivide();
            }

            if (northeast->insert(point) || northwest->insert(point) ||
                southeast->insert(point) || southwest->insert(point)) {
                return true;
            }
        }

        return false;
    }

    void query(const Rectangle& range, std::vector<Point>& found) const {
        if (!boundary.intersects(range)) {
            return;
        }

        for (const auto& point : points) {
            if (range.contains(point)) {
                found.push_back(point);
            }
        }

        if (divided) {
            northeast->query(range, found);
            northwest->query(range, found);
            southeast->query(range, found);
            southwest->query(range, found);
        }
    }

    void draw(SDL_Renderer* renderer) const {
        SDL_Rect rect = {
            static_cast<int>(boundary.x - boundary.w),
            static_cast<int>(boundary.y - boundary.h),
            static_cast<int>(boundary.w * 2),
            static_cast<int>(boundary.h * 2)
        };
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &rect);

        for (const auto& point : points) {
            SDL_RenderDrawPoint(renderer, static_cast<int>(point.x), static_cast<int>(point.y));
        }

        if (divided) {
            northeast->draw(renderer);
            northwest->draw(renderer);
            southeast->draw(renderer);
            southwest->draw(renderer);
        }
    }

private:
    void subdivide() {
        double x = boundary.x;
        double y = boundary.y;
        double w = boundary.w / 2;
        double h = boundary.h / 2;

        Rectangle ne = { x + w, y - h, w, h };
        northeast = std::make_unique<Quadtree>(ne, capacity);
        Rectangle nw = { x - w, y - h, w, h };
        northwest = std::make_unique<Quadtree>(nw, capacity);
        Rectangle se = { x + w, y + h, w, h };
        southeast = std::make_unique<Quadtree>(se, capacity);
        Rectangle sw = { x - w, y + h, w, h };
        southwest = std::make_unique<Quadtree>(sw, capacity);

        divided = true;
    }

    Rectangle boundary;
    int capacity;
    std::vector<Point> points;
    bool divided;
    std::unique_ptr<Quadtree> northeast;
    std::unique_ptr<Quadtree> northwest;
    std::unique_ptr<Quadtree> southeast;
    std::unique_ptr<Quadtree> southwest;
};

void draw_random_walk(Quadtree& quadtree) {
    std::srand(std::time(nullptr));
    double x = SCREEN_WIDTH / 2.0;
    double y = SCREEN_HEIGHT / 2.0;
    double step_size = 10.0;

    for (int i = 0; i < 500; ++i) {
        int direction = std::rand() % 4;
        switch (direction) {
            case 0: x += step_size; break; // right
            case 1: x -= step_size; break; // left
            case 2: y += step_size; break; // down
            case 3: y -= step_size; break; // up
        }

        // Ensure the point stays within the canvas
        x = std::min(std::max(x, 0.0), static_cast<double>(SCREEN_WIDTH));
        y = std::min(std::max(y, 0.0), static_cast<double>(SCREEN_HEIGHT));

        quadtree.insert(Point{x, y});
    }
}

int main(int argc, char* argv[]) {
    bool interactive = (argc > 1 && std::string(argv[1]) == "--interactive");

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Quadtree Visualization", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    Rectangle boundary = { SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0, SCREEN_WIDTH / 2.0, SCREEN_HEIGHT / 2.0 };
    Quadtree quadtree(boundary, 4);

    if (!interactive) {
        draw_random_walk(quadtree);
    }

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (interactive && e.type == SDL_MOUSEMOTION) {
                Point point = { static_cast<double>(e.motion.x), static_cast<double>(e.motion.y) };
                quadtree.insert(point);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        quadtree.draw(renderer);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
