/*
 * Function: main
 * PURPOSE: OUTPUT HOW MANY PALINDROMES ARE IN A FILE
            AND OUTPUT HOW MANY HAVE A CERTAIN LETTER IN THEM
            AND OUTPUT THE PALINDROMES WITH THE MOST CHARACTERS
            AND OUTPUT THE PALINDROMES THAT HAVE A CERTAIN LETTER IN THEM AND HAVE THE MOST CHARACTERS
 * Name: Daniel Pellegrino
 * Written: 4/10/2021; Last Modified 3/24/2022
 * Language: C++
 */

#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

int wordCount( ifstream & );
int palindromeCount( ifstream &, vector<string> & );
int palindromeLetterCount( ifstream &, const char );
void displayMaxPalindromes( const vector<string> &, const char );

int main( void )
{

    string inputFileName;
    ifstream fileIn;

    vector<string> palindromes;
    char letter = 'm';

    cout << "Please enter a text file name: ";

    cin >> inputFileName;

    fileIn.open(inputFileName.data());

    assert(fileIn.is_open());
    
    cout << "# of words processed:\t\t\t" << wordCount(fileIn) << endl << "# of palindromes:\t\t\t" << palindromeCount(fileIn, palindromes) << endl
         << "# of palindromes with the letter " << letter << ":\t" << palindromeLetterCount(fileIn, letter) << endl;

    displayMaxPalindromes(palindromes, letter);

    fileIn.close();

    palindromes.clear();

    return 0;
}

int wordCount( ifstream &FILE )
{
    string s;
    int wordCount = 0;

    while (FILE >> s)
    {
        wordCount++;
    }

    FILE.clear();
    FILE.seekg(0);

    return wordCount;
}

int palindromeCount( ifstream &FILE, vector<string> &total )
{
    string s;
    stack<char> topStack;
    queue<char> frontQueue;

    while (FILE >> s)
    {
        for(int i = 0; i < (int)s.size(); i++)
        {
            if(isupper(s[i]))
            {
                s[i] += 32;
            }
            topStack.push(s[i]);

            frontQueue.push(s[i]);

        }

        for(int i=0; i < (int)s.size(); i++)
        {
            if(topStack.top() == frontQueue.front())
            {
                topStack.pop();
                frontQueue.pop();
            }
        }
        if(topStack.empty())
        {
            total.push_back(s);
        }

        else
        {
            while(!topStack.empty())
            {
                topStack.pop();
            }

            while(!frontQueue.empty())
            {
                frontQueue.pop();
            }
        }
    }

    FILE.clear();
    FILE.seekg(0);

    return ((int)total.size());
}

int palindromeLetterCount( ifstream &FILE, const char letter )
{
    string s;
    stack<char> topStack;
    queue<char> frontQueue;

    int letterPalinTotal = 0;

    while (FILE >> s)
    {
        for(int i = 0; i < (int)s.size(); i++)
        {
            if(isupper(s[i]))
            {
                s[i] += 32;
            }
            topStack.push(s[i]);
            frontQueue.push(s[i]);
        }
        for(int i=0; i < (int)s.size(); i++)
        {
            if(topStack.top() == frontQueue.front())
            {
                topStack.pop();

                frontQueue.pop();
            }
        }
        if(topStack.empty())
        {
            if(s.find(letter) != string::npos)
            {
                letterPalinTotal++;
            }
        }

        else
        {
            while(!topStack.empty())
            {
                topStack.pop();
            }

            while(!frontQueue.empty())
            {
                frontQueue.pop();
            }
        }
    }

    FILE.clear();
    FILE.seekg(0);

    return letterPalinTotal;
}

void displayMaxPalindromes( const vector<string> &total, const char letter )
{

    string temp;
    int longest = 0, mLongest = 0;

    for(int i = 0; i < (int)total.size(); i++)
    {
        if((int)total[i].size() > longest)
        {
            longest = total[i].size();
        }

        if(total[i].find(letter) != string::npos)
        {
            if((int)total[i].size() > mLongest)
            {
                mLongest = total[i].size();
            }
        }
    }

    cout << endl << "Displaying palindromes with " << longest << " characters..." << endl;

    for(int i = 0; i < (int)total.size(); i++)
    {
        if((int)total[i].size() == longest)
        {
            cout << total[i] << endl;
        }
    }

    cout << endl << "Displaying palindromes that contain m and have " << mLongest << " characters..." << endl;

    for(int i = 0; i < (int)total.size(); i++)
    {
        if(total[i].find(letter) != string::npos)
        {
            if((int)total[i].size() == mLongest)
            {
                cout << total[i] << endl;
            }
        }
    }

    return;
}
