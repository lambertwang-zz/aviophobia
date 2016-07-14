/*
 * Event Step class
 */

// aviophobia headers
#include "EventStep.h"
#include "GameManager.h"

av::EventStep::EventStep() {
    // Obtain stepcount from game_manager
    av::GameManager &game_manager = av::GameManager::getInstance();
    this->step_count = game_manager.getStepCount();

    // "av::step"
    this->setType(av::STEP_EVENT);
}

av::EventStep::EventStep(int init_step_count) {
    this->step_count = init_step_count;
    
    this->setType(av::STEP_EVENT);
}

void av::EventStep::setStepCount(int new_step_count) {
    this->step_count = new_step_count;
}

int av::EventStep::getStepCount() const {
    return this->step_count;
}
