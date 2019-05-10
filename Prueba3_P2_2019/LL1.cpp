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

    for (GSymbolPtr currSymbol : set) {
        GSymbolPtrSet gsps = getFirsts(currSymbol);
        std::cout << currSymbol->getName() << " firsts:";
        for (GSymbolPtr igsp : gsps) {
            std::cout << igsp->getName() << ",";
            if (igsp == gr.getSymbol("''"))
            {
                std::cout << "i need my follows:";
                GSymbolPtrSet gsps_follows = getFollows(currSymbol);
            }
        }
        std::cout << "\n";

        GRulePtrVector grpv = gr.getRulesFor(currSymbol);
        
        //TableRow tr1("T'", grpv[0]);
        //tbl.insert("T'", gsps);
    }

    






    std::cout << "\n/******************/\n\n";
    for (GRulePtr gp : gr.getAllRules()) 
    {

        std::cout << gp->toString() << std::endl;
        //std::cout << "Aqui pasa algo\n";
    }
}

