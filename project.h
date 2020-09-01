#ifndef PROJECT_H
#define PROJECT_H

#include <memory>
#include <vector>

class Community;

class Project
{
public:
  Project();
  ~Project();

public:
  void addCommunity(std::unique_ptr<Community> community);
  const Community * getCommunity(std::size_t index) const;
  Community * getCommunity(std::size_t index);
  std::size_t totalCommunities() const;


private:
  using CommunityPtr = std::unique_ptr<Community>;

private:
  std::vector<CommunityPtr> mCommunities;
};

inline const Community * Project::getCommunity(std::size_t index) const
{
  return mCommunities.at(index).get();
}

inline Community * Project::getCommunity(std::size_t index)
{
  return mCommunities.at(index).get();
}

inline std::size_t Project::totalCommunities() const
{
  return mCommunities.size();
}

#endif // PROJECT_H
