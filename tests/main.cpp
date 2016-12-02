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

    LevelPicker picker(levelArray);

    auto firstLevel = levelArray.first();
    auto scores = picker.getScoreMap();

    WHEN("it is instantiated") {
      THEN("it has some a score map") {
        REQUIRE(scores.size() > 0);
        REQUIRE(scores.size() > 0);
      }
    }
  }
}
