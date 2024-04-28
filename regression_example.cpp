#include <iostream>
#include <vector>
#include <random>
#include <cmath>

using namespace std;

//Struct to hold an X-Y coordinate for a point in 2 dimensions
struct Point{
    int X;
    int Y;
};


vector<Point> generate_points(int min_point_val, int max_point_val, int number_of_points){

    random_device rd;  //Seed for random number
    mt19937 gen(rd());  //Popular pseuodo-random number generator engine
	        
    // Define the distribution for integers between -10 and 10
    uniform_int_distribution<int> dis(min_point_val,max_point_val);
		  
    //Create a vector of X-Y points
    vector<Point> Points;

    //Generate points.
    for(int i=0; i < number_of_points; ++i){
	Point point_val;

	//Generate random numbers for X and Y co-ordinates of a each point.
        int randomNum = dis(gen);
        point_val.X = randomNum;
        int randomNum2 = dis(gen);
        point_val.Y = randomNum2;
	Points.push_back(point_val);
    }
	
	return Points;
}



void regression(vector<Point> Points){

    //Regression
    float Sxy;
    float Sxx;
    float Syy;

    float sum_x_times_y = 0; 
    float sum_x = 0;
    float sum_y = 0;
    float x_squared = 0;
    float sum_x_squared = 0;
    float y_squared = 0;
    float sum_y_squared = 0;
    float mean_x;
    float mean_y;
    float b;
    float a;
    float r;
    for (const auto& element : Points) {
        sum_x_times_y = sum_x_times_y + element.X*element.Y;
	sum_x = sum_x + element.X;
	sum_y = sum_y + element.Y;
	x_squared = x_squared + element.X*element.X;
	y_squared = y_squared + element.Y*element.Y;
	}

    sum_x_squared = (sum_x * sum_x)/Points.size();
    sum_y_squared = (sum_y * sum_y)/Points.size();
    
    Sxy = sum_x_times_y - (sum_x*sum_y)/Points.size();
    Sxx = x_squared - sum_x_squared;
    Syy = y_squared - sum_y_squared;
    b = Sxy/Sxx;
    mean_x = sum_x/Points.size();
    mean_y = sum_y/Points.size();
    a = mean_y - b*mean_x;
    r = Sxy/sqrt(Sxx*Syy);
    cout << "The fit line for these points is y = " << a << " + " << b << "x" << "\n";
    cout << "The correlation coefficient is " << r << "\n";
}


int main(){

    vector<Point> Points = generate_points(-10,10,10);    
	
    //Print out points in vector.  Each point is an element in the vector.
    for (const auto& element : Points) {
        cout << element.X << "," << element.Y << "\n";
	}
    
    regression(Points);

    return 0;	
}
