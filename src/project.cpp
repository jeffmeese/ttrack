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
  connect(c, SIGNAL(workStatusChanged(bool)), SLOT(handleWorkStatusChanged(bool)));
  mCommunities.push_back(std::move(community));
  emit communityAdded(c);
}

void Project::handleWorkStatusChanged(bool working)
{
  Community * community = reinterpret_cast<Community*>(sender());
  for (std::size_t i = 0; i < totalCommunities(); i++) {
    Community * existing = mCommunities.at(i).get();
    if (working && existing != community && existing->working()) {
      existing->stopWork();
    }
  }
}

void Project::setModified(bool value)
{
  mModified = value;
  emit modified(value);
}
