//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Round_play.h
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#ifndef Round_playH
#define Round_playH
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "utility.h"

#include <fstream>
#include <vector>
#include <string>
#include <map>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
// namespace Round_play
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

 namespace Round_play
{                                                                     
    typedef std::pair<std::string, double> S_Pair; 
    typedef std::vector<S_Pair> Player_vec; 
    typedef std::pair<std::string,std::string> SR_Pair;
    typedef std::string Name;

    typedef std::vector<SR_Pair> Round_Player_vec;                                                                       
    typedef std::map<std::string, double> Player_map;
    typedef std::map<std::string,std::string> Round_match_map;
    typedef std::multimap<std::string,std::string> Record_map;
    
    typedef std::multimap<double,std::string> In_Player_map;
    typedef Record_map::iterator R_it;
    typedef Player_map::iterator P_it;
    typedef Round_match_map::iterator Rm_it;
    typedef Player_map::const_iterator P_cit;
    typedef In_Player_map::const_iterator In_P_cit;
    typedef Player_map::const_reverse_iterator R_P_cit;
    typedef In_Player_map::const_reverse_iterator R_In_P_cit;

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    //	declarations
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    void Round_match(Player_map & p_map, Player_vec & p_vec, 
    Round_match_map & r_m_map, Record_map & r_map);
    
    double check_name1(Round_match_map & r_m_map,std::string & temp1);
    
    void Round_Compete1(Player_map & p_map, Player_map & p_smap,Round_match_map & r_m_map);
    void Round_Compete2(Player_map & p_map,Player_map & p_smap,Round_match_map & r_m_map);                
    
    double Rv_simu(double x);
    void Sort_vec(Player_vec & p_vec);
}

namespace rp = Round_play; //alias

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
#endif
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
