//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//  Round_play.cpp
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

#include "Round_play.h"
#include "utility.h"
#include "rv_library.h"
#include "IO.h"

#include <iostream>
#include <map>
#include <fstream>
#include <string>
#include <algorithm> 
#include <iomanip>

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//XX   Round_match() 
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Round_play::Round_match(Player_map & p_map, Player_vec & p_vec, 
Round_match_map & r_m_map, Record_map & r_map)
{   
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    //p_vec need to be sort before input
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    r_map.clear();
    io::Read_History(r_map);
    r_m_map.clear();//only record the present pair names
    Round_Player_vec r_p_vec;
    SR_Pair temp_pair,temp_iv_pair;
    double playersize = p_vec.size();

    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
    //find match on the list of vector one by one
    //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX    
    for (double i=0; i!=playersize; ++i)
    {   
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        //define the variable
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
    
        Name name1,name2;
        R_it it,itlow,itup;
        Rm_it rmit;
        double num0,num1;

        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
        //check and pair
        //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX 
 
        num1 = check_name1(r_m_map,p_vec[i].first);
        if(num1 == 0) 
        {   
            name1=p_vec[i].first; //i has not paired(=0), so it is the name1,

            for(double t=i; t!=playersize;++t)//use t to find name2 in the rest of p_vec 
            {
                if(t==i);//exclude himself
                else 
                {   
                    if(r_m_map.size()!=0)
                    {
                        for(rmit=r_m_map.begin();rmit!=r_m_map.end();++rmit)
                        {
                            if(p_vec[t].first==rmit->first && 
                            p_vec[t].first==rmit->second) {num0=1;}
                        };
                    };

                    if(num0==1);
                    else
                    {   //count if it this to be pair name has already pair
                        itlow = r_map.lower_bound(name1);
                        itup = r_map.upper_bound(name1);
                        for(it=itlow; it!=itup; ++it)
                        {
                            if (p_vec[t].first==it->second) {num1=1;}
                        }

                        if(num1!=1) 
                        {
                            name2=p_vec[t].first;
                            temp_pair=std::make_pair(name1,name2);
                            temp_iv_pair=std::make_pair(name2,name1);
                            r_map.insert(temp_pair); 
                            r_map.insert(temp_iv_pair);
                            r_m_map.insert(temp_pair);
                            break;
                        };
                    };
                };
            }  
        }
    }
   
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	check_name1()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Round_play::check_name1(Round_match_map & r_m_map,std::string & temp1)
{
    double num_count=0;
    for(Rm_it jit=r_m_map.begin();jit!=r_m_map.end();++jit)
    {   
        if(temp1 == jit->second) ++num_count;
    } 
    return num_count;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Round_Compete1()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Round_play::Round_Compete1(Player_map & p_map,Player_map & p_smap,
Round_match_map & r_m_map)
{
    Rm_it rit; 
    double score1;
    double score2; 
  
    std::cout << "\nHere is the match paring for this round "<< std::endl;
    for (rit=r_m_map.begin();rit!=r_m_map.end(); ++rit)
    {
        std::string name1 = rit->first;
        std::string name2 = rit->second;
        std::cout << name1 <<" vs "<< name2 << std::endl;   
    }

    for (rit=r_m_map.begin();rit!=r_m_map.end(); ++rit)
    {
        std::string name1 = rit->first;
        std::string name2 = rit->second;
        std::cout << std::endl;
        std::cout << "\nIn the game of "<< std::endl;
        std::cout << name1 <<" vs "<< name2 << std::endl;
        score1 = ut::GetDouble("Please input of the score of first player"); 
        score2 = 1 - score1;
        //update score 
        P_it pit;
        p_smap[name1] += score1;
        p_smap[name2] += score2;   
    }

}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Round_Compete2()
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Round_play::Round_Compete2(Player_map & p_map,Player_map & p_smap,
Round_match_map & r_m_map)
{
    Rm_it rit; 
    for (rit=r_m_map.begin(); rit!=r_m_map.end(); ++rit)
    {
        Name name1 = rit->first;
        Name name2 = rit->second;
        double dan1 = p_map.at(name1);
        double dan2 = p_map.at(name2);
        double x = dan1 - dan2;
        double score1=Rv_simu(x);
        double score2=1-score1;

        p_smap[name1] += score1;
        p_smap[name2] += score2;
         
        std::cout << std::left << std::setw(8) << name1 << " vs " << std::right 
        << std::setw(8)<< name2 << std::endl;
        std::cout << std::left << std::setw(8) << score1 <<" : " << std::right 
        << std::setw(8)<< score2 << std::endl;
    }
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//	Rv_simu() Do simulation
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

double Round_play::Rv_simu(double x)  
{
    double abs_x = abs(x);
    double ph;
    double pd;
    double score1;

    if (abs_x!=0) {ph=rv::normal_cdf(abs_x); pd=0.05*rv::normal_cdf(-abs_x);}
    else {pd=0.025; ph=0.4875;}

    double udp = rv::my_ran2();
    if (udp < ph) {score1 = 1;} 
    else if (udp < (ph + pd)) {score1 = 0.5;}
    else {score1 = 0;}

    if(x<0){score1 = 1 - score1;}

    return score1;
}

//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
//End
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
