#ifndef PROJECT_H
#define PROJECT_H

#include <QDataStream>
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
  void loadFromFile(const QString & fileName);
  void loadFromStream(QDataStream & dataStream);
  bool removeCommunity(Community * community);
  bool removeCommunity(std::size_t index);
  void saveToFile(const QString & fileName) const;
  void saveToStream(QDataStream & dataStream) const;
  std::size_t totalCommunities() const;

public slots:
  void handleWorkStatusChanged(bool working);
  void setModified(bool modified = true);

signals:
  void communityAdded(Community * community);
  void modified(bool value);

private:
  using CommunityPtr = std::unique_ptr<Community>;
  using CommunityVector = std::vector<CommunityPtr>;

private:
  bool mModified;
  CommunityVector mCommunities;
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
