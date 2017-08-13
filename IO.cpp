//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  IO.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "IO.h"
#include "utility.h"

#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm> 
#include <iomanip>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Input_Data()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Input_Data(Player_map & p_map, Player_map & p_smap, 
Player_vec & p_vec)
{
    std::ifstream i_stream;
    i_stream.open("Player.txt");

    if(i_stream.fail()) 
    {
        throw std::runtime_error("database file not found");
        i_stream.close();
    }    

    std::string name;
    double Dan;
    
    while (i_stream >> name >> Dan)
    {
        S_Pair temp_pair = std::make_pair(name,Dan);
        p_map.insert(temp_pair); //using a map to store dan
        p_vec.push_back(temp_pair); //using a vector pair to store score
        p_smap.insert(temp_pair);//using a map to store score  
    }

    i_stream.close();    
    Sort_vec(p_vec);
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

    std::cout << std::left << std::setw(15)<<"XXXXXXXX The # "
<< round << " result XXXXXXXX"<< std::endl;

    for(Player_vec::iterator rcit=p_vec.begin(); rcit != p_vec.end(); ++rcit)
    {
        std::cout << std::left << std::setw(15) <<(*rcit).first 
        << ' ' << std::setw(15) << (*rcit).second << std::endl;
    }

    std::cout << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Output_Result()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Output_Result(Player_vec & p_vec)
{
    Player_vec::iterator rcit=p_vec.begin();

    std::cout << "The winner of the game is "<< (*rcit).first<<std::endl;
    std::cout << std::endl;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  WriteInFile()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::WriteInFile(Player_map & p_smap, long & round, Player_vec & p_vec)
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
    theFile.open("Score.txt");

    for(Player_vec::iterator rcit=p_vec.begin(); rcit != p_vec.end(); ++rcit)
    {
        theFile << std::left << std::setw(15) << (*rcit).first  
        << ' ' << std::setw(15) << (*rcit).second << std::endl;
    }

    theFile.close();  
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Read_Score()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Read_Score(Player_map & p_smap)
{
    std::ifstream i_stream;
    i_stream.open("Score.txt");

    if(i_stream.fail()) 
    {
        i_stream.close();
    }    

    std::string name1;
    double score;

    while (i_stream >> name1 >> score)
    {
        p_smap.insert(std::make_pair(name1,score));
    }

    i_stream.close();    
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Read_History()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Read_History(Record_map & r_map)
{
    std::ifstream i_stream;
    i_stream.open("History.txt");

    if(i_stream.fail()) 
    {
        i_stream.close();
    }    

    std::string name1, name2;

    while (i_stream >> name1 >> name2){
          r_map.insert(std::make_pair(name1,name2));
    }
    i_stream.close();    

}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Write_History()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Write_History(Record_map & r_map)
{
    std::ofstream o_stream("History.txt");

    R_it rit;
    for(rit=r_map.begin(); rit!=r_map.end(); ++rit)
    {
        std::ostringstream os;

        os << std::left << std::setw(15) <<(*rit).first 
        << ' ' << std::setw(15) << (*rit).second << std::endl;
        o_stream << os.str();
    }

    o_stream.close();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Sort_vec()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void InputOutput::Sort_vec(Player_vec & p_vec)
{
    
    std::sort(p_vec.begin(),p_vec.end(),compu_by_value);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	bool compu_by_value()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

bool InputOutput::compu_by_value(const S_Pair & a, const S_Pair & b)
{
    return a.second > b.second;
} 

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
