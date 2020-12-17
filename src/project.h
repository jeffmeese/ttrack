#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>

#include <memory>
#include <vector>

class Community;

class Project
    : public QObject
{
  Q_OBJECT

public:
  Project();
  ~Project();

public:
  bool modified() const;

public:
  void addCommunity(std::unique_ptr<Community> community);
  const Community * getCommunity(std::size_t index) const;
  Community * getCommunity(std::size_t index);
  std::size_t totalCommunities() const;

public slots:
  void setModified(bool modified = true);

signals:
  void communityAdded(Community * community);
  void modified(bool value);

private:
  using CommunityPtr = std::unique_ptr<Community>;

private:
  bool mModified;
  std::vector<CommunityPtr> mCommunities;
};

inline bool Project::modified() const
{
  return mModified;
}

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
