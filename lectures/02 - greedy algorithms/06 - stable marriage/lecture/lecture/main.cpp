#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
int main(void)
{
   /*
   *2 disparate groups: proposers and acceptors
   */
   unordered_map<string, queue<string>> proposers{};
   unordered_map<string, vector<string>> acceptors{};
   unordered_map<string, string> matches{};

   proposers["Sarah"] = queue<string>{ {"Erik", "Sean", "Beau", "Ethan", "Justin"} };
   proposers["Carrie"] = queue<string>{ {"Beau", "Ethan", "Justin", "Sean", "Erik" } };
   proposers["Jessica"] = queue<string>{ {"Erik", "Beau", "Justin", "Sean", "Ethan" } };
   proposers["Rachel"] = queue<string>{ {"Ethan", "Justin", "Sean", "Beau", "Erik" } };
   proposers["Vanessa"] = queue<string>{ {"Erik", "Justin", "Sean", "Beau", "Ethan" } };

   acceptors["Justin"] = vector<string>{ "Sarah", "Jessica", "Carrie", "Rachel", "Vanessa" };
   acceptors["Ethan"] = vector<string>{ "Carrie", "Jessica", "Vanessa", "Rachel", "Sarah" };
   acceptors["Beau"] = vector<string>{ "Jessica", "Sarah", "Rachel", "Vanessa", "Carrie" };
   acceptors["Sean"] = vector<string>{ "Rachel", "Sarah", "Vanessa", "Jessica", "Carrie" };
   acceptors["Erik"] = vector<string>{ "Vanessa", "Rachel", "Sarah", "Carrie", "Jessica" };

   /*
   *While there exists an acceptor without a proposer
      * All Proposers simultaneously make offer to highest
     priority available Acceptor
      * All Acceptors simultaneously reject all but the most
     favorable Proposer
   */
   while (matches.size() < acceptors.size())
   {
      unordered_map<string, vector<string>> pending_matches{};

      //collate proposals into a set of pending matches
      for (auto& proposer : proposers)
      {
         string name = proposer.first;
         string desired_match = proposer.second.front();
         cout << name << " proposes to " << desired_match << endl;
         pending_matches[desired_match].push_back(name);
      }

      //for each pending match, accept only the best match
      for (auto& pending : pending_matches)
      {
         string acceptor = pending.first;
         int lowest_index = INT32_MAX;
         for (string proposer : pending.second)
         {
            for (int i = 0; i < acceptors[acceptor].size(); i++)
            {
               //example condition:
               //If JESSICA == {Preference list}
               if (proposer == acceptors[acceptor][i] && i < lowest_index)
               {
                  //record index of matched
                  matches[acceptor] = proposer;
                  lowest_index = i;
               }
            }
         }

         //at this point, acceptors have accepted an offer, but the proposer
         //hasn't been notified
         for (int i = lowest_index + 1; i < acceptors[acceptor].size(); i++)
         {
            //is this guy the current lady's first choice?  If so,
            //break the bad news.
            if (proposers[acceptors[acceptor][i]].front() == acceptor)
            {
               proposers[acceptors[acceptor][i]].pop();
            }
         }
      }
   }
   return 0;
}