/*
	Harvey Petersen hrp3@uakron.edu
	Algorithms Spring 2022
	Project 3
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

class Picture{
private:
     std::vector<std::vector<int>> main; //This stores the primary values of the picture
     std::vector<std::vector<int>> energyMatrix; //This stores the energy matrix when needed
          std::vector<std::vector<int>> cumulativeMatrix; //This stores the cumulative energy matrix when needed
     std::vector<int> builder; //Used when building the main matrix
     int col = 0;
     int row = 0;
     int scale = 0;
     int rowCounter = 0; //Used when building the main matrix
     int colCounter = 0;
     
     //No in or out parameters. 
     //Creates an energy matrix, saved as a class member
     void createEnergyMatrix(){
         std::vector<int> temp;
        //Clear any previous data
         energyMatrix.clear();
         int value = 0;
         int tempInt1 = 0, tempInt2 = 0, tempInt3 = 0, tempInt4 = 0;
         for(int i = 0; i < row; i++){
             for (int j = 0; j < col; j++){
                 if(j == 0){ //left border
                    tempInt1 = 0;
                    tempInt2 = main[i][j+1] - main[i][j]; 
                 }
                 else if (j == col -1){ //right border
                    tempInt1 = main[i][j-1] - main[i][j];
                    tempInt2 = 0; 
                 }
                 else{
                    tempInt1 = main[i][j-1] - main[i][j];
                    tempInt2 = main[i][j+1] - main[i][j]; 
                 }
                 if (i == 0){ //top border
                    tempInt3 = 0;
                    tempInt4 = main[i+1][j] - main[i][j]; 
                 }
                 else if (i == row -1){ //bottom border
                    tempInt3 = main[i-1][j] - main[i][j];
                    tempInt4 = 0;
                 }
                 else{
                    tempInt3 = main[i-1][j] - main[i][j];
                    tempInt4 = main[i+1][j] - main[i][j];
                 }
                 value = abs(tempInt1) + abs(tempInt2) +abs(tempInt3) +abs(tempInt4);
                 temp.push_back(value);
             }
             energyMatrix.push_back(temp);
             temp.clear();
         }
     }
     //No in or out parameters. Creates a Cumulative Energy Matrix for seam identification
     void createCumulativeMatrix(){
         std::vector<int> temp;
         //Clear any previous data
         cumulativeMatrix.clear();
         int upLeft = 0, upCenter = 0, upRight = 0, minInt = 0;
         for(int i = 0; i < row; i++){
             for (int j = 0; j < col; j++){
                 
                 if (i != 0){ //not top or bottom row
                     if (j == 0){ //left border
                         minInt = mini(999999,cumulativeMatrix[i-1][j],cumulativeMatrix[i-1][j+1]);
                     }
                     else if (j == col-1){ //right border
                         minInt = mini(cumulativeMatrix[i-1][j-1],cumulativeMatrix[i-1][j],999999);
                     }
                     else{
                         minInt = mini(cumulativeMatrix[i-1][j-1],cumulativeMatrix[i-1][j],cumulativeMatrix[i-1][j+1]);
                     }

                     minInt = energyMatrix[i][j] + minInt;
                 }
                 else if (i == 0){ //top row 
                     minInt = energyMatrix[i][j];
                 }
                 temp.push_back(minInt);
                 
             }
             cumulativeMatrix.push_back(temp);
             temp.clear();
         }
     }
      //Makes the rows into columns and columns into rows
      //No in or out parameters
      void transpose(){
         std::vector<int> temp;
         std::vector<std::vector<int>> tempVec;
         for(int i = 0; i < col; i++){
             for (int j = 0; j < row; j++){
                 temp.push_back(main[j][i]);
             }
             tempVec.push_back(temp);
             temp.clear();
         }
         int k = 0;
         k = row;
         row = col;
         col = k;
         main = tempVec;
     }

public:
     //Default constructor
     Picture(){};
     //Constructor
     Picture(int column, int rows){
         col = column;
         row = rows;
         
     }
     //Destructor
     ~Picture(){
     };
     //Sets the scale value. Takes in one int, no return.
     void setScale(int value){
         scale = value;
     }
     //In: A string with a value that will be turned into an int
     //The value is loaded into the main matrix according to the column and row parameters
     void load(std::string value){
         builder.push_back(stoi(value));
         colCounter++;
         if (colCounter == col){
             rowCounter++;
             main.push_back(builder);
             if ((rowCounter == row) && (colCounter == col)){
                 rowCounter = 0;
             }
             colCounter = 0;
             builder.clear();
         }
     }
     
     //No input or output
     //Carves the least energetic seam out of the main matrix
     void carve(){
        //Each carve uses a fresh energy matrix
        createEnergyMatrix();
        createCumulativeMatrix();
         //cumulative array exists, now find the smallest value at the bottom and work back up
        int minInt = 9999999, upLeft = 0, upCenter = 0, upRight = 0, minIndex = 0;

        for (int j = 0; j < col; j++){
            upCenter = cumulativeMatrix[row-1][j];
            
            if(j == 0){ //left border
                upLeft = 9999999;
            }
            else{
                upLeft = cumulativeMatrix[row-1][j-1];
            }

            if (j == col -1){ //right border
                upRight = 9999999;
            }
            else{
                upRight = cumulativeMatrix[row-1][j+1];
            }

            if (upLeft < minInt){
                minInt = upLeft;
                minIndex = j-1;
            }
            if (upCenter < minInt){
                minInt = upCenter;
                minIndex = j;
            }
            if (upRight < minInt){
                minInt = upRight;
                minIndex = j+1;
            }
        }
        main[row-1].erase(main[row-1].begin() + minIndex);
        int indexHolder = 0;
        int hold1 = 99999, hold2 = 99999, hold3 = 99999; //Just large numbers
        for (int i = row -2; i >= 0; i--){
            if(minIndex == 0){
                hold1 = 99999;
            }
            else{
                hold1 = cumulativeMatrix[i][minIndex-1];
            }
            
            if (minIndex >= col-1){
               hold3 = 99999;
            }
            else{
                hold3 = cumulativeMatrix[i][minIndex+1];
                
            }
            hold2 = cumulativeMatrix[i][minIndex];
            
            if (hold1 <= minInt){
                minInt = hold1;
                indexHolder = minIndex-1;
                if ((hold2 <= minInt) && (hold2 < hold1)){
                    minInt = hold2;
                    indexHolder = minIndex;
                    if ((hold3 <= minInt) && (hold3 < hold2)){
                        minInt = hold3;
                        indexHolder = minIndex+1;
                    }
                }else if ((hold3 <= minInt) && (hold3 < hold1)){
                        minInt = hold3;
                        indexHolder = minIndex+1;
                }
            }else if ((hold2 <= minInt) && (hold2 < hold1)){
                    minInt = hold2;
                    indexHolder = minIndex;
                    if ((hold3 <= minInt) && (hold3 < hold2)){
                        minInt = hold3;
                        indexHolder = minIndex+1;
                    }
            }else if ((hold3 <= minInt) && (hold3 < hold2)){
                        minInt = hold3;
                        indexHolder = minIndex+1;
            }else{ //for troubleshooting
                std::cout << "ERROR in the seam carving" << std::endl;
                std::cout << "hold 1: " << hold1 << " hold2: " << hold2 << " hold3: " << hold3 << " minInt: " << minInt << std::endl;
                std::cout << "Index: " << minIndex << " i equals: " << i << std::endl;
                std::cout << "Rows = " << row << " and columns equal : " << col << std::endl;
                exit(0);
               
                
            }
            minIndex = indexHolder;
            main[i].erase(main[i].begin() + indexHolder);
        }
        col = col - 1;
        
    }
     
    //No in or out
    //A horizontal carve flips the matrix, does a vertical carve, then flips it back.
    void carveHorizontal(){
         this->transpose();
         this->carve();
         this->transpose();
     }
    //In: fstream by reference for the output file, already opened
    //Writes the main matrix out in the correct format
    void output(std::fstream& file){
        file << "P2" << std::endl;
        file << "# Created by InfranView" << std::endl;
        file << col << " " << row << std::endl;
        file << scale << std::endl;
         for (int i = 0; i < main.size(); i++){
             for (auto iter = main[i].begin(); iter != main[i].end(); iter++){
                 file << *iter << " ";
             }
             file << std::endl;
         }
    }
    
    //In: three int values
    //Returns the smallest of the three values
    int mini(int a, int b, int c){
    
        return std::min(a, std::min(b, c));
        
    }
};


int main(int argc, char *argv[]) {

    if (argc != 4) { //verify arguments
        std::cout << "wrong format! should be \"a.exe filename # #\" or \"a.exe filename # #\"" << "\n";
        return 0;
    }
    //Open file
    std::string filename = argv[1];
    std::fstream myfile (filename.c_str());
    if(!(myfile)){
        std::cout << "The file was not opened. Check your spelling, the name is case sensitive." << std::endl;
        return 0;
    }
    
    std::string holder;
    std::vector<std::string> input;
    
    getline(myfile, holder); //clear the literal P2
    bool parseFlag = true;
    //Get the column and row values. Clear any comments.
    int col = 0, row = 0;
    while(parseFlag){
        getline(myfile, holder, ' ');
        if (holder[0] != '#'){
            col = stoi(holder);
            getline(myfile, holder);
            row = std::stoi(holder);
            parseFlag = false;
        }
        else{
            getline(myfile, holder);
        }
        if(!(myfile)){
            std::cout << "The file is in an invalid format. Please try again with a file in the correct format.";
            return 0;
        }
    }
    //Create object to parse the file
    Picture myPic(col, row);
    //Save the scale value
    getline(myfile, holder);
    myPic.setScale(std::stoi(holder));
    //Read the file in, number by number. Ignore comments. Values are loaded without respect
    //To spaces or endlines, they will be entered according to the column and row values
    while(myfile){
        myfile >> holder;
        if(holder[0] == '#'){
            getline(myfile, holder);
        }
        else{
            myPic.load(holder);
        }
    }
    myfile.close();
    //Determine the number of loops needed
    int index = 0;
    std::string valueHolder = argv[2];
    int verticalCuts = stoi(valueHolder);
    valueHolder = argv[3];
    int horizontalCuts = stoi(valueHolder);
    //Execute the seam cuts one by one. First vertical, then horizontal
    if(verticalCuts > 0){
        for (int i = verticalCuts; i > 0; i--){
            myPic.carve();
        }
    }
    
    if (horizontalCuts > 0){
        for (int i = horizontalCuts; i > 0; i--){
            myPic.carveHorizontal();
        }
    }
    //Output the file
    std::size_t position = filename.find(".pgm");
    filename = filename.substr(0, position);
    filename += "_processed_" + std::to_string(verticalCuts) +"_" + std::to_string(horizontalCuts) + ".pgm";
    std::fstream outputFile(filename.c_str(), std::fstream::out);
    
    myPic.output(outputFile);
    
    outputFile.close();
    

return 0;
}
