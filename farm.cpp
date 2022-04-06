#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>


using namespace std;

int r_indexx = 0;
unordered_map<int,int>memo2;


void generate_n(int n){
    ofstream n_file;
    n_file.open("n_data.txt");
    srand((unsigned)time(NULL));
    for(int i = 0; i < n; i++){
        int x = 32768;
        int r_num = rand()%x + 1;
        if(r_num%2==0){
            r_num = -1*r_num;
        }
        n_file << r_num << " ";
    }
    n_file.close();
}

void generate_mn(int m, int n){
    ofstream mn_file;
    mn_file.open("mn_data.txt");
    srand((unsigned)time(NULL));
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j ++){
            int x = 32768;
            int r_num = rand()%x + 1;
            if(r_num%2==0 && r_num%3==0){
                r_num = -1*r_num;
            }
            mn_file << r_num << " ";
        }
        
    }
    mn_file.close();
}

vector<int>get_arr(int size, string f){
    ifstream file;
    file.open(f);
    vector<int>arr(size);

    for(int i = 0; i < size; i ++){
        file >> arr[i];
    }
    file.close();

    return arr;
}

vector<vector<int> >get_matrix(int m, int n, string f){
    ifstream file;
    file.open(f);
    vector<vector<int> >matrix(n, vector<int>(m, 0));

    for(int i = 0; i < n; i ++){
        for(int j = 0; j < m; j ++){
            file >> matrix[i][j];
        }
    }
    file.close();

    return matrix;
}

void Task1(int n, vector<int>&nums){

    int maxx = INT_MIN;
    int l, r;
    for (int i = 0; i < n; i++){ 
        for (int j = i; j < n; j++){ //iterate from i = 1 to n. this will create a range from i to j.
            int curr_sum = 0; 
            for (int k = i; k <= j; k++){ //we want to create a sub array from i to j and sum up the values.
                curr_sum = curr_sum + nums[k]; //the current sum is calculated here.
            }
            if(maxx < curr_sum){ //check if it is a new possible max.
                maxx = curr_sum;
                l = i; r = j;
            }
            
        }
    }
    cout << "l: " << l << " r: " << r << " sum: "  << maxx << "\n";
}

void Task2(int n, vector<int>&nums){
    
    int maxx = INT_MIN;
    int l = 0,r = 0;
   
    int dp[n+1]; dp[0] = 0; //initialize dp array with dp[0] = 0.
    for(int i = 0; i < n; i ++){ //calculate the consecutive sum from i = 0 to n. 
        dp[i+1]= nums[i]+dp[i];
    }
    for(int i = 1; i < n; i ++){
        int curr_sum = max(nums[i-1], dp[i]); //calculate weather to start from dp[i] or nums[i] depending on which value is greater. 
        for(int j = i; j < n; j++){ //calculate the sum from sub array i to j
            curr_sum+=nums[j];
            if(curr_sum > maxx){ //keeps track of the sum and sees if it is greater than the maxx.
                maxx = curr_sum;
                l = i-1; r = j;
            }

        }
    }

    cout << "l: " << l << " r: " << r << " sum: "  << maxx << "\n";
}

int Task3a(vector<int>&nums, int idx, unordered_map<int,int>&memo, int &r_index){
    if(idx >= nums.size()) return 0;
    if(memo.count(idx)) return memo[idx];
    int curr = nums[idx];
    int sum = nums[idx] + Task3a(nums, idx+1, memo, r_index);
    
    if(curr < sum) {
        memo[idx] = sum;
    }
    else {
        memo[idx] = curr;
        r_indexx = idx;
    }
    return memo[idx];
}

void Task3b(int n, vector<int>&nums){

   int dp[n]; //initialize the dp array that will keep track of the greates element so far.
   dp[0] = nums[0];
   int l = 0, r = 0; 

   int sum = INT_MIN;
   for(int i = 1; i < n; i ++){
       dp[i] = max(dp[i-1]+nums[i], nums[i]); //checks if the sum that you have made so far along with the current number is greater. if not
                                              // it will reset the value to just the current number and iterate from there.

       if(dp[i-1]+nums[i] < nums[i]){
           dp[i] = nums[i];
           l = i;
       }
       else {
           dp[i] = dp[i-1]+nums[i];
       }
       if(sum < dp[i]){
           sum = dp[i];
           r = i;
       }
   }
    cout << "l: " << l << " r: " << r << " sum: "  << sum << "\n";

}

