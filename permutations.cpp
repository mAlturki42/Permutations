/*
	Title:          permutations.cpp
	Author:         Mohammed Alturki
	Date Created:   10/29/2021
	Purpose:        A program implementing the Lexicographic and Johnson Trotter algorithm
*/
#include<iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;



#define RIGHT_TO_LEFT 0
#define LEFT_TO_RIGHT 1

//to store the permutation with the i and j values
class item
{
    public:
        string str;
        int i;
        int j;
        //constructor to set the values
        item(string str, int i, int j)
        {
            this->str = str;
            this->i = i;
            this->j = j;
        }
};

vector<item> getPermutations(string str)
{
    vector<item> ans; //vector to store the answer
    while (true)
    {
        int n = str.size(), i, j; //declare variables
        for (i = n - 2; i >= 0; i--)
        {
            if (str[i] < str[i + 1])
                break;
        }
        if (i < 0)
        {
            item I(str, -1, -1); //create an item
            ans.push_back(I);
            break;
        }
        else
        {
            for (j = n - 1; j > i; j--)
            {
                if (str[j] > str[i])
                {
                    break;
                }
            }
            item I(str, i, j); //create an item
            ans.push_back(I); //push back the item
            swap(str[i], str[j]); //swap the characters
            reverse(str.begin() + i + 1, str.end());  //reverse the string
        }
    }
    //return the permutations
    return ans;
}

// Johnson Trotter algorithm begins
// Utility functions for finding the
// position of largest mobile integer in a[].

int searchArr(int a[], string str, int mobile) 
{
    int n = str.size();
    for (int i = 0; i < n; i++) 
    {
        if (a[i] == mobile) 
        {
            return i + 1;
        }
    }
    return 0;
}

// function to find the largest mobile integer.
int getMobile(int a[], bool dir[], string str) 
{
    int n = str.size();
    int mobile_prev = 0, mobile = 0;
    for (int i = 0; i < n; i++)
    {
        // function to get the direction 0 represents RIGHT TO LEFT.
        if (dir[a[i] - 1] == RIGHT_TO_LEFT && i != 0)
        {
            if (a[i] > a[i - 1] && a[i] > mobile_prev)
            {
                mobile = a[i];
                mobile_prev = mobile;
            }
        }
        
        // direction 1 represents LEFT TO RIGHT.
        if (dir[a[i] - 1] == LEFT_TO_RIGHT && i != n - 1)
        {
          if (a[i] > a[i + 1] && a[i] > mobile_prev)
          {
            mobile = a[i];
            mobile_prev = mobile;
          }
        }
    }
    if (mobile == 0 && mobile_prev == 0)
        return 0;
    else
        return mobile;
}

// Prints a single permutation
void printOnePerm(int a[], bool dir[], string str)
{
    int n = str.size();
    int mobile = getMobile(a, dir, str);
    int pos = searchArr(a, str, mobile);
    // swapping the elements according to the
    // direction i.e. dir[].
    if (dir[a[pos - 1] - 1] == RIGHT_TO_LEFT)
        swap(a[pos - 1], a[pos - 2]);
    else if (dir[a[pos - 1] - 1] == LEFT_TO_RIGHT)
        swap(a[pos], a[pos - 1]);
    // changing the directions for elements
    for (int i = 0; i < n; i++)
    {
        if (a[i] > mobile)
        {
            if (dir[a[i] - 1] == LEFT_TO_RIGHT)
                dir[a[i] - 1] = RIGHT_TO_LEFT;
            else if (dir[a[i] - 1] == RIGHT_TO_LEFT)
                dir[a[i] - 1] = LEFT_TO_RIGHT;
        }
    }
    for (int i = 0; i < n; i++) {
        if (dir[a[i] - 1] == RIGHT_TO_LEFT)
            cout << "<- ";
        else if (dir[a[i] - 1] == LEFT_TO_RIGHT)
            cout << "-> ";
    }
    cout << "\n\t";
    //display the characters of string
    for (int i = 0; i < n; i++)
        cout << str[a[i] - 1] << "  ";
    cout << endl;
}

int fact(string str)
{
    int n = str.size();
    int res = 1;
    for (int i = 1; i <= n; i++)
        res = res * i;
    return res;
}

//function to implement Johnson Trotter
void JohnsonTrotter(string str)
{
    int n = str.size();
    //for(int i=0;i<n;i++)
    //cout<<str[i]<<" ";
    // int To store current permutation
    int a[n];
    // bool to store current directions
    bool dir[n];
    // printing first permutation of string
    cout << "1:\t";
    for (int i = 0; i < n; i++)
        cout << "<- ";
    cout << "\n\t";
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        cout << str[i] << "  ";
    }
    cout << endl;
    // initially all directions are set
    // to RIGHT TO LEFT i.e. 0.
    for (int i = 0; i < n; i++)
        dir[i] = RIGHT_TO_LEFT;
    // for generating permutations in the order.
    for (int i = 1; i < fact(str); i++) {
        cout << i + 1 << ":\t";
        printOnePerm(a, dir, str);
    }
}

//main function to display the output 
int main()
{
    string str;

    //input the string from user
    cout << "Enter a string to find it's permutation: ";
    cin >> str;

    cout<<"\n\nJOHNSON-TROTTER ALGORITHM\n";
    //calling johnson trotter algorithm
    JohnsonTrotter(str);
    cout << "Johnson-Trotter Algorithm complete!\n\n\n";

    //print the lexicographic permutations
    cout << "\nLEXICOGRAPHIC ALGORITHM: \n";
    vector<item> ans = getPermutations(str);
    for (int i = 0; i < ans.size() - 1; i++)
    {
        cout << (i + 1) << ":\t"
             << ans[i].str << "\ti = "
             << ans[i].i << "\tj = "
             << ans[i].j << "\n";
    }
    //print the last permutation separately
    cout << ans.size() << ".\t"
         << ans[ans.size() - 1].str;

    //print the acknowledgement
    cout << "\nLexicographic Algorithm complete!";
    cout << "\n\nAll done!";
    return 0;
}
