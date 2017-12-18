
#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string.h>
using   namespace std;

int main()
{
    ifstream ifile;
    ofstream ofile, ofile2;
    ifile.open("SMSSpamCollection");
    ofile.open("extra_examples.txt");
    ofile2.open("extra_attributes.txt");
    string S;
    string T;

    char ch;

    map<string,int> M;
    int attr = 3;
    M["size"] = 0;
    M["email"] = 1;
    M["one+_digit_numbers"] = 2;

    int examp = 0;
    while(getline(ifile,S))
    {
        ++examp;
    }
    ifile.close();
    ifile.open("SMSSpamCollection");


    vector<vector<int> > Ex(examp, vector<int>(attr,0));
    for(int i=0;i<examp;i++)
    {
        getline(ifile,S);
        Ex[i][0] = S.size();
        for(int j=2;j<S.size();j++)
        {
            if(S[j] == '@')
                Ex[i][1]++;
            if(!isdigit(S[j]) && isdigit(S[j-1]) && isdigit(S[j-2]))
                Ex[i][2]++;
        }
    }

    for(int i=0;i<examp;i++)
    {
        for(int j=0;j<attr;j++)
            ofile<<Ex[i][j]<<" ";
        ofile<<endl;
    }

    vector<string> At(attr);
    for(map<string,int>::iterator it = M.begin(); it!=M.end(); it++)
    {
        At[it->second] = it->first;
    }

    for(int i=0;i<attr;i++)
    {
        ofile2<<At[i]<<endl;
    }

    return 0;
}
