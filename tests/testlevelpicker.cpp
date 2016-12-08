#include "tests.h"

/* testing with a private member
class TestLevelPicker : public LevelPicker {
public:
    TestLevelPicker(QJsonArray array) : LevelPicker(array) {}
    std::map<QString, Score*> getScoreMap() {
        return scoreMap;
    }
};
*/

SCENARIO("level picker creates scores and levels", "[levelPicker]") {

  GIVEN("level.json with some items") {

    QFile levelFile("level.json");
    levelFile.open(QIODevice::ReadOnly);
    auto json = QJsonDocument::fromJson(levelFile.readAll());
    auto levelArray = json.array();
    levelFile.close();

    // LevelPicker picker(levelArray);

    // auto firstLevel = levelArray.first();
    // auto scores = picker.getScoreMap();

    //    void testPicker(LevelPicker *picker, ScoreThingee *scores) {
    //      picker->setRead("Gen-1-1", .5);
    //      picker->setRead("Mat-19-16", 1);
    //      picker->setRead("Luk-2-8", 1);
    //      picker->setRead("Mat-6-19", 1);
    //      picker->setRead("Acts-2-1", 1);

    //      for (int i = 0; i < 100; i++) {
    //        auto picked = picker->pick();

    //        qDebug() << " picked: " << picked->getName() << " " <<
    //        picked->getWeight()
    //                 << " " << picked->getRank();

    //        qDebug() << "before: " << time(0);
    //        scores->saveScores();
    //        qDebug() << "after: " << time(0);
    //      }
    //    }

    WHEN("it is instantiated") {
      THEN("it has some a score map") {
        // REQUIRE(scores.size() > 0);
        // REQUIRE(scores.size() > 0);
      }
    }
  }
}