void Task4(int m, int n, vector<vector<int> >&nums){
    int curr_sum = 0; int maxx = INT_MIN; int top_x = 0, top_y = 0, bottom_x = 0, bottom_y = 0;
    
    for(int x = 0; x < n; x ++){ //starting from the first row to the last row
        for (int y = 0; y < m; y ++){ //starting from the first column to last column
            for(int x1 = 0; x1 < n; x1++){ 
                
                for(int y1 = 0; y1 < m; y1 ++){
                    curr_sum = 0;
                    for(int i = x; i <= x1; i ++){  //here we mark the starting point and end point of rectangle
                        for(int j = y; j <= y1; j ++){ //the starting top left = x,y and ending is x1, y1
                            curr_sum+=nums[i][j]; //sum up all the values in starting rectangle. 
                        }
                    }
                    if(curr_sum > maxx){
                        top_x = x; top_y = y;
                        bottom_x = x1; bottom_y = y1;
                        maxx = curr_sum;
                    }
                }

            }
        }
    }

    cout << "x1: " << top_x << " y1: " << top_y <<  " x2: " << bottom_x << " y2: " << bottom_y << " sum: "  << maxx << "\n";

}

void Task5(int m, int n, vector<vector<int> >&nums){

    
    int maxx = INT_MIN;
    int col = m; int row = n; 

    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

    vector<vector<int> > prefix(n,vector<int>(m, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            prefix[i][j] = nums[i][j]; // calculation prefix sum for each row
    }
    

    int rows = n; int cols = m;

    for(int r=0; r<rows; r++) {
        for(int c=0; c<cols; c++) {

            if(r > 0) 
               prefix[r][c] += prefix[r-1][c]; //add cell from column before
            
            if(c > 0) 
               prefix[r][c] += prefix[r][c-1]; // add cell from the row before
            
            if(r > 0 && c > 0) 
               prefix[r][c] -= prefix[r-1][c-1]; //remove duplicated val from diagonal expansion
         }
    } 
    
    int curr_sum = 0;

    for(int i = 0; i < row; i ++){ //calculate the x val of top right of rectangle
        for(int j = 0; j < col; j ++){ //calculate the y val of top right of rectangle
            for(int x = i; x < row; x ++) { //calculate the x val of bottom left of rectangle
                for(int y = j; y < col; y ++){ //calculate the y val of bottom left of rectangle

                    curr_sum = prefix[x][y];

                    //remove values of previous part of matrix that is before current columns and rows

                    if(i > 0)  
                        curr_sum -= prefix[i-1][y];
                    if(j > 0)  
                        curr_sum -= prefix[x][j-1];
                    if(i > 0 && j > 0)  
                        curr_sum += prefix[i-1][j-1];

                    if(curr_sum > maxx){ //keep track of max_sum
                        x1 = i, y1 = j, x2 = x, y2 = y;
                        maxx = curr_sum;
                    }
                }
            }
        }
    }

    cout << "x1: " << x1 << " y1: " << y1 <<  " x2: " << x2 << " y2: " << y2 << " sum: "  << maxx << "\n";
    
}

void Task6(int m, int n, vector<vector<int> > &matrix){

    vector<vector<int> > dp(n,vector<int>(m, 0));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++)
            dp[i][j] = matrix[i][j];  // make a hard copy of matrix
    }
   
    for(int i=0;i<n;i++){
        for(int j=1;j<m;j++)
            dp[i][j] += dp[i][j-1];  // calculation prefix sum for each row
    }
    // store indices of submatrix with maximum sum
    int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
    int maxx = INT_MIN;
    
    for(int col1=0;col1<m;col1++){ //after calcilating the sums, I use Kadane's algorithm to find the max sum in the vector

        
        for(int col2=col1;col2<m;col2++){
            int tmp[n]; // stores the sum between two columns for each row
            
            for(int row=0;row<n;row++)
                tmp[row] = dp[row][col2] - (col1>0 ? dp[row][col1-1] : 0);
            
            int curr_sum = 0;
            int curr_max_so_far = 0;
            int row1 = 0, row2 = -1;
            int tmpStartRow = 0; 
         
            
            for(int i=0;i<n;i++){ //calculates the sum of the current rectangle
                
                curr_sum += tmp[i];
                
                if(curr_sum < 0) {
                    curr_sum = 0;
                    tmpStartRow = i+1;
                } 
                
                else if(curr_sum > curr_max_so_far) {
                    curr_max_so_far = curr_sum;
                    row1 = tmpStartRow;
                    row2 = i;
                }
            }

            if(row2 == -1) {
                curr_max_so_far = tmp[0];
                row1 = 0;
                row2 = 0;
                for(int i=1;i<n;i++){
                    if(tmp[i] > curr_max_so_far){
                        curr_max_so_far = tmp[0];
                        row1 = i;
                        row2 = i;
                    }
                }
            }

            if(curr_max_so_far > maxx){
                maxx = curr_max_so_far;
                x1 = col1;
                x2 = col2;
                y1 = row1;
                y2 = row2;
            }
        }
    }

    cout << "x1: " << x1 << " y1: " << y1 <<  " x2: " << x2 << " y2: " << y2 << " sum: "  << maxx << "\n";
}

