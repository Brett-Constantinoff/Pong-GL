#include "App.h"

//runs once on startup
void App::onStart(){
    /*
    APPLICATION SETTINGS
    */

    //dont need depth testing since this is all 2D
    disableDepthTesting();

    //need these setting for the font rendering
    enableBlending();
    blendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    enableCullFace();

    /*
    INITIALIZE ANY APP UTILS AND ATTRIBUTES
    */

    //utility attributes
    mSoundEngine = Utils::createSoundEngine();
    mTextRenderer = new TextRenderer();
    mTextRenderer->loadFont("src/res/fonts/OCRAEXT.TTF", 24);

    //object attributes
    glm::vec2 playerSize = {15.0f, 150.0f};
    glm::vec2 playerSpeed = {500.0f, 500.0f};
    mPlayer1 = new Player({15.0f, (mScreenHeight / 2.0f) - (playerSize.y / 2.0f)}, playerSize, playerSpeed, {1.0f, 0.0f, 0.0f}, "WASD");
    mPlayer2 = new Player({mScreenWidth - playerSize.x - 15.0f, (mScreenHeight / 2.0f) - (playerSize.y / 2.0f)}, playerSize, playerSpeed, {0.0f, 0.0f, 1.0f}, "ARROW");
    mCollidables.push_back(mPlayer1);
    mCollidables.push_back(mPlayer2);
    mBallSize = {15.0f, 15.0f};
    glm::vec2 ballSpeed = {500.0f, 500.0f};
    mBall = new Ball({mScreenWidth / 2.0f - (mBallSize.x / 2.0f), mScreenHeight / 2.0f - (mBallSize.y / 2.0f)}, mBallSize, ballSpeed, {0.0f, 1.0f, 0.0f});
    mBackground = new Background({mScreenWidth, mScreenHeight}, {0.0f, 0.0f});
    for(uint32_t i = 0; i < 3 ; i++){
        Obstacle* o = new Obstacle({Utils::random(100.0f, mScreenWidth - 100.0F), Utils::random(100.0f, mScreenHeight - 100.0f)}, playerSize, {0.0f, 0.0f}, {1.0f, 1.0f, 0.0f});
        mObstacles.push_back(o);
        mCollidables.push_back(o);
    }

    //game attributes
    mPlayer1Score = 0;
    mPlayer2Score = 0;
    mGameState = GameState::RUNNING;
}

//runs everyframe
void App::onUpdate(){
    //setup time
    mCurrFrame = glfwGetTime();
    mDeltaTime = mCurrFrame - mLastFrame;
    mLastFrame = mCurrFrame;
    
    /*
    IF GAME IS RUNNING UPDATE OBJECTS AND PERFORM GAME LOGIC
    */
    if(mGameState == GameState::RUNNING){
        //position updates
        mPlayer1->update(mDeltaTime, *getID(), {mScreenWidth, mScreenHeight});
        mPlayer2->update(mDeltaTime, *getID(), {mScreenWidth, mScreenHeight});
        mBall->update(mDeltaTime, *getID());

        //scoring logic
        if(mBall->outOfBoundLeft()){
            mPlayer2Score++;
            if(mPlayer2Score == GAME_OVER){
                mPlayer2Winner = true;
            }
            mSoundEngine->play2D("src/res/sounds/score.wav", false);
            mBall->respawn({mScreenWidth / 2.0f - (mBallSize.x / 2.0f), mScreenHeight / 2.0f - (mBallSize.y / 2.0f)});
        }
        else if(mBall->outOfBoundsRight()){
            mPlayer1Score++;
            if(mPlayer1Score == GAME_OVER){
                mPlayer1Winner = true;
            }
            mSoundEngine->play2D("src/res/sounds/score.wav", false);
            mBall->respawn({mScreenWidth / 2.0f - (mBallSize.x / 2.0f), mScreenHeight / 2.0f - (mBallSize.y / 2.0f)});
        }

        /*
        HANDLE COLLISIONS
        */

        //ball vs players and obsatcles
        for(auto c : mCollidables){
            if(mBall->onCollideObject(c)){
                mSoundEngine->play2D("src/res/sounds/hit.wav", false);
                mBall->setColour({Utils::random(0.5f, 1.0f), Utils::random(0.5f, 1.0f), Utils::random(0.5f, 1.0f)});
            }
        }

        //ball vs screen bounds
        if(mBall->onCollideWalls()){
            mSoundEngine->play2D("src/res/sounds/hit.wav", false);
        }
    }
    /*
    ONCE SOMEONE WINS RESET THE STATE OF THE GAME
    */
    else if(mGameState == GameState::RESET){
        mBall->respawn({mScreenWidth / 2.0f - (mBallSize.x / 2.0f), mScreenHeight / 2.0f - (mBallSize.y / 2.0f)});
        mPlayer1Score = 0;
        mPlayer2Score = 0;
        mPlayer1Winner = false;
        mPlayer2Winner = false;
        mGameState = GameState::RUNNING;
        mResetTime = 10;
    }
}

