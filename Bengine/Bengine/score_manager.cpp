#include "score_manager.h"

ScoreManager* ScoreManager::instance_ = nullptr;

ScoreManager::ScoreManager()
{
	score_ = 0;
	high_score_ = 0;
}

ScoreManager* ScoreManager::instance()
{
	if(instance_ == nullptr)
	{
		instance_ = new ScoreManager();
	}
	return instance_;
}

ScoreManager::~ScoreManager()
{
	delete instance_;
}

void ScoreManager::set_score(const int& score)
{
	score_ = score;
	if (score_ > high_score_)
		high_score_ = score_;
}

int ScoreManager::score() const
{
	return score_;
}

int ScoreManager::high_score() const
{
	return high_score_;
}
