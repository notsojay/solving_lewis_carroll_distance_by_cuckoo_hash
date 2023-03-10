#include "convert.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}

// You probably want to change this function.
std::vector< std::string > convert(const std::string & s1, const std::string & s2, const WordSet & words)
{
	if(!words.contains(s1) || !words.contains(s2) || words.getCount() == 0 || s1.size() != s2.size() || s1.empty() || s2.empty()) return {};
	if(s1 == s2) return {s1};
	std::vector< std::string > ret;
	std::unordered_map<std::string, std::string> paths;
	std::unordered_set<std::string> visited;
	std::queue<std::string> q;
	int distance = 0;
	q.push(s1);
	while(!q.empty())
	{
		size_t qSize = q.size();
		++distance;
		for(size_t i = 0; i < qSize; ++i)
		{
			std::string currentStr = q.front();
			q.pop();
			for(size_t j = 0; j < currentStr.size(); ++j)
			{
				std::string temp = currentStr;
				for(char k = 'a'; k <= 'z'; ++k)
				{
					temp[j] = k;
					if(temp == currentStr)
					{
						continue;
					}
					if(temp == s2)
					{
						paths[s2] = currentStr;
						getPath(paths, ret, s2, distance);
						return ret;
					}
					if(words.contains(temp) && visited.find(temp) == visited.end())
					{
						paths[temp] = currentStr;
						q.push(temp);
						visited.insert(temp);
					}
				}
			}
		}
	}
	return {};
}

void getPath(const std::unordered_map<std::string, std::string> & paths, std::vector< std::string > & ret, const std::string & s2, const int & distance)
{
	ret.resize(distance+1, "");
	ret[distance] = s2;
	for(int i = distance-1; i >= 0; --i)
	{
		ret[i] = paths.find(ret[i+1])->second;
	}
}