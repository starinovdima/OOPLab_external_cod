#include "dialog.h"
#include <sstream>

namespace Dialog {

    namespace plt = matplotlibcpp;

    void dialog() {
        int c;
        Poly polynomial;
        do {
            Instruments::output_menu();
            c = Instruments::choose_answer();
            switch (c) {
                case 0:
                    std::cout << "***\n--Goodbye!--\n***" << std::endl;
                    break;
                case 1:
                    std::cout << "***\n-- New polynomial input --\n***" << std::endl;
                    input(polynomial);
                    break;
                case 2:
                    std::cout << "***\n-- Polynomial output  --\n***" << std::endl;
                    output(polynomial);
                    break;
                case 3:
                    std::cout << "***\n-- Show polynomial graphic --\n***" << std::endl;
                    show_graphic(polynomial);
                    plt :: show ();
                    break;
                case 4:
                    std::cout << "***\n-- Add another polynomial --\n***" << std::endl;
                    add_another_pol(polynomial);
                    break;
                case 5:
                    std::cout << "***\n-- Value in point --\n***" << std::endl;
                    value_in_point(polynomial);
                    break;
                case 6:
                    std::cout << "***\n-- Polynomial derivative --\n***" << std::endl;
                    derivative(polynomial);
                    break;
            }
        } while (c != 0);
    }

    void input(Poly &polynomial){

        char answer;
        std::cout << "\nDo you understand that your current polynomial will change completely, continue?" << std::endl;
        Instruments::answer_(answer,'y','n');
        if(answer == 'n')
            return;
        Poly sample;
        std::cout << "First, enter the number of coefficients of the polynomial, "
                     "then enter their value in turn (from high to low)" << std::endl;
        std::cin >> sample;
        polynomial = std::move(sample);

    }

    void output(Poly &polynomial){

        std::cout << "Output as COEF x DEGREE\n" << std::endl;
        std::cout << polynomial << "\n" << std::endl;

    }

    void show_graphic(Poly &polynomial){

        plt :: figure_size ( 1280 , 720 );
        int n = 10000;
        double count = -50;
        std::vector<double> x(n), y(n);

        for(int i = 0; i < n; i++){
            x[i] = count;
            count += 0.01;
            y[i] = polynomial(x[i]);
        }
        std::string name;
        std::ostringstream oss;

        oss << polynomial;
        name += oss.str();

        plt :: title("Polynomial graphic");
        plt :: named_plot(name,x,y);
        plt :: xlim(-10,10);
        plt :: ylim(-5,10);
        plt :: legend();
        plt ::grid(true);

    }

    void add_another_pol(Poly &polynomial){

        std::cout << "Enter the polynomial you want to add!" << std::endl;
        Poly sample;
        std::cout << "First, enter the number of coefficients of the polynomial, "
                     "then enter their value in turn (from high to low)" << std::endl;
        std::cin >> sample;
        polynomial = polynomial + sample;
        std::cout << "Operation completed successfully!" << std::endl;

    }

    void value_in_point(Poly &polynomial){
        std::vector<double> x(1),y(1);
        std::cout << "Enter the X value for which you want to find the Y value" << std::endl;
        Instruments::getAll(x[0]);
        y[0] = polynomial(x[0]);
        std::cout << "Point -> x: " << x[0] << "  y: " << y[0] << std::endl;
        char answer;
        std::cout << "\nDo you want to see this point on the graph? (y/n) "<< std::endl;
        Instruments::answer_(answer,'y','n');
        if(answer == 'n')
            return;
        show_graphic(polynomial);
        plt :: scatter(x,y,100);
        plt :: show();
    }

    void derivative(Poly &polynomial){
        polynomial = polynomial.derivative();
        std::cout << "Successfully!\n" << std::endl;
    }


}



namespace Instruments {

    int choose_answer() {
        int choice;
        const char *mes = "";
        std::cout << "Make your choice: ";
        do {
            std::cout << mes;
            mes = "Invalid value! Repeat please -> ";
            Instruments::getAll(choice);

        } while (choice < 0 || choice > 7);
        return choice;
    }

    void output_menu(){
        const char *MSGS[] = {"0. Quit","1. New polynomial input","2. Polynomial output ","3. Show polynomial graph ",
                              "4. Add another polynomial","5. Value in point ","6. Polynomial derivative"};
        for (auto  i : MSGS) {
            std::cout << i << std::endl;
        }
    }
}

