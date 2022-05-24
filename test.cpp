#include <iostream>
#include <string>

#define NC "\e[0m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define CYN "\e[0;36m"
#define REDB "\e[41m"

int main(int argc, char ** argv){

    char a = 'A';

    std::cout << CYN << a << NC << std::endl;
    //std::cout << REDB "Add red background" NC << std::endl;
    std::cout << "reset to default colors with NC" << std::endl;
    
    
    
    



    return 0;
}