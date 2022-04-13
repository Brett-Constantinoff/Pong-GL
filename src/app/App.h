#ifndef APP_H
#define APP_H

#include "../utils/Context.h"
#include "../utils/TextRenderer.h"
#include "../shaders/Shader.h"
#include "objects/Player.h"
#include "objects/Ball.h"
#include "objects/Obstacle.h"
#include "objects/Background.h"
#include <sstream>

#define GAME_OVER 5

enum class GameState{
    RUNNING = 0,
    OVER = 1,
    RESET = 2
};

class App : public Context{
    //define any attirbutes your app needs
    private:
        //utility attributes
        irrklang::ISoundEngine* mSoundEngine;
        TextRenderer* mTextRenderer;
        float mCurrFrame;
        float mDeltaTime;
        float mLastFrame = 0.0f;
        float mCountDownTicks = 0.0f;
        float mObstacleTicks = 0.0f;
        int mResetTime = 10;
        int mSpawnObstacle = 25;
        float mScreenWidth = static_cast<float>(SCREEN_WIDTH);
        float mScreenHeight = static_cast<float>(SCREEN_HEIGHT);

        //object attributes
        Background* mBackground;
        Ball* mBall;
        glm::vec2 mBallSize;
        Player* mPlayer1;
        Player* mPlayer2;
        std::vector<Obstacle*> mObstacles;
        std::vector<Object*> mCollidables;

        //game attributes
        GameState mGameState;
        bool mPlayer1Winner = false;
        bool mPlayer2Winner = false;
        uint16_t mPlayer1Score;
        uint16_t mPlayer2Score;
       
    //can add additional methods, but these 4 are all you really need
    public:
        virtual void onStart();
        virtual void onUpdate();
        virtual void onRender();
        ~App();
};
#endif