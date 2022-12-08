#include <QCoreApplication>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

//using namespace std;

class FileTXT{
public:
   std::ifstream in;

    // В конструкторе окроем файл для чтения
    FileTXT(std::string path){
        in.open(path);
        std::cout << "File is open" << std::endl;
    }

    std::vector<int> get_numbers(){
        std::vector<int> number_array;

        if (in.is_open()){
            std::string str_num;
            std::string line;
            int int_num, len;

            getline(in, line); //Считали первую строку и вытащили из нее количество чисел след строки
            len = stoi(line);
            std::cout << "You entered read " << len << " num in next line" << std::endl;

            getline(in, line); //Cчитали вторую строку, дальше работаем с ней

            for (int i=0; i<len; i++){
                int comma = line.find(",");
                str_num = line.substr(0, comma);

                try {
                    int_num = stoi(str_num);
                    std::cout << int_num << std::endl;
                    number_array.push_back(int_num);
                }
                catch (...) {
                    std::cout << "Error" << std::endl;
                }

                line = line.substr(comma+1);
            }
        }
        return number_array;
    }

    ~FileTXT(){
        in.close();     // закрываем файл
        std::cout << "File is close" << std::endl;
    }
};

class TXTReader{
public:
    FileTXT* file;

    TXTReader(){
        file = new FileTXT("C:\\Users\\koroc\\Documents\\readmeplease.txt");
    }

    void print_numbers(){
        std::vector<int> number_array = file->get_numbers();

        for (int j=0; j<number_array.size(); j++) std::cout << number_array[j] << " ";
        std::cout << std::endl;

    }

    ~TXTReader(){
        delete file;
    }
};



int main(int argc, char *argv[])
{
    TXTReader read_txt;
    read_txt.print_numbers();

    return 0;
}
