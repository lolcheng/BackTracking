#include "../inc/BackTracking.h"
#include <time.h>
using namespace std;

int main()
{
    // SudokuSolution *s = new SudokuSolution();
    // vector<vector<char>> board = {
    //     {'8', '6', '.', '.', '.', '.', '7', '.', '.'},
    //     {'2', '.', '.', '5', '.', '4', '.', '.', '.'},
    //     {'4', '.', '1', '.', '.', '.', '.', '9', '.'},
    //     {'.', '.', '.', '4', '3', '.', '.', '.', '8'},
    //     {'.', '.', '.', '.', '7', '.', '2', '.', '.'},
    //     {'1', '.', '2', '.', '.', '.', '.', '.', '.'},
    //     {'7', '.', '.', '.', '4', '.', '.', '.', '.'},
    //     {'.', '.', '.', '7', '6', '.', '.', '.', '9'},
    //     {'.', '.', '4', '.', '.', '1', '.', '.', '2'},
    // };
    // s->solveSudoku(board);
    // for (int i = 0; i <= 8; i++)
    // {
    //     for (int j = 0; j <= 8; j++)
    //         cout << board[i][j] << ",";
    //     cout << endl;
    // }
    // cout << clock() << endl;

    // TelephoneNumberSolution *s = new TelephoneNumberSolution();
    // vector<string> result;
    // result = s->LetterCombinations("23");
    // for (int i = 0; i < result.capacity(); i++)
    // {
    //     cout << result[i] << ",";
    // }
    // cout << clock();

    // int RegionState[12] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
    // for (int i = 0; i <= 6; i++)
    // {
    //     for (int j = i + 1; j <= 7; j++)
    //     {
    //         for (int k = j + 1; k <= 8; k++)
    //         {
    //             for (int l = k + 1; l <= 9; l++)
    //             {
    //                 for (int m = l + 1; m <= 10; m++)
    //                 {
    //                     for (int n = m + 1; n <= 11; n++)
    //                     {
    //                         RegionState[i] = 1;
    //                         RegionState[j] = 1;
    //                         RegionState[k] = 1;
    //                         RegionState[l] = 1;
    //                         RegionState[m] = 1;
    //                         RegionState[n] = 1;
    //                         GetBall *g = new GetBall();
    //                         g->GetAvailableRegion(RegionState);
    //                         g->BackTracking(0, -1);
    //                         g->UpdateIndex();
    //                         RegionState[i] = -1;
    //                         RegionState[j] = -1;
    //                         RegionState[k] = -1;
    //                         RegionState[l] = -1;
    //                         RegionState[m] = -1;
    //                         RegionState[n] = -1;
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
    // for (int i = 0; i <= 11; i++)
    // {
    //     for (int j = 0; j <= 11; j++)
    //         std::cout << Index[i][j] << ",";
    //     std::cout << std::endl;
    // }
    int RegionState[12] = {
        1,
        1,
        1,
        -1,
        1,
        -1,
        1,
        -1,
        -1,
        -1,
        1,
        -1,
    };

    GetBall *g = new GetBall();
    g->GetAvailableRegion(RegionState);
    g->BackTracking(0, -1);
    cout << g->GetMinDistance() << endl;
    g->PrintDistanceDirectory();
    return 0;
}
