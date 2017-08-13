//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  IO.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm> 
#include <iomanip>

#include "IO.h"
#include "utility.h"


//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Input_Data()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Input_Data(Player_map & p_map, Player_map & p_smap, Player_vec & p_vec)
{
    std::ifstream theFile("Player.txt");
    std::vector<std::string> p_names;
    std::vector<double> G_Dan;
    std::string name;
    double Dan;
    
    while (theFile >> name >> Dan){
          p_names.push_back(name);
          G_Dan.push_back(Dan);
    }

    for (double i=0; i!=G_Dan.size(); ++i)
        {
        S_Pair temp_pair = std::make_pair(p_names[i],G_Dan[i]);
        p_map.insert(temp_pair); //using a map to store dan
        p_vec.push_back(temp_pair); //using a vector pair to store score
        p_smap.insert(temp_pair);//using a map to store score  
        }
    Sort_vec(p_vec);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Sort_vec()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Sort_vec(Player_vec & p_vec)
{
    
    std::sort(p_vec.begin(),p_vec.end(),compu_by_value);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Output_Data()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Output_Data(Player_map & p_smap, long & round, Player_vec & p_vec)
{
    P_it pit;
    p_vec.clear();
    for(pit=p_smap.begin(); pit!=p_smap.end(); ++pit)
    {
        S_Pair temp=std::make_pair(pit->first,pit->second);
        p_vec.push_back(temp); 
    }
    Sort_vec(p_vec);
    std::ofstream theFile;
    theFile.open("Score.txt",std::ios::app);

    theFile <<"XXXXXXXX The # "<< round << " result XXXXXXXX"<< std::endl;
    std::cout << std::left << std::setw(15)<<"XXXXXXXX The # "<< round << " result XXXXXXXX"<< std::endl;

    for(auto rcit=p_vec.cbegin(); rcit != p_vec.cend(); ++rcit)
    {
    std::cout << std::left << std::setw(15) <<(*rcit).first << ' ' << std::setw(15) << (*rcit).second << std::endl;
    theFile << std::left << std::setw(15) << (*rcit).first  << ' ' << std::setw(15) << (*rcit).second << std::endl;
    }

    std::cout << std::endl;
    theFile << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