//render calls go here
void App::onRender(){

    //draw the objects
    mBackground->draw();
    mPlayer1->draw();
    mPlayer2->draw();
    mBall->draw();
    for(auto o : mObstacles){
        o->draw();
    }

    //convert numeric values to string for rendering
    std::string winner;
    std::stringstream ss1, ss2, countDown, spawnTimer;
    ss1 << mPlayer1Score;
    ss2 << mPlayer2Score;
    countDown << mResetTime;
    spawnTimer << mSpawnObstacle;

    //render score
    mTextRenderer->render(ss1.str() + " | " + ss2.str(), {mScreenWidth / 2.0f,  25.0f}, 2.0f, {1.0f, 1.0f, 1.0f}, true);

    //render obstacle timer
    mTextRenderer->render("Obstacles will spawn in: " + spawnTimer.str() + " seconds!", {0.0f, 10.0f}, 0.5f, {1.0f, 1.0f, 1.0f}, false);
    mObstacleTicks += mDeltaTime;
    if(mObstacleTicks >= 1.0f){
        mSpawnObstacle--;
        mObstacleTicks = 0.0f;
    }

    if(mSpawnObstacle == 0){
        //spawn new obstacle
        for(auto o : mObstacles){
            o->respawn( {Utils::random(100.0f, mScreenWidth - 100.0F), Utils::random(100.0f, mScreenHeight - 100.0f)} );
        }
        mSpawnObstacle = 25;
    }

    //set the winners
    if(mPlayer1Winner){
        winner = "RED PLAYER";
        mGameState = GameState::OVER;
    }
    
    if(mPlayer2Winner){
        winner = "BLUE PLAYER";
        mGameState = GameState::OVER;
    }

    //render game over and countdown timer
    if(mGameState == GameState::OVER){
        //render these in the middle of the screen
        mTextRenderer->render("GAME OVER! " + winner + " won!", {mScreenWidth / 2.0f,  mScreenHeight / 2.0f}, 2.0f, {1.0f, 1.0f, 1.0f}, true);
        mTextRenderer->render("Game will restart in " + countDown.str() + " seconds!", {mScreenWidth / 2.0f,  mScreenHeight / 2.0f + 50.0f}, 2.0f, {1.0f, 1.0f, 1.0f}, true);
        
        //countdown from 10
        mCountDownTicks += mDeltaTime;
        if(mCountDownTicks >= 1.0f){
            mResetTime--;
            mCountDownTicks = 0.0;
        }
        
        //reset the game one the timer is finished
        if(mResetTime == 0){
            mGameState = GameState::RESET;
        }
    }
}


//any memory allocated for the app needs to be deleted
App::~App(){
    for(auto c: mCollidables){
        delete c;
    }
    delete mBall;
    delete mBackground;
    delete mTextRenderer;
    delete mSoundEngine;
}