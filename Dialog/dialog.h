#ifndef LIBRARY_DIALOG_H
#define LIBRARY_DIALOG_H

#include <iostream>
#include "../Library/matplotlibcpp.h"
#include "../Library/Poly.hpp"

namespace Instruments{

    template <typename X>

    void getAll(X &num) {
        int right;
        const char *mes1 = "";
        do {
            std::cout << mes1;
            mes1 = "Invalid value! ";
            right = 0;
            std::cin >> num;
            if (std::cin.eof()) {
                num = 0;
                return;
            }
            if (!std::cin.good() || std::cin.peek() != '\n') {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                right = 1;
            }
        }while(right == 1);
        return;
    }

    int choose_answer();
    void output_menu();

    template <typename Z>

    void answer_(Z &answer,const Z one,const Z two){

        const char *mes = "";
        do {

            std::cout << mes;
            mes = "Invalid value! Repeat please -> ";
            Instruments::getAll(answer);

        }while (answer != one && answer != two);

    }

}


namespace Dialog{
    using namespace math;

    void dialog();
    void input(Poly &);
    void output(Poly &);
    void show_graphic(Poly &);
    void add_another_pol(Poly &);
    void value_in_point(Poly &);
    void derivative(Poly &);
}


#endif
