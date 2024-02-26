#include <vector>
#include <cmath>
#include <limits>
#include<fstream>
#include<iostream>
#include<ctime>
#include<algorithm>
#include<chrono>



using namespace std;

struct Point {
    int x, y;
};

float distance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void twoOptSwap(std::vector<int>& route, int i, int k) {
    while (i < k) {
        std::swap(route[i], route[k]);
        i++;
        k--;
    }
}



float calculateTotalDistance(const std::vector<Point>& points, const std::vector<int>& route) {
    float totalDist = 0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        totalDist += distance(points[route[i]], points[route[i + 1]]);
    }
    totalDist += distance(points[route.back()], points[route.front()]); // Return to start
    return totalDist;
}



std::vector<int> twoOpt(const std::vector<Point>& points, std::vector<int> route) {
    // Record the start time
    auto start_time = std::chrono::high_resolution_clock::now();
    srand(time(NULL));
    int epoch, rand_index1, rand_index2, max_index;
    int counter = 0;
    max_index = route.size() - 1;
    float bestDistance = calculateTotalDistance(points, route);
    for (epoch = 0; epoch <= 3 * max_index; epoch++) {
        
        
        int rand_index1 = rand() % max_index;
        int rand_index2 = rand() % max_index;
       
        twoOptSwap(route, rand_index1, rand_index2);
        

        float newDistance = calculateTotalDistance(points, route);
        if (newDistance < bestDistance) {
            bestDistance = newDistance;
            epoch = 0;
            
        }
        else {
            
            twoOptSwap(route, rand_index1, rand_index2); // Swap back if no improvement
        }
        if ((counter % 60000 ) == 0) {
            auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                std::chrono::high_resolution_clock::now() - start_time);
            cout << "Time: " << duration.count() << "s" << endl;
            for (int i = 0; i < route.size(); i++) {
                
                cout << route[i] << "->";
            }
            cout << "Current path lenght: " << bestDistance << endl << endl;
        }
        counter += 1;
    }
    return route;
}


/*
std::vector<int> twoOpt(const std::vector<Point>& points, std::vector<int> route) {
    bool improvement = true;
    while (improvement) {
        improvement = false;
        double bestDistance = calculateTotalDistance(points, route);

        for (size_t i = 0; i < route.size() - 1; ++i) {
            for (size_t k = i + 1; k < route.size(); ++k) {
                twoOptSwap(route, i, k);
                double newDistance = calculateTotalDistance(points, route);
                if (newDistance < bestDistance) {
                    bestDistance = newDistance;
                    improvement = true;
                }
                else {
                    twoOptSwap(route, i, k); // Swap back if no improvement
                }
                if (i % 100 == 0 && k == i + 1)
                    cout << " JD " << endl;
            }
        }
    }
    return route;
}*/


int main() {
    ios::sync_with_stdio(false);


    // Assume 'points' is a vector of 'Point' objects representing the coordinates of the cities.
    // The 'route' is initially a sequential order of cities.
    std::vector<Point> points; // Fill with actual data

    ifstream file;
    struct Point temp;
    file.open("test3.txt");
    int x;

    while (file>> x >>temp.x >> temp.y){
         
        points.push_back(temp);
    }

    file.close();




    std::vector<int> route(points.size());
    for (int i = 0; i < points.size(); ++i) {
        route[i] = i;
    }

    



    // Apply 2-opt algorithm
    route = twoOpt(points, route);
    for (int i = 0; i < route.size(); i++) {
        cout << route[i] << "->";
    }
    cout << endl << calculateTotalDistance(points, route);

    // Output or use the improved route
}