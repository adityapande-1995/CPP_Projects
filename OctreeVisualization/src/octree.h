#pragma once

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

struct Point3D {
    glm::vec3 position;
};

struct Cube {
    glm::vec3 center;
    glm::vec3 halfSize;

    bool contains(const Point3D& point) const {
        return (point.position.x >= center.x - halfSize.x && point.position.x <= center.x + halfSize.x &&
                point.position.y >= center.y - halfSize.y && point.position.y <= center.y + halfSize.y &&
                point.position.z >= center.z - halfSize.z && point.position.z <= center.z + halfSize.z);
    }

    bool intersects(const Cube& other) const {
        return !(other.center.x - other.halfSize.x > center.x + halfSize.x ||
                 other.center.x + other.halfSize.x < center.x - halfSize.x ||
                 other.center.y - other.halfSize.y > center.y + halfSize.y ||
                 other.center.y + other.halfSize.y < center.y - halfSize.y ||
                 other.center.z - other.halfSize.z > center.z + halfSize.z ||
                 other.center.z + other.halfSize.z < center.z - halfSize.z);
    }
};

class Octree {
public:
    Octree(Cube boundary, int capacity)
        : boundary(boundary), capacity(capacity), divided(false) {}

    bool insert(const Point3D& point) {
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

            if (children[0]->insert(point) || children[1]->insert(point) ||
                children[2]->insert(point) || children[3]->insert(point) ||
                children[4]->insert(point) || children[5]->insert(point) ||
                children[6]->insert(point) || children[7]->insert(point)) {
                return true;
            }
        }

        return false;
    }

    void draw() const {
        glBegin(GL_LINES);
        drawCube(boundary);
        glEnd();

        for (const auto& point : points) {
            glPointSize(2.0f);
            glBegin(GL_POINTS);
            glVertex3f(point.position.x, point.position.y, point.position.z);
            glEnd();
        }

        if (divided) {
            for (const auto& child : children) {
                child->draw();
            }
        }
    }

private:
    void subdivide() {
        glm::vec3 newHalfSize = boundary.halfSize / 2.0f;
        glm::vec3 offsets[8] = {
            glm::vec3(-newHalfSize.x, -newHalfSize.y, -newHalfSize.z),
            glm::vec3( newHalfSize.x, -newHalfSize.y, -newHalfSize.z),
            glm::vec3(-newHalfSize.x,  newHalfSize.y, -newHalfSize.z),
            glm::vec3( newHalfSize.x,  newHalfSize.y, -newHalfSize.z),
            glm::vec3(-newHalfSize.x, -newHalfSize.y,  newHalfSize.z),
            glm::vec3( newHalfSize.x, -newHalfSize.y,  newHalfSize.z),
            glm::vec3(-newHalfSize.x,  newHalfSize.y,  newHalfSize.z),
            glm::vec3( newHalfSize.x,  newHalfSize.y,  newHalfSize.z)
        };

        for (int i = 0; i < 8; ++i) {
            children[i] = std::make_unique<Octree>(Cube{boundary.center + offsets[i], newHalfSize}, capacity);
        }

        divided = true;
    }

    void drawCube(const Cube& cube) const {
        glm::vec3 corners[8] = {
            cube.center + glm::vec3(-cube.halfSize.x, -cube.halfSize.y, -cube.halfSize.z),
            cube.center + glm::vec3( cube.halfSize.x, -cube.halfSize.y, -cube.halfSize.z),
            cube.center + glm::vec3( cube.halfSize.x,  cube.halfSize.y, -cube.halfSize.z),
            cube.center + glm::vec3(-cube.halfSize.x,  cube.halfSize.y, -cube.halfSize.z),
            cube.center + glm::vec3(-cube.halfSize.x, -cube.halfSize.y,  cube.halfSize.z),
            cube.center + glm::vec3( cube.halfSize.x, -cube.halfSize.y,  cube.halfSize.z),
            cube.center + glm::vec3( cube.halfSize.x,  cube.halfSize.y,  cube.halfSize.z),
            cube.center + glm::vec3(-cube.halfSize.x,  cube.halfSize.y,  cube.halfSize.z)
        };

        // Draw lines between the corners to form the edges of the cube
        for (int i = 0; i < 4; ++i) {
            glVertex3fv(&corners[i].x);
            glVertex3fv(&corners[(i + 1) % 4].x);
            glVertex3fv(&corners[i + 4].x);
            glVertex3fv(&corners[(i + 1) % 4 + 4].x);
            glVertex3fv(&corners[i].x);
            glVertex3fv(&corners[i + 4].x);
        }
    }

    Cube boundary;
    int capacity;
    std::vector<Point3D> points;
    bool divided;
    std::unique_ptr<Octree> children[8];
};
