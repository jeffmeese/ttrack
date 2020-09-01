#include "project.h"

#include "community.h"

Project::Project()
{

}

Project::~Project()
{

}

void Project::addCommunity(std::unique_ptr<Community> community)
{
  mCommunities.push_back(std::move(community));
}
