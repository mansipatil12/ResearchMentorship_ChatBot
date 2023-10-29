#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

class User
{
public:
   std::string name;
   std::vector<std::string> interests;

   User(const std::string &name, const std::vector<std::string> &interests)
       : name(name), interests(interests) {}
};

class Mentor : public User
{
public:
   Mentor(const std::string &name, const std::vector<std::string> &interests)
       : User(name, interests) {}
};

class Mentee : public User
{
public:
   Mentee(const std::string &name, const std::vector<std::string> &interests)
       : User(name, interests) {}
};

struct Match
{
   Mentor mentor;
   Mentee mentee;

   Match(const Mentor &m, const Mentee &mnt) : mentor(m), mentee(mnt) {}
};

class MatchMaker
{
public:
   std::vector<Match> matches;

   MatchMaker(const std::vector<Mentor> &mentors, Mentee mentee)
   {
      for (const Mentor &mentor : mentors)
      {
         for (const std::string &interest : mentor.interests)
         {
            if (std::find(mentee.interests.begin(), mentee.interests.end(), interest) != mentee.interests.end())
            {
               Match match(mentor, mentee);
               matches.push_back(match);
               break;
            }
         }
      }
   }
};

int main()
{

   std::cout << "Welcome to the Mentor-Mentee Matching Chat Bot!" << std::endl;

   std::vector<Mentor> mentors;

   std::cout << "Loading mentors..." << std::endl;

   std::ifstream file("mentors.txt");
   std::string line;

   while (std::getline(file, line))
   {
      std::istringstream iss(line);
      std::string name;
      iss >> name;

      std::vector<std::string> interests;
      std::string interest;
      while (iss >> interest)
      {
         interests.push_back(interest);
      }

      Mentor mentor(name, interests);
      mentors.push_back(mentor);
   }

   if (mentors.size() == 0)
   {
      std::cout << "No mentors found!" << std::endl;
      return 0;
   }

   std::cout << "Mentors loaded!" << std::endl;

   std::string mentee_name;
   std::cout << "Enter the name of the mentee: ";
   std::cin >> mentee_name;

   std::vector<std::string> mentee_interests;
   std::string mentee_interest;
   std::cout << "Enter the interests of the mentee (enter q to stop): ";
   for (;;)
   {
      std::cin >> mentee_interest;
      if (mentee_interest == "q")
      {
         break;
      }
      mentee_interests.push_back(mentee_interest);
   }

   Mentee mentee(mentee_name, mentee_interests);

   std::cout << "Finding matches..." << std::endl;

   MatchMaker match_maker(mentors, mentee);

   for (const Match &match : match_maker.matches)
   {
      std::cout << match.mentor.name << " matches with " << match.mentee.name << std::endl;
   }
}
