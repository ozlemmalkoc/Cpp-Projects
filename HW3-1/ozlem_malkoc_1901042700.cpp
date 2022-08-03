#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

class pixel{
public:
    pixel();
    pixel(const int& r, const int& g, const int& b);

    void setterR(const int& r);
    void setterG(const int& g);
    void setterB(const int& b);

    int& getterR() { return r; }
    int& getterG() { return g; }
    int& getterB() { return b; }

    const int& getterR() const { return r; }
    const int& getterG() const { return g; }
    const int& getterB() const { return b; }

    static const int getterMin() { return MINVALUE; }
    static const int getterMax() { return MAXVALUE; }
    
    const int isValid(const int& val) const;
    const string toString() const;
    
    const pixel operator+(const pixel& other) const;
    const pixel operator-(const pixel& other) const;
private:
    int r;
    int g;
    int b;
    static const int MINVALUE = 0;
    static const int MAXVALUE = 255;
};

class ppmImage{
public:
    ppmImage();
    ppmImage(const int& row, const int& column);
    ppmImage(const string& fileName);

    void resizeData(const int& row, const int& column);

    const int& getterRow() const;
    const int& getterColumn() const;
    const vector<vector<pixel>>& getterData() const;
    
    void setterRow(const int& row);
    void setterColumn(const int& column);
    void setterData(const vector<vector<pixel>>& data);
    bool isValidDimension(const int& val)const;

    bool savePpm(const string& fileName) const;
    bool readPpm(const string& fileName);
    void printDimension() const;
    const pixel& getPixel(const int& row, const int& column) const;
    pixel& getPixel(const int& row, const int& column);
    bool setPixel(const int& row, const int& column, const pixel& p);
    const string toString() const;

    const ppmImage operator+(const ppmImage& other) const;
    const ppmImage operator-(const ppmImage& other) const;
    friend ostream& operator<<(ostream& os, const ppmImage& image);
    int& operator()(const int& row, const int& column, const int& colorChannel);
    const int& operator()(const int& row, const int& column, const int& colorChannel) const;

private:
    int row;
    int column;
    vector<vector<pixel>> data;
};

pixel::pixel(): r(getterMax()), g(getterMax()), b(getterMax()) {}

pixel::pixel(const int& r, const int& g, const int& b): pixel(){
    setterR(r);
    setterG(g);
    setterB(b);
}

void pixel::setterR(const int& r){
    int res = isValid(r);

    if(res == -1)
        this->r = getterMin();
    else if(res == 0)
        this->r = r; 
    else
        this->r = getterMax();
}

void pixel::setterG(const int& g){
    int res = isValid(g);

    if(res == -1)
        this->g = getterMin();
    else if(res == 0)
        this->g = g; 
    else
        this->g = getterMax();
}

void pixel::setterB(const int& b){
    int res = isValid(b);

    if(res == -1)
        this->b = getterMin();
    else if(res == 0)
        this->b = b; 
    else
        this->b = getterMax();
}

// Returns -1 if value is lower than minimum value
// Returns 0 if value is between minimum and maximum values
// returns 1 if value is greater than maximum value
const int pixel::isValid(const int& val) const{
    if(val < (int) getterMin())
        return -1;
    if(val > (int) getterMax())
        return 1;
    return 0;
}

const string pixel::toString() const{
    return to_string(getterR()) + ' ' + to_string(getterG()) + ' ' + to_string(getterB()) + ' ';
}

const pixel pixel::operator+(const pixel& other) const{
    pixel newObj(getterR() + other.getterR(), getterG() + other.getterG(), getterB() + other.getterB());
    return newObj;
}

const pixel pixel::operator-(const pixel& other) const{
    pixel newObj(getterR() - other.getterR(), getterG() - other.getterG(), getterB() - other.getterB());
    return newObj;
}

ppmImage::ppmImage(): row(0), column(0) {}

ppmImage::ppmImage(const int& row, const int& column): ppmImage(){
    setterRow(row);
    setterColumn(column);

    resizeData(getterRow(), getterColumn());
}

ppmImage::ppmImage(const string& fileName): ppmImage(){
    readPpm(fileName);
}

void ppmImage::resizeData(const int& row, const int& column){
    data.resize(getterRow());
    for(auto& v : data)
        v.resize(getterColumn());
}

const int& ppmImage::getterRow() const{
    return row;
}

const int& ppmImage::getterColumn() const{
    return column;
}

