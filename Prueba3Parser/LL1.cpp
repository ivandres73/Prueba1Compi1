#include <iostream>
#include <algorithm>
#include "LL1.h"

LL1::LL1(Grammar &gr,
         const StringToStringSetMap& _firsts,
         const StringToStringSetMap& _follows): gr(gr)
{
    for (const auto& f : _firsts) {
        std::string nt_name = f.first;
        const StringSet& sset = f.second;
        GSymbolPtrSet symb_set;

        std::transform(sset.begin(), sset.end(), std::inserter(symb_set, symb_set.end()),
                        [&gr](const std::string& s) { return gr.getSymbol(s); });

        firsts[nt_name] = std::move(symb_set);
    }

    for (const auto& f : _follows) {
        std::string nt_name = f.first;
        const StringSet& sset = f.second;
        GSymbolPtrSet symb_set;

        std::transform(sset.begin(), sset.end(), std::inserter(symb_set, symb_set.end()),
                        [&gr](const std::string& s) { return gr.getSymbol(s); });

        follows[nt_name] = std::move(symb_set);
    }
}

GSymbolPtrSet LL1::getFirsts(const GSymbolPtrVector& symbv) {
    /* TODO: Implement this function */
    for (GSymbolPtr gsp : symbv) {
        std::cout << "algo pasa";
        gsp->getName();
    }
}

void LL1::computeTable()
{
    /* TODO: Implement this function */
    GSymbolPtrVector set = gr.getNonTerminals();
    bool flag;

    for (GSymbolPtr currSymbol : set) {
        flag = false;
        GSymbolPtrSet gsps = getFirsts(currSymbol);
        std::cout << currSymbol->getName() << " firsts:\n";
        TableRow tr1; 
        for (GSymbolPtr igsp : gsps) {
            std::cout << igsp->getName() << ",";
            if (igsp == gr.getSymbol("''"))
            {
                flag = true;
                continue;
            }
            GRulePtrVector grpv = gr.getRulesFor(currSymbol);
            for (GRulePtr grp : grpv)
            {
                if (grp->getRHS().front()->isTerminal())
                {
                    if (grp->getRHS().front()->getName() != igsp->getName())
                    {
                        continue;
                    }
                }
                tr1.emplace(igsp->getName(), grp);
                std::cout << " ||row es [" << igsp->getName() << ", " << grp->toString() << "] en " << currSymbol->getName() << std::endl;
                
                //tr1.erase(igsp->getName());
                break;
            }
            
            
        }
        tbl.emplace(currSymbol->getName(), tr1);
        if (flag) {
            std::cout << "\ni need my follows:\n";
            GSymbolPtrSet gsps_follows = getFollows(currSymbol);
            for (GSymbolPtr igsp2 : gsps_follows)
            {
                std::cout << igsp2->getName() << ",";
                GRulePtrVector grpv = gr.getRulesFor(currSymbol);
                for (GRulePtr grp : grpv)
                {
                    if (grp->getRHS().front()->getName() == "''")
                    {
                        TableRow tr2;
                        tr2.emplace(igsp2->getName(), grp);
                        std::cout << " ||row es [" << igsp2->getName() << ", " << grp->toString() << "] en " << currSymbol->getName() << std::endl;
                        tbl.emplace(currSymbol->getName(), tr2);
                        tr2.erase(igsp2->getName());
                    }
                }
            }
        }
       
        std::cout << "\n";
    }

    






    std::cout << "\n/******************/\n\n";
    for (GRulePtr gp : gr.getAllRules()) 
    {

        std::cout << gp->toString() << std::endl;
        //std::cout << "Aqui pasa algo\n";
    }
}

