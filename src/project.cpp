#include "project.h"

#include "community.h"
#include "streamio.h"

#include <QFile>

#include <cstdint>
#include <sstream>
#include <stdexcept>

const char FILE_HEADER[12] = "TTRACK.FILE";
static const int32_t FILE_VERSION = 1;

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

void Project::loadFromFile(const QString &fileName)
{
  QFile inputFile(fileName);
  if (!inputFile.open(QIODevice::ReadOnly)) {
    std::ostringstream oss;
    oss << "Could not open file " << fileName.toStdString() << " for reading";
    throw std::invalid_argument(oss.str());
  }

  QDataStream dataStream(&inputFile);
  loadFromStream(dataStream);
}

void Project::loadFromStream(QDataStream &dataStream)
{
  QString fileHeader = streamio::readString(dataStream);
  if (fileHeader != QString(FILE_HEADER)) {
    std::ostringstream oss;
    oss << "Invalid file header";
    throw std::invalid_argument(oss.str());
  }

  int32_t fileVersion = 0;
  dataStream >> fileVersion;

  int32_t totalCommunities = 0;
  dataStream >> totalCommunities;
  QString id = streamio::readString(dataStream);
  for (int i = 0; i < totalCommunities; i++) {
    std::unique_ptr<Community> community(new Community);
    community->loadFromDataStream(dataStream);
  }
}

void Project::saveToFile(const QString &fileName) const
{
  QFile outputFile(fileName);
  if (!outputFile.open(QIODevice::WriteOnly)) {
    std::ostringstream oss;
    oss << "Could not open file " << fileName.toStdString() << " for writing";
    throw std::invalid_argument(oss.str());
  }

  QDataStream dataStream(&outputFile);
  saveToStream(dataStream);
}

void Project::saveToStream(QDataStream &dataStream) const
{
  streamio::writeString(FILE_HEADER, dataStream);
  dataStream << FILE_VERSION;

  dataStream << static_cast<int32_t>(mCommunities.size());
  for (std::size_t i = 0; i < mCommunities.size(); i++) {
    const Community * community = mCommunities.at(i).get();
    community->saveToDataStream(dataStream);
  }
}

void Project::setModified(bool value)
{
  mModified = value;
  emit modified(value);
}