const vector<vector<pixel>>& ppmImage::getterData() const{
    return data;
}

void ppmImage::setterRow(const int& row){
    if(isValidDimension(row))
        this->row = row;
}

void ppmImage::setterColumn(const int& column){
    if(isValidDimension(column))
        this->column = column;
}

void ppmImage::setterData(const vector<vector<pixel>>& data){
    this->data = data;
}

bool ppmImage::isValidDimension(const int& val) const{
    return val >= 0;
}

bool ppmImage::savePpm(const string& fileName) const{
    ofstream out(fileName.data(), ofstream::out);

    if(!out)
    {
        exit(EXIT_FAILURE);
    }

    out << toString();
    out.close();

    return true;
}

bool ppmImage::readPpm(const string& fileName){
    ifstream indata;

    indata.open(fileName.data());

    if(!indata)
    {
        exit(EXIT_FAILURE);
    }
    
    string buffer;
    int r, c, max, valR, valG, valB;

    indata >> buffer;

    if(buffer.compare("P3") != 0)
        return false;
    
    indata >> r >> c;

    setterRow(r);
    setterColumn(c);

    data.resize(getterRow());
    for(auto v : data)
        v.resize(getterColumn());

    indata >> max;

    for(int i=0 ; i < getterRow() ; ++i)
        for(int j=0 ; j < getterColumn() ; ++j)
        {
            indata >> valR >> valG >> valB;
            pixel p(valR, valG, valB);
            data[i].push_back(p);
        }

    return true;
}

void ppmImage::printDimension() const{
    cout << row << ' '<< column;
}

const pixel& ppmImage::getPixel(const int& row, const int& column) const{
    if(isValidDimension(row) && isValidDimension(column))
        return data[row][column];

    exit(EXIT_FAILURE);
}

pixel& ppmImage::getPixel(const int& row, const int& column){
    if(isValidDimension(row) && isValidDimension(column))
        return data[row][column];

    exit(EXIT_FAILURE);
}

bool ppmImage::setPixel(const int& row, const int& column, const pixel& p){
    if(!isValidDimension(row) || !isValidDimension(column))
        exit(EXIT_FAILURE);
    
    data[row][column] = p;
    return true;
}

const string ppmImage::toString() const{
    string str("P3\n" + to_string(getterRow()) + " " + to_string(getterColumn()) + "\n" + to_string(pixel::getterMax()) + "\n");
    
    for(auto& row : getterData()){
        for(auto& col : row)
            str += col.toString();
        str += "\n";
    }

    return str;
}

int read_ppm(const string source_ppm_file_name, ppmImage& destination_object){
    if(destination_object.readPpm(source_ppm_file_name))
        return 1;
    return 0;
}

int write_ppm(const string destination_ppm_file_name, const ppmImage& source_object){
    if(source_object.savePpm(destination_ppm_file_name))
        return 1;
    return 0;
}

const ppmImage ppmImage::operator+(const ppmImage& other) const{
    if(getterRow() != other.getterRow() || getterColumn() != other.getterColumn())
    {
        ppmImage newObj;
        return newObj;
    }

    ppmImage newObj(getterRow(), getterColumn());

    for(int i=0 ; i < getterRow() ; ++i)
        for(int j=0 ; j < getterColumn() ; ++j)
            newObj.setPixel(i, j, this->getPixel(i, j) + other.getPixel(i, j));
    
    return newObj;
}

const ppmImage ppmImage::operator-(const ppmImage& other) const{
    if(getterRow() != other.getterRow() || getterColumn() != other.getterColumn())
    {
        ppmImage newObj;
        return newObj;
    }

    ppmImage newObj(getterRow(), getterColumn());

    for(int i=0 ; i < getterRow() ; ++i)
        for(int j=0 ; j < getterColumn() ; ++j)
            newObj.setPixel(i, j, this->getPixel(i, j) - other.getPixel(i, j));
    
    return newObj;
}

ostream& operator<<(ostream& os, const ppmImage& image){
    os << image.toString();
    return os;
}

// if color channel is invalid, returns red color channel
int& ppmImage::operator()(const int& row, const int& column, const int& colorChannel) {
    switch(colorChannel)
    {
        case 1:
            return getPixel(row, column).getterR();
        case 2:
            return getPixel(row, column).getterG();
        case 3:
            return getPixel(row, column).getterB();
        default:
            return getPixel(row, column).getterR(); // default action
    }
}

