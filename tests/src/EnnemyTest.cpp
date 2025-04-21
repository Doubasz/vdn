// EnnemyTest.cpp
#include <gtest/gtest.h>
#include "Ennemy.h"
#include "Entity.h"

// Stub minimal d'Entity pour overlaps()
struct EntityMock : public Entity {
    EntityMock(int x, int y, int w = 1, int h = 1) {
        box = {x,y,w,h};
        setVel(0, 0);
    }
};

// Fixture
class EnnemyTest : public ::testing::Test {
protected:
    Ennemy enemy;

    std::vector<std::vector<int>> makeMap(int width, int height, int fill) {
        return std::vector<std::vector<int>>(height, std::vector<int>(width, fill));
    }
};

TEST_F(EnnemyTest, DefaultConstructor) {
    EXPECT_EQ(enemy.getVel().x, 1);
    EXPECT_EQ(enemy.getVel().y, 0);
    EXPECT_EQ(enemy.getBox().x, 0);
    EXPECT_EQ(enemy.getBox().y, 0);
    EXPECT_EQ(enemy.getBox().w, 1);
    EXPECT_EQ(enemy.getBox().h, 1);
    EXPECT_EQ(enemy.getHp(), 2);
    EXPECT_FLOAT_EQ(enemy.iFrames, 0.4f);
    EXPECT_TRUE(enemy.isAlive);
}

TEST_F(EnnemyTest, ParamConstructorSetsPositionAndType) {
    Ennemy e2(10, 20, 5);
    EXPECT_EQ(e2.getBox().x, 10);
    EXPECT_EQ(e2.getBox().y, 20);
    EXPECT_EQ(e2.getType(), 5);
}

TEST_F(EnnemyTest, ChangePosition) {
    enemy.changePosition(3, 4);
    EXPECT_EQ(enemy.getBox().x, 3);
    EXPECT_EQ(enemy.getBox().y, 4);
}

TEST_F(EnnemyTest, UpdateAppliesVelocityAndGravity) {
    // on utilise setVel pour initialiser
    enemy.changePosition(1, 1);
    enemy.setVel(2, -1);
    // gravity par défaut = 0
    enemy.update(1);  // deltaTime = 1
    EXPECT_EQ(enemy.getBox().x, 3); // 1 + 2*1
    EXPECT_EQ(enemy.getBox().y, 0); // 1 + (-1)*1
}

TEST_F(EnnemyTest, ChangeDirectionFlipsXVelocity) {
    enemy.setVel(4, 0);
    enemy.changeDirection();
    EXPECT_EQ(enemy.getVel().x, -4);
    enemy.changeDirection();
    EXPECT_EQ(enemy.getVel().x, 4);
}

TEST_F(EnnemyTest, PlayerOutOfRange) {
    EntityMock playerNear(enemy.getBox().x + 3, enemy.getBox().y);
    EXPECT_FALSE(enemy.PlayerOutofRange(playerNear));
    EntityMock playerFar(enemy.getBox().x + 10, enemy.getBox().y);
    EXPECT_TRUE(enemy.PlayerOutofRange(playerFar));
}

TEST_F(EnnemyTest, FollowPlayerFlipsDirectionWhenInRange) {
    enemy.changePosition(0, 0);
    enemy.setVel(1, 0);  // moving right
    EntityMock playerLeft(-2, 0);
    enemy.followPlayer(playerLeft);
    EXPECT_LT(enemy.getVel().x, 0);

    EntityMock playerRight(2, 0);
    enemy.followPlayer(playerRight);
    EXPECT_GT(enemy.getVel().x, 0);
}

TEST_F(EnnemyTest, VaTomberDetectsFallAndGround) {
    auto map = makeMap(5, 5, 0);
    // cellule vide marquée -1
    map[2][2] = -1;
    enemy.changePosition(1, 1);
    enemy.setVel(1, 0);
    EXPECT_TRUE(enemy.vaTomber(map));

    map[2][2] = 1;  // sol
    EXPECT_FALSE(enemy.vaTomber(map));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
