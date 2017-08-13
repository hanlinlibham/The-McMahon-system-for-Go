//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  IO.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef IOH
#define IOH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "utility.h"
#include "Round_play.h"

#include <fstream>
#include <vector>
#include <string>
#include <map>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  namespace InputOutput
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

namespace InputOutput
{
	typedef std::vector<std::string> & Get_Name ; 
	typedef std::vector<double> & Get_Dan;
    typedef std::vector<double> & Get_Score;

    typedef std::map<std::string, double> Player_map;
    typedef std::multimap<std::string,std::string> Record_map;
    
    typedef std::multimap<double,std::string> In_Player_map;
    typedef std::pair<std::string, double> S_Pair;
    typedef std::vector<S_Pair> Player_vec;
    typedef std::pair<std::string,std::string> SR_Pair;
    
    typedef Record_map::iterator R_it;
    typedef Player_map::iterator P_it;
    typedef Player_map::const_iterator P_cit;
    typedef In_Player_map::const_iterator In_P_cit;
    typedef Player_map::const_reverse_iterator R_P_cit;
    typedef In_Player_map::const_reverse_iterator R_In_P_cit;

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    //	declarations
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    
    void Input_Data(Player_map & p_map, Player_map & p_smap, 
    Player_vec & p_vec);

    void Read_History(Record_map & r_map);
    void Read_Score(Player_map & p_smap);

    bool compu_by_value(const S_Pair & a, const S_Pair & b);   
    void Sort_vec(Player_vec & p_vec); 
    void Output_Data(Player_map & p_smap, long & round, Player_vec & p_vec);
    void Write_History(Record_map & r_map);
    void WriteInFile(Player_map & p_smap, long & round, Player_vec & p_vec);
    void Output_Result(Player_vec & p_vec);
}

namespace io = InputOutput; //alias

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
