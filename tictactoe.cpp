#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>
using namespace std;

class setDimensionException : public std::exception {
    public:
    std::string what() {
        return "Out of range";
    }
};
void print_board(int hei, int wid, char** arr) {
    for (int i = 0; i < hei; ++i) {
        for (int j = 0; j < wid; ++j) {
            std::cout << arr[i][j] << " ";
        }
        std::cout << endl;
    }
    std::cout << endl;
}
void take_user_input(int hei, int wid, char** arr) {
    std::string u_sheight;
    int u_height = -1; 
    std::string u_swidth;
    int u_width = -1;
    do {
        do {
        std::cout << "Enter height: " << std::endl;
        getline(cin, u_sheight);
        try {
           u_height = std::stoi(u_sheight);
           if (u_height < 0 || u_height >= hei) {
            throw setDimensionException();
           }
        } catch(setDimensionException& sde) {
            std::cerr << u_height << " : " << sde.what() << std::endl;
            std::cout << "Must be between 0 and " << hei - 1 << std::endl;
        }
        catch (const std::invalid_argument& ia) {
            std::cerr << "Invalid argument: " << ia.what() << std::endl;
        } catch (const std::out_of_range& oor) {
             std::cerr << "Out of range: " << oor.what() << std::endl;
        }
        std::cout << std::endl;
        } while(u_height < 0 || u_height >= hei);
        std::cout << "Height entered: " << u_height << std::endl;
        do {
            std::cout << "Enter width: " << std::endl;
            getline(cin, u_swidth);
            try {
                u_width = std::stoi(u_swidth);
                if (u_width < 0 || u_width >= wid) {
                    throw setDimensionException();
                }
            } catch(setDimensionException& sde) {
                std::cerr << u_height << " : " << sde.what() << std::endl;
                std::cout << "Must be between 0 and " << wid - 1 << std::endl;
            } catch (const std::invalid_argument& ia) {
                std::cerr << "Invalid argument: " << ia.what() << std::endl;
            } catch (const std::out_of_range& oor) {
                std::cerr << "Out of range: " << oor.what() << std::endl;
            }
            std::cout << std::endl;
        } while(u_width < 0 || u_width >= wid);
         std::cout << "Width entered: " << u_width << std::endl;
    } while (arr[u_height][u_width] != '-');
    arr[u_height][u_width] = 'O';
}

void take_computer_input(int hei, int wid, char** arr) {
    int c_height = -1;
    int c_width = -1;
    srand((unsigned) time(NULL));
    do {
        c_height = (rand() % hei);
        c_width = (rand() % wid);
    } while (arr[c_height][c_width] != '-');
    arr[c_height][c_width] = 'X';
}

int check_winner(int hei, int wid, char** arr) {
    char value = arr[0][0];
    bool win = false;
    int winner = -1;
    if (hei == wid) {
        for (int i = 0; i < hei; ++i) {
            if (value == arr[i][i]) {
                win = true;
            } else {
                win = false;
                break;
            }
        }
        if (win) {
            if (value == 'O') {
                winner = 1;
            } 
            if (value == 'X') {
                winner = 0;
            }
        }
    } else {
        for (int i = 0; i < hei; ++i) {
            int val = 0;
            bool equal = true;
            int win_height = -1;
            while (val + 1 < wid && equal) {
                if (arr[i][val] != '-' && arr[i][val] == arr[i][val + 1]) {
                    win_height = i;
                } else {
                    equal = false;
                    break;
                }
                val++;
            }
            if (equal) {
                if (arr[win_height][val-1] == 'O') {
                    winner = 1;
                    win = true;
                }
                if (arr[win_height][val-1] == 'X') {
                    winner = 0;
                    win = true;
                }
            }
        }
        for (int i = 0; i < wid; ++i) {
            int val = 0;
            bool equal = true;
            int win_width = -1;
            while (val + 1 < hei && equal) {
                if (arr[val][i] != '-' && arr[val][i] == arr[val + 1][i]) {
                    win_width = i;
                } else {
                    equal = false;
                    break;
                }
                val++;
            }
            if (equal) {
                if (arr[val - 1][win_width] == 'O') {
                    winner = 1;
                    win = true;
                }
                if (arr[val - 1][win_width] == 'X') {
                    winner = 0;
                    win = true;
                }
            }
        }
    }
    if (win) {
        if (winner == 1) {
            std::cout << "Player has won!" << std::endl;
        }
        if (winner == 0) {
            std::cout << "Computer has won!" << std::endl;
        }
    }
    return win;
}

int main() {
    std::cout << "TIC-TAC-TOE" << std::endl << std::endl;
    std::string setHeightString;
    int setHeight = -1;
    std::string setWidthString;
    int setWidth = -1;
    do {
        std::cout << "Enter a desired height of the board: " << std::endl;
        getline(std::cin, setHeightString);
        try {
            setHeight = stoi(setHeightString);
            if (setHeight > 10 || setHeight < 3) {
                throw setDimensionException();
            }
        } catch (setDimensionException& sde) {
            std::cerr << setHeight << " : " << sde.what() << std::endl;
            std::cout << "Must be in between 3 and 10" << std::endl;
        } catch (const std::invalid_argument& ia) {
            std::cout << "Invalid argument: " << ia.what() << std::endl;
        } catch (const std::out_of_range& oor) {
            std::cout << "Out of range: " << oor.what() << std::endl;
        } 
        std::cout << std::endl;
    } while(setHeight > 10 || setHeight < 3);
    do {
        std::cout << "Enter a desired width of the board: " << std::endl;
        getline(std::cin, setWidthString);
        try {
            setWidth = stoi(setWidthString);
            if (setWidth > 10 || setWidth < 3) {
                throw setDimensionException();
            }
        } catch (setDimensionException& sde) {
            std::cerr << setWidth << " : " << sde.what() << std::endl;
            std::cout << "Must be in between 3 and 10" << std::endl;
        } catch (const std::invalid_argument& ia) {
            std::cout << "Invalid argument: " << ia.what() << std::endl;
        } catch (const std::out_of_range& oor) {
            std::cout << "Out of range: " << oor.what() << std::endl;
        } 
        std::cout << std::endl;
    } while(setWidth > 10 || setWidth < 3);

    int height{setHeight};   
    int& ref_height{height};
    int width{setWidth};
    int& ref_width{width};
    char** p_array = new char*[height];
    char**& ref_p_array{p_array};

    for (int i = 0; i < height; ++i) {
        p_array[i] = new char[width];
        for (int j = 0; j < width; ++j) {
            p_array[i][j] = '-';
        }
    }
    
    print_board(ref_height, ref_width, ref_p_array);

    take_user_input(ref_height, ref_width, ref_p_array);
    
    print_board(ref_height, ref_width, ref_p_array);

    take_computer_input(ref_height, ref_width, ref_p_array);
    
    print_board(ref_height, ref_width, ref_p_array);

    
    //std::string u_swidth;
    //char* u_input; 
    //char u_char;

    
    // std::cout << "Enter width: " << std::endl; 
    // do {
    //     std::cin >> u_width;
    // } while(u_width < 0 || u_width > width);
    
    for (int i = 0; i < height; ++i) {
        delete[] p_array[i];
    
    }

    delete[] p_array;

    return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          