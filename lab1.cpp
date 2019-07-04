#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

vector<int> init(int ans_size)
{
    vector<int> v;
    for(int i = 0; i < ans_size; i++)
        v.push_back(0);
    return v;
}

int toint(string str)
{
    int temp = 0;
    for(int i = 0; i < str.size(); i++)
    {
        if(str[i] >= 48 && str[i] <= 55) // 0~9
        {
            temp += str[i] - 48;
            temp *= 16;
        }
        else if(str[i] == 56 || str[i] == 57)
        {
            if(i == 0)
            {
                temp += str[i] - 56;
                temp *= 16;
            }
            else
            {
                temp += str[i] - 48;
                temp *= 16;
            }
        }
        else if(str[i] >= 97 && str[i] <= 102) // a~f
        {
            if(i == 0)
            {
                temp += str[i] - 95;
                temp *= 16;
            }
            else
            {
                temp += str[i] - 87;
                temp *= 16;
            }
        }
    }
    temp /= 16;
    if(str[0] == 56 || str[0] == 57 || (str[0] >= 97 && str[0] <= 102)) temp -= 32768;

    return temp;
}

char DectoHex(int n)
{
    char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    return hex[n];
}

string tostr(int i)
{
    string str;

    if(i > 0)
    {
        while(i > 0)
        {
            str = DectoHex(i % 16) + str;
            i /= 16;
        }
    while(str.size() < 8) str = "0" + str;
    }

    else
    {
        int temp = abs(i) - 1;
        while(temp > 0)
        {
            str = DectoHex(temp % 16) + str;
            temp /= 16;
        }
        for(int k = 0; k < str.size(); k++)
        {
            if(str[k] >= 48 && str[k] <= 57) str[k] = DectoHex(15 - (str[k] - 48));
            else str[k] = DectoHex(15 - (str[k] - 87));
        }
    while(str.size() < 8) str = "f" + str;
    }
    return str;

}

int main()
{
    for(int i = 1; i <= 16; i++)
    { 
        char input_body[5], weight_body[5];
        string str;
        vector<int> ans, output_ans = init(676);
        int ans_size = 0;

        for(int j = 1; j <= 3; j++)
        {
            ans.clear();
    
            vector<int> input, filter;
            char weight_[15] = "./Data/weight_";
            
            memset(input_body, 0, sizeof(input_body));
            sprintf(input_body, "%d", j);
            strcat(weight_, input_body);
            strcat(weight_, "_");
            memset(weight_body, 0, sizeof(weight_body));
            sprintf(weight_body, "%d", i);
            strcat(weight_, weight_body);
            char filename_tail[5] = ".txt";
            strcat(weight_, filename_tail);

            ifstream in(weight_, ios::in);
            while(getline(in, str, '\n'))
            {
                int temp = toint(str);
                filter.push_back(temp);
            }
    
            char input_[14] = "./Data/input_";
            strcat(input_, input_body);
            strcat(input_, filename_tail);
            ifstream inn(input_, ios::in);

            while(getline(inn, str, '\n'))
            {
                int temp = toint(str);
                input.push_back(temp);
            }

            ans_size = (sqrt(input.size()) - sqrt(filter.size()) + 1) * sqrt(input.size());
            ans = init(676);
            
            for(int k = 0, n = 0; k < ans_size; k++)
            {
                if(((k+2)%28 ==0) || ((k+1)%28==0)) continue;
                int temp = input.at(k) * filter[0] + input.at(k+1) * filter[1] + input.at(k+2) * filter[2]
                         + input.at(k+28) * filter[3] + input.at(k+29) * filter[4] + input.at(k+30) * filter[5]
                         + input.at(k+56) * filter[6] + input.at(k+57) * filter[7] + input.at(k+58) * filter[8];
                ans.at(n++) += temp;
            }
           
            for(int k = 0; k < output_ans.size(); k++)
            {
                output_ans.at(k) += ans.at(k);
            }
               
            in.close();
            inn.close();
        }
                    
        char output_[12] = "output_ans_";
        memset(input_body, 0, sizeof(input_body));
        sprintf(input_body, "%d", i);
        strcat(output_, input_body);
        char filename_tail[5] = ".txt";
        strcat(output_, filename_tail);
        
        fstream out(output_, ios::out);
        for (int k = 0; k < output_ans.size(); k++)
        {
            out << tostr(output_ans.at(k)) << endl;
        }
        out.close();
    }
        
    return 0;
}