const int& ppmImage::operator()(const int& row, const int& column, const int& colorChannel) const{
    switch(colorChannel)
    {
        case 1:
            return getPixel(row, column).getterR();
        case 2:
            return getPixel(row, column).getterG();
        case 3:
            return getPixel(row, column).getterB();
        default:
            return getPixel(row, column).getterR(); // default action
    }
}

int test_addition(const string filename_image1, const string filename_image2, const string filename_image3){
    ppmImage image1, image2;

    if(read_ppm(filename_image1, image1) != 1 || read_ppm(filename_image2, image2) != 1)
        return 0;

    return write_ppm(filename_image3, image1 + image2);
}

int test_subtraction(const string filename_image1, const string filename_image2, const string filename_image3){
    ppmImage image1, image2;

    if(read_ppm(filename_image1, image1) != 1 || read_ppm(filename_image2, image2) != 1)
        return 0;

    return write_ppm(filename_image3, image1 - image2);
}

int test_print(const string filename_image1){
    ppmImage image1;

    if(read_ppm(filename_image1, image1) == 0)
        return 0;

    cout << image1;
    return 1;
}

int swap_channels(ppmImage& image_object_to_be_modified, int swap_choice){
    int swap1, swap2;

    switch(swap_choice){
        case 1: swap1 = 1; swap2 = 2; break;
        case 2: swap1 = 1; swap2 = 3; break;
        case 3: swap1 = 2; swap2 = 3; break;
        default: return 0;
    }

    for(int i=0 ; i < image_object_to_be_modified.getterRow() ; ++i)
        for(int j=0 ; j < image_object_to_be_modified.getterColumn() ; ++j)
        {  
            int temp = image_object_to_be_modified(i, j, swap1);
            image_object_to_be_modified(i, j, swap1) = image_object_to_be_modified(i, j, swap2);
            image_object_to_be_modified(i, j, swap2) = temp;
        }

    return 1;
}

ppmImage single_color(const ppmImage& source, int color_choice){
    ppmImage newImage(source.getterRow(), source.getterColumn());

    if(color_choice < 1 || color_choice > 3)
        return newImage;
    
    for(int i=0 ; i < source.getterRow() ; ++i)
       { for(int j=0 ; j < source.getterColumn() ; ++j)
        { 
            newImage(i, j, 1) = 0;
            newImage(i, j, 2) = 0;
            newImage(i, j, 3) = 0;
            newImage(i, j, color_choice) = source(i, j, color_choice);
        }
}
    return newImage;
}

int main(int argc, char** argv){
    ppmImage image1, image2;
    int minArgNum = 2, maxArgNum = 4;

    if(argc <= minArgNum)
        exit(EXIT_FAILURE);
    
    if(strcmp(argv[1], "1") == 0){
        if(argc != maxArgNum + 1) // first one is program name
            exit(EXIT_FAILURE);
        
        test_addition(argv[2], argv[3], argv[4]);
    }
    else if(strcmp(argv[1], "2") == 0){
        if(argc != maxArgNum + 1) 
            exit(EXIT_FAILURE);
        
        test_subtraction(argv[2], argv[3], argv[4]);
    }
    else if(strcmp(argv[1], "3") == 0){
        
        if(argc < maxArgNum)
            exit(EXIT_FAILURE);
        
        read_ppm(argv[2], image1);
        swap_channels(image1, 2);
        write_ppm(argv[3], image1);
    }
    else if(strcmp(argv[1], "4") == 0){
        if(argc < maxArgNum)
            exit(EXIT_FAILURE);

        read_ppm(argv[2], image1);
        swap_channels(image1, 3);
        write_ppm(argv[3], image1);
    }
    else if(strcmp(argv[1], "5") == 0){
        if(argc < maxArgNum)
            exit(EXIT_FAILURE);

        read_ppm(argv[2], image1);
        image2 = single_color(image1, 1);
        write_ppm(argv[3], image2);
    }
    else if(strcmp(argv[1], "6") == 0){
        if(argc < maxArgNum)
            exit(EXIT_FAILURE);

        read_ppm(argv[2], image1);
        image2 = single_color(image1, 2);
        write_ppm(argv[3], image2);
    }
    else if(strcmp(argv[1], "7") == 0){
        if(argc < maxArgNum)
            exit(EXIT_FAILURE);

        read_ppm(argv[2], image1);
        image2 = single_color(image1, 3);
        write_ppm(argv[3], image2);
    }
    else
        exit(EXIT_FAILURE);
    
    return 0;
}