#include<bits/stdc++.h>
#include<iostream>
#include<fstream>
#include<string.h>
using   namespace std;

int main()
{
    ifstream ifile;
    ofstream ofile, ofile2, ofile3;
    ifile.open("SMSSpamCollection");
    ofile.open("examples.txt");
    ofile2.open("attributes.txt");
    ofile3.open("output.txt");
    string S;
    string T;

    char ch;
    map<string,int> M;
    int attr = 0;
    int examp = 0;
    while(getline(ifile,S))
    {
        T = "";
        int i = 0;
        while(isalpha(S[i]))
        {
            i++;
        }
        for(;i<S.size();i++)
        {
            if(isalpha(S[i]))
                T += S[i];
            else if(T!="")
            {
                if(M.find(T) == M.end())
                {
                    M[T] = attr;
                    attr++;
                }
                T = "";
            }
        }
        if(T!="")
        {
            if(M.find(T) == M.end())
            {
               M[T] = attr;
               attr++;
            }
            T = "";
        }
        ++examp;
    }
    ifile.close();
    ifile.open("SMSSpamCollection");


    vector<vector<int> > Ex(examp, vector<int>(attr,0));
    for(int i=0;i<examp;i++)
    {
        getline(ifile,S);
        T = "";
        int j=0;
        while(isalpha(S[j]))
        {
            T += S[j];
            j++;
        }
        if(T == "ham")
        {
            ofile3<<0<<endl;
        }
        else
        {
            ofile3<<1<<endl;
        }
        T = "";
        for(;j<S.size();j++)
        {
            if(isalpha(S[j]))
                T += S[j];
            else if(T!="")
            {
                Ex[i][M[T]]++;
                T = "";
            }
        }
        if(T!="")
        {
            Ex[i][M[T]]++;
                T = "";
        }
    }

    vector<pair<int,int> > X(attr, make_pair(0,0));
    vector<int> Y(attr,0);
    for(int i=0;i<examp;i++)
    {
        for(int j=0;j<attr;j++)
        {
            ofile<<Ex[i][j]<<" ";
            Y[j] += Ex[i][j];
        }
        ofile<<endl;
    }

    for(int i=0;i<attr;i++)
    {
         X[i].first = Y[i];
         X[i].second = i;
    }
    sort(X.begin(),X.end());
    ofstream ofile4;
    ofile4.open("test.txt");
    for(int i=0;i<attr;i++)
        ofile4<<X[i].first<<" "<<X[i].second<<endl;


    vector<string> At(attr);
    for(map<string,int>::iterator it = M.begin(); it!=M.end(); it++)
    {
        At[it->second] = it->first;
    }

    for(int i=0;i<attr;i++)
    {
        ofile2<<At[i]<<endl;
    }


    ofstream ofile5,ofile6;
    ofile5.open("super_reduced_examples.txt");
    ofile6.open("super_reduced_attributes.txt");
    for(int i=0;i<examp;i++)
    {
        for(int j=0;j<attr;j++)
        {
            if(Y[j] > 50 && Y[j] < 500)
                ofile5<<Ex[i][j]<<" ";
        }
        ofile5<<endl;
    }
    for(int i=0;i<attr;i++)
    {
        if(Y[i] > 50 && Y[i] < 500)
        ofile6<<At[i]<<endl;
    }

    return 0;
}
