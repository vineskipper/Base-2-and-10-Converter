#include <iostream>
#include <thread> // for sleep_for
#include <chrono> // for time types
#include <cmath> // for pow, and log2
#include <sstream> // for stringstream

namespace global {
    bool isBinary(std::string& strNum){
        for (char ch : strNum){
            if (ch != '1' && ch != '0') return false;
        }

        return true;
    }

    bool isDecimal(std::string& strNum){
        for (char ch : strNum){
            switch (ch)
            {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    break;
                default:
                    return false;
            }
        }

        return true;
    }

    void clearScreen(int waitTime = 0.5){
        std::this_thread::sleep_for(std::chrono::seconds(waitTime));
        #ifdef _WIN32 
            std::system("cls");
        #else 
            std::system("clear");
        #endif
    }

    int binaryToDecimal(std::string& strNum){
        int decimalNum {};
        int index {static_cast<int>(strNum.size()) - 1};

        for (char bit : strNum){
            decimalNum += std::atoi(&bit) * std::pow(2, index);

            --index;
        }

        return decimalNum;
    }

    int decimalToBinary(std::string& strNum){ 
        //FIXME
                
        std::string binaryNum {};
        int num {std::stoi(strNum)};
        std::stringstream ss {};
        
        // the value of the binary number's place based on the index position (e.g: the 3rd place in a binary number would have a value of 4)
        int placeValue;

        for (int i {static_cast<int>(std::log2(num))}; i >= 0; i--) {
            placeValue = static_cast<int>(std::pow(2, i));

            if (num / placeValue){
                /*
                - integer division discards all fractional part of the quotient so if the quotient is not greater than 0, the number is less than the placeValue the quotient is 0
                - would directly checking is the number is greater than the place value have the same effect? it should right?
                */

                ss << '1';
                num -= placeValue;
            } else {
                ss << '0';
            }
        }

        ss >> binaryNum;

        return std::stoi(binaryNum);
    }

}

int main(int argc, char* argv[]){
    char numberBase {}; // the type of number being inputted (binary or decimal)
    std::string strNumber {}; // the inputted number held as a string

    if (argv[1]){ // this condition is true when the program is run from the cli
        numberBase = *argv[1]; 
        strNumber = argv[2];
    } 
    
    else {    

        do {
            std::cout << "Enter the number's base (b = binary, d = decimal): ";
            std::cin >> numberBase;
            
            global::clearScreen(0.7);

            //TODO: print error message
            
        } while (numberBase != 'b' && numberBase != 'd');

        switch (numberBase)
        {
        case 'b':
            do {
                std::cout << "Enter the binary number: ";
                std::cin >> strNumber; //TODO: validate input

                global::clearScreen(0.7);
            } while (!global::isBinary(strNumber));

            break;

        case 'd':
            do {
                std::cout << "Enter the decimal number: ";
                std::cin >> strNumber; //TODO: validate input

                global::clearScreen(0.7);
            } while (!global::isDecimal(strNumber));

            break;

        default:
            break;
        }

    }
        
    switch (numberBase)
    {
        case 'b':
            std::cout << strNumber << " in base 10 is: " << global::binaryToDecimal(strNumber) << '\n';
            break;
        case 'd':
            std::cout << strNumber << " in base 2 is: " << global::decimalToBinary(strNumber) << '\n';
            break;
        default:
            std::cerr << "\nError: Invalid number base\n";
    }

    return 0;
}