int main(int argc, char *argv[]){

    string input = "";
    if(argc > 1){
        input = argv[1];
    }

    if(input == "1"){
        int n; cin >> n;
        cout << endl;
        vector<int>nums(n);
        for(int i = 0; i < n; i ++){
            cin >> nums[i];
        }
        if(n != 1) Task1(n, nums);
        else cout << "l: 0 r: 0 sum: " << nums[0];
    }
    else if(input == "2"){
        int n; cin >> n;
        cout << endl;
        vector<int>nums(n);
        for(int i = 0; i < n; i ++){
            cin >> nums[i];
        }
        if(n != 1) Task2(n, nums);
        else cout << "l: 0 r: 0 sum: " << nums[0];
    }
    else if(input == "3a"){
        int n; cin >> n;
        cout << endl;
        vector<int>nums(n);
        for(int i = 0; i < n; i ++){
            cin >> nums[i];
        }
       
        if(n != 1) {
            unordered_map<int,int>memo;
            int ret = INT_MIN; int l = 0, r = 0;
            for(int i = 0; i < nums.size(); i ++){
                int val =  Task3a(nums, i, memo, r);
                if(ret < val){
                    ret = val;
                    l = i;
                    r = r_indexx;
                }
            }
            cout << "l: " << l << " r: " << r_indexx << " sum: "  << ret << "\n";
        }
        else cout << "l: 0 r: 0 sum: " << nums[0];
    }
    else if(input == "3b"){
        int n; cin >> n;
        cout << endl;
        vector<int>nums(n);
        for(int i = 0; i < n; i ++){
            cin >> nums[i];
        }
        if(n != 1) Task3b(n, nums);
        else cout << "l: 0 r: 0 sum: " << nums[0];
    }
    else if(input == "4"){
        int m; cin >> m; 
        int n; cin >> n; 
        cout << endl;
        vector<vector<int> >nums(n, vector<int>(m, 0));
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < m; j ++){
                cin >> nums[i][j];
            }
            cout << "\n";
            
        }
        Task4(m, n, nums);
    }
    else if(input == "5"){
        int m; cin >> m; 
        int n; cin >> n; 
        cout << endl;
        vector<vector<int> >nums(n, vector<int>(m, 0));
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < m; j ++){
                cin >> nums[i][j];
            }
        }
        Task5(m, n, nums);
    }
    else if(input == "6"){
        int m; cin >> m; 
        int n; cin >> n; 
        cout << endl;
        vector<vector<int> >nums(n, vector<int>(m, 0));
        for(int i = 0; i < n; i ++){
            for(int j = 0; j < m; j ++){
                cin >> nums[i][j];
            }            
        }
        Task6(m, n, nums);
    }
    else if(input == "experiment"){


        int input_sizes_1 [] = {1000, 2000, 3000, 4000, 5000};
        int input_sizes_2 [] = {20, 40, 60, 80, 100};

        generate_n(5000);
        generate_mn(100, 100);
        

        cout << "TASK 1" << endl;

        for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<int>nums = get_arr(input_sizes_1[i],"n_data.txt");
            Task2(input_sizes_1[i], nums);
            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_1[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";

        }

        cout << "TASK 2" << endl;

        for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<int>nums = get_arr(input_sizes_1[i],"n_data.txt");
            Task2(input_sizes_1[i], nums);
            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_1[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";
        }
        
        cout << "TASK 3a" << "\n";

        for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<int>nums = get_arr(input_sizes_1[i],"n_data.txt");
            unordered_map<int,int>memo;
            int ret = INT_MIN; int l = 0, r = 0; 
            for(int i = 0; i < nums.size(); i ++){
                int val =  Task3a(nums, i, memo2, r);
                if(ret < val){
                    ret = val;
                    l = i;
                }
            }
            cout << "l: " << l << " r: " << r_indexx << " sum: "  << ret << "\n";

            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_1[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";

        }

        cout << "TASK 3b" << endl;

        for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<int>nums = get_arr(input_sizes_1[i],"n_data.txt");
            Task3b(input_sizes_1[i], nums);
            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_1[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";

        }

        cout << "TASK 4" << endl;

         for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<vector<int> > matrix = get_matrix(input_sizes_2[i],input_sizes_2[i],"mn_data.txt");
            Task4(input_sizes_2[i],input_sizes_2[i],matrix);
            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_2[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";

        }

        cout << "TASK 5" << endl;

         for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<vector<int> > matrix = get_matrix(input_sizes_2[i],input_sizes_2[i],"mn_data.txt");
            Task5(input_sizes_2[i],input_sizes_2[i],matrix);
            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_2[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";

        }

        cout << "TASK 6" << endl;

         for(int i = 0; i < 5; i ++ ){
            std::chrono::time_point<std::chrono::system_clock> start, end;
            start = std::chrono::system_clock::now();
            vector<vector<int> > matrix = get_matrix(input_sizes_2[i],input_sizes_2[i],"mn_data.txt");
            Task6(input_sizes_2[i],input_sizes_2[i],matrix);
            end = std::chrono::system_clock::now();  
            std::chrono::duration<double> elapsed_seconds = end - start;

            cout << "duration w/ input size of " << input_sizes_2[i] << " " << elapsed_seconds.count() << "\n";
            cout << "\n";

        }
        
    }
    else {
        cout << "Invalid Input" << "\n";
    }
        
    return 0;
}