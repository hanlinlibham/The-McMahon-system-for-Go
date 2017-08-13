//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX   McMahon System ID:1673177
//XX   main.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "IO.h"
#include "utility.h"

#include <iostream>
#include <map>
#include <fstream>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	declaration of public fns
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Titles();
void Inputconsole(long & pnum, long & round, long & op, long & sl);

void run(long & pnum, long & round, long & op, long & sl, 
     rp::Player_vec & p_vec, rp::Player_map & p_map, 
     rp::Round_match_map & r_m_map,rp::Record_map & r_map, 
     rp::Player_map & p_smap);

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	main()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

int main(int argc, char *argv[])
{   
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    //	set up
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    rp::Player_map p_map,p_smap; //build a map to store dan and score
    rp::Player_vec p_vec; //build a vector to store score 
    rp::Record_map r_map; //build a multimap to store history pair 
    rp::Round_match_map r_m_map; //build a map to store current round pair 
    long pnum, round, op, sl;

    io::Input_Data(p_map, p_smap, p_vec);// initialise the data
    pnum = p_vec.size(); //count on the player number

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    //	app
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

    Titles();
    
    Inputconsole(pnum, round, op, sl);
    
    run(pnum, round, op, sl, p_vec, p_map, r_m_map, r_map, p_smap);

    return ut::PauseAndReturn();
}
 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Titles()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Titles()
{
    ut::OutputLine("Here is the McMahon System Program");
    std::cout<<std::endl;
    ut::OutputLine("Any change for player can be made in the Play.txt");
    ut::PauseAndContinue();
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Inputconsole()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Inputconsole(long & pnum, long & round, long & op, long & sl)
{
    std::string banner0 = "The number of player is";
    std::string banner1 = "Select the \n 1:Start a new game"; 
    banner1 += "\n 2:Load from the history";
    std::string banner2 = "Please input the total round";
    std::string banner3 = "Select the \n 1:Input result \n 2:Do simulation";

    ut::OutputLine(banner0, pnum); 
    sl = ut::GetLongInRange(banner1, 1, 2);

    if(sl != 1){round = 1;}
    else
    {
        round = ut::GetLongInRange(banner2, 1, pnum-1);
        op = ut::GetLongInRange(banner3, 1, 2);
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	run()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void run(long & pnum, long & round, long & op, long & sl, 
     rp::Player_vec & p_vec, rp::Player_map & p_map, 
     rp::Round_match_map & r_m_map, 
     rp::Record_map & r_map, rp::Player_map & p_smap)
{
    
    if (pnum%2==0)
    {
        p_vec.push_back(std::make_pair("BYE",0));
        p_map.insert(std::make_pair("BYE",0));
    }
    
    if (sl != 1) op = 1;
    
    for (long r = 1; r!=round+1 ; ++r)
    {   
        io::Read_Score(p_smap);
        
        switch(op)
        {
            case 1: 
                rp::Round_match(p_map, p_vec, r_m_map, r_map);
                rp::Round_Compete1(p_map, p_smap, r_m_map);
                break;
            case 2: 
                rp::Round_match(p_map, p_vec, r_m_map, r_map);
                rp::Round_Compete2(p_map, p_smap, r_m_map);
                break;
        }

        io::Output_Data(p_smap, r, p_vec);
        io::Write_History(r_map);
        io::WriteInFile(p_smap, round, p_vec);

        ut::GetString("press any key to continue");
    }

    io::Output_Result(p_vec);
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	end
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
