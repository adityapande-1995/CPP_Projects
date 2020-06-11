#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include "matplotlibcpp.h"
namespace plt = matplotlibcpp;

// Limits of the graph
int Y_MIN = 0 ; int Y_MAX = 50;
int X_MIN = 0 ; int X_MAX = 50;

class Node{
public:
  int x,y;
  Node(){this->x = 0 ; this->y = 0;}
  Node(int x , int y){this->x = x ; this->y = y;}
  void print(){std::cout << this->x << " " << this->y;}

  // For hash collisions
  bool operator==(const Node& other) const{
    return (this->x == other.x && this->y == other.y);
  }
  bool operator!=(const Node& other) const{
    return !(this->x == other.x && this->y == other.y);
  }
};

class NodeHashFunction {
public:
  int operator()(const Node& p) const
  {
    return p.x*100 + p.y ;
  }
};

// Printing dist hashmap
void print_dist(auto& dist){
  std::cout << "** Printing distances to each node **" << std::endl;
  for (auto it = dist.cbegin() ; it != dist.cend() ; ++it ){
    std::cout << it->first.x << " " << it->first.y << " ->  " << it->second << std::endl;
  } 
}

// Printing previous node tracking
void print_prev(auto& prev){
  std::cout << "** Printing previous nodes for tracing the path **" << std::endl;
  for (auto it = prev.cbegin() ; it != prev.cend() ; ++it ){
    std::cout << it->first.x << " " << it->first.y << " ->  " << it->second.x << " " << it->second.y  << std::endl;
  } 
}

// Whether a node is in map
bool inMap(Node t){
  bool c1 = t.x >= X_MIN && t.x < X_MAX && t.y >= Y_MIN && t.y < Y_MAX;
  bool c2 = (pow(t.x - X_MAX/2 + 10  ,2) + pow(t.y - Y_MAX/2 + 5  ,2) - pow(12 ,2)  > 0 );
  bool c3 = (pow(t.x - 30  ,2) + pow(t.y - 30   ,2) - pow(4 ,2)  > 0 );
  return c1 && c2 && c3;
}

// Return neighbours of a node
std::vector<Node> neighbours(Node U){
  std::vector<Node> neb;

  if (inMap( Node(U.x + 1 , U.y + 1)  )){ neb.push_back( Node(U.x + 1 , U.y + 1)   );  }
  if (inMap( Node(U.x + 1 , U.y + 0)  )){ neb.push_back( Node(U.x + 1 , U.y + 0)   );  }
  if (inMap( Node(U.x + 1 , U.y - 1)  )){ neb.push_back( Node(U.x + 1 , U.y - 1)   );  }

  if (inMap( Node(U.x + 0 , U.y + 1)  )){ neb.push_back( Node(U.x + 0 , U.y + 1)   );  }
  if (inMap( Node(U.x + 0 , U.y - 1)  )){ neb.push_back( Node(U.x + 0 , U.y - 1)   );  }

  if (inMap( Node(U.x - 1 , U.y + 1)  )){ neb.push_back( Node(U.x - 1 , U.y + 1)   );  }
  if (inMap( Node(U.x - 1 , U.y + 0)  )){ neb.push_back( Node(U.x - 1 , U.y + 0)   );  }
  if (inMap( Node(U.x - 1 , U.y - 1)  )){ neb.push_back( Node(U.x - 1 , U.y - 1)   );  }

  return neb;
}

std::vector<Node> Dijkstra(){
  //Node STOP = Node(26,26);
  Node STOP = Node(X_MAX -1,Y_MAX -1);
  Node START = Node(0,0);

  Node v;
  std::vector <Node> Nebs;
  float alt;

  std::unordered_map <Node,float,NodeHashFunction> dist;
  std::unordered_map <Node, Node, NodeHashFunction> previous;
  std::vector <Node> Q;

  // Init
  for(int i = X_MIN ; i < X_MAX ; i++){
    for(int j = Y_MIN ; j < Y_MAX ; j++){
      dist[ Node(i,j) ] = 10000;
      previous[ Node(i,j) ] = Node(-1,-1);
      Q.push_back( Node(i,j) );
    }
  }

  dist[Node(0,0)] = 0;

  while (Q.size() > 0){
    // Get node with smallest dist in Q
    auto u = std::min_element(Q.begin(), Q.end(), [&dist](Node m, Node n){return dist[m] < dist[n];} );
    Node U = *u;
    // Remove u from Q
    Q.erase(u);
    // For each neighbout v of u
    Nebs = neighbours(U);
    for (int k = 0 ; k < Nebs.size() ; k++){
      v = Nebs[k];
      alt = dist[U] + sqrt( pow(U.x - v.x,2) + pow(U.y - v.y,2));
      if (alt < dist[v]){
        dist[v] = alt;
        previous[v] = U;
      }
    }
  }

  // print_dist(dist);

  std::cout << "-- Distance to goal : " << dist[STOP] << std::endl;

  // Extract path
  std::vector <Node> path;

  Node temp = STOP;
  path.push_back(temp);
  while (temp != Node(0,0)){
    temp = previous[temp];
    path.push_back(temp);
  }

  return path;
}

int main() {
  auto path = Dijkstra();

  //Print path
  std::cout << " --- Path ---" << std::endl;
  for (int i = 0 ; i < path.size(); i++){
    path[i].print();
    std::cout << "\n";
  }

  // Plot the grid itself
  std::vector<int> grid_x; std::vector<int> grid_y;
  std::vector<int> ngrid_x; std::vector<int> ngrid_y;
  for (int i = X_MIN ; i < X_MAX ; i++){
    for (int j = X_MIN ; j < X_MAX ; j++){
      if (inMap(Node(i,j))){
        grid_x.push_back(i) ; grid_y.push_back(j) ;
      }
      else{
        ngrid_x.push_back(i) ; ngrid_y.push_back(j) ;
      }
    }
  }

  plt::scatter(grid_x,grid_y);
  plt::scatter(ngrid_x,ngrid_y);
  // Drawing the path
  std::vector<int> path_x; std::vector<int> path_y;
  for (int i = 0 ; i < path.size(); i++){
    path_x.push_back(path[i].x) ; path_y.push_back(path[i].y) ;
  }
  plt::plot(path_x, path_y);


  plt::show();
  return 0;
}
