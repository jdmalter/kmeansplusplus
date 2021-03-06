#ifndef MAIN_H
#define MAIN_H

#include <fstream>
#include <vector>
#include "darray.h"
#include "kmeans.cpp"

using namespace std;

ifstream createInput(const char* s)
{
    ifstream input;
    input.open(s);
    if (!input)
    {
        cout << "Must be able to read from " << s << endl;
        exit(1);
    }
    return input;
}

ofstream createOutput(const char* s)
{
    ofstream output;
    output.open(s);
    if (!output)
    {
        cout << "Must be able to write to " << s << endl;
        exit(1);
    }
    return output;
}

template<csize d>
void write(ofstream &output, 
        const vector<darray<d>> &vectors, 
        const vector<string> &strings, 
        csize k, 
        const vector<darray<d>> clusters)
{
    for (int i = 0; i < k; i++)
    {
        vector<int> group;
        for (int j = 0; j < vectors.size(); j++)
        {
            if (i == vectors[j].assignment)
            {
                group.push_back(j);
            }
        }
        
        string clusterString = toPrettyString<d>(clusters[i]);
        output << "cluster at " << clusterString << " with " << group.size() << " vectors" << endl;
        for (int j = 0; j < group.size(); j++)
        {
            string vectorString = toPrettyString<d>(vectors[group[j]]);
            output << vectorString << " " << strings[group[j]] << endl;
        }
        output << endl;
    }
}

#endif /* MAIN_H */
