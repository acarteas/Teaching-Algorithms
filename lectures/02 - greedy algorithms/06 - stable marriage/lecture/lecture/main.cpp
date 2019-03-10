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
   unordered_map<string, unordered_map<string, int>> acceptors{};
   unordered_map<string, string> matches{};
   unordered_map<string, int> match_ranks{};

   proposers["Sarah"] = queue<string>{ {"Erik", "Sean", "Beau", "Ethan", "Justin"} };
   proposers["Carrie"] = queue<string>{ {"Beau", "Ethan", "Justin", "Sean", "Erik" } };
   proposers["Jessica"] = queue<string>{ {"Erik", "Beau", "Justin", "Sean", "Ethan" } };
   proposers["Rachel"] = queue<string>{ {"Ethan", "Justin", "Sean", "Beau", "Erik" } };
   proposers["Vanessa"] = queue<string>{ {"Erik", "Justin", "Sean", "Beau", "Ethan" } };

   acceptors["Justin"]["Sarah"] = 0;
   acceptors["Justin"]["Jessica"] = 1;
   acceptors["Justin"]["Carrie"] = 2;
   acceptors["Justin"]["Rachel"] = 3;
   acceptors["Justin"]["Vanessa"] = 4;

   acceptors["Ethan"]["Carrie"] = 0;
   acceptors["Ethan"]["Jessica"] = 1;
   acceptors["Ethan"]["Vanessa"] = 2;
   acceptors["Ethan"]["Rachel"] = 3;
   acceptors["Ethan"]["Sarah"] = 4;

   acceptors["Beau"]["Jessica"] = 0;
   acceptors["Beau"]["Sarah"] = 1;
   acceptors["Beau"]["Rachel"] = 2;
   acceptors["Beau"]["Vanessa"] = 3;
   acceptors["Beau"]["Carrie"] = 4;

   acceptors["Sean"]["Rachel"] = 0;
   acceptors["Sean"]["Sarah"] = 1;
   acceptors["Sean"]["Vanessa"] = 2;
   acceptors["Sean"]["Jessica"] = 3;
   acceptors["Sean"]["Carrie"] = 4;

   acceptors["Erik"]["Vanessa"] = 0;
   acceptors["Erik"]["Rachel"] = 1;
   acceptors["Erik"]["Sarah"] = 2;
   acceptors["Erik"]["Carrie"] = 3;
   acceptors["Erik"]["Jessica"] = 4;

   //initialize match ranks
   for (auto acceptor : acceptors)
   {
      match_ranks[acceptor.first] = INT_MAX;
   }
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

      //go until potential match found
      while (match_ranks[desired_match] < acceptors[desired_match][name])
      {
         proposer.second.pop();
         desired_match = proposer.second.front();
      }

      //record the match
      match_ranks[desired_match] = acceptors[desired_match][name];
      matches[desired_match] = name;

      cout << name << " proposes to " << desired_match << endl;
   }
}
return 0;
}