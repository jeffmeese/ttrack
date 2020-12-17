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
  Community * c = community.get();
  connect(c, SIGNAL(changed()), SLOT(setModified()));
  mCommunities.push_back(std::move(community));
  emit communityAdded(c);
}

void Project::setModified(bool value)
{
  mModified = value;
  emit modified(value);
}
